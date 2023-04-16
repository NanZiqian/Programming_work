#include<iostream>
#include<stack>
#include<vector>
#include<cmath>
using namespace std;

class Calculator{
    public:
    Calculator(){

    }
    ~Calculator(){
        while(!stacknum.empty()){
            makeEmpty(stacknum.top());
            stacknum.pop();
        }
    }
    
    struct TreeNode{  //树的结构体 
        vector<char> val;
        struct TreeNode *left;
        struct TreeNode *right;
        TreeNode(char ch){
            val.resize(10,'\0');
            val[0]=ch;
            left=nullptr;
            right=nullptr;
        }
    };


    int IsOp(char c) {//判断是否为运算符，是运算符返回1，若不是返回0
        switch(c){
		case '+':   
        case '-':  
        case '*':   
        case '/':   
        case '^':  
            return 1;
		default:
            return 0;		   
        }
    }


    /// @brief 运算符优先级比较，1代表theta1优先级高于theta2
    /// @param theta1 
    /// @param theta2 
    /// @return 0/1
    char Precede(char theta1,char theta2){//运算符优先级比较 ,1 theta1 2 theta2 3运算顺序比较1-2-3，则theta1>theta2，2-3-1，则theta1<theta2

	int i=0,j=0;
	char pre[5][5]={// +   -   *   /   ^
                    {'>','>','<','<','<'},  
                    {'>','>','<','<','<'},  
                    {'>','>','>','>','<'},  
                    {'>','>','>','>','<'},  
                    {'>','>','>','>','<'},  
                    }; 
                
    switch(theta1){
        case '+': i=0; break;  
        case '-': i=1; break;  
        case '*': i=2; break;  
        case '/': i=3; break;  
        case '^': i=4; break;  
	}
	
    switch(theta2){
        case '+': j=0; break;
        case '-': j=1; break;  
        case '*': j=2; break;  
        case '/': j=3; break;  
        case '^': j=4; break;  
    }
    return(pre[i][j]);
}

    double Converttodouble(vector<char> v){//把一个字符串转化为整数,v至少有一个数字
        int i=0,j=0;
        double sum=0;
        while(v[i++]!='\0' && v[i-1]!='.'){
            sum=sum*10+(v[i-1]-'0');
        }

        if(v[i-1]=='.'){
            while(v[i++]!='\0'){
                j++;
                sum=sum+(v[i-1]-'0')*pow(0.1,j);
            }
        }
        
        return sum;
    }

    void moveright(vector<char>& v){//把一个字符串所有右移一位
        int i=0;
        while(v[i++]!='\0');
        while(--i>=1){
            v[i]=v[i-1];
        }
    }

    void popUntilnull(){//当运算时是右括号时，运算直至弹出左括号；当expression读完时，弹出直至stackop为null
        while(!stackop.empty() && stackop.top()!='('){
            normalpop();
        }
        if(!stackop.empty() && stackop.top()=='(')
            stackop.pop();

    }

    void normalpop(){//弹出一次运算符，比stackop栈顶操作符优先级高或stackop为空时作为父节点，从stacknum弹出的适量结点为子结点，整体压入stacknum；低于则poponce()，直至比stackop栈顶操作符优先级高，或发现(，或stackop空。(1+1*1^1+1)
        stacktop=stackop.top(); 
        stackop.pop();
        if(stackop.empty() || stackop.top()=='('){
            TreeNode* x=new TreeNode(stacktop);
            x->right=stacknum.top();
            stacknum.pop();
            x->left=stacknum.top();
            stacknum.pop();
            stacknum.push(x);
        }else{
        switch(Precede(stackop.top(),stacktop)){
            case '<':{                
				TreeNode* x=new TreeNode(stacktop);
                x->right=stacknum.top();
                stacknum.pop();

                x->left=stacknum.top();
                stacknum.pop();
                stacknum.push(x);
				break;
                
            }
            case '>':{            
				while(!stackop.empty() && Precede( stackop.top(),stacktop)=='>' && stackop.top()!='('){
                    poponce();
                }
                TreeNode* x=new TreeNode(stacktop);
                x->right=stacknum.top();
                stacknum.pop();

                x->left=stacknum.top();
                stacknum.pop();
                stacknum.push(x);
            }
        }
        }
    }

    void poponce(){
        stacktop=stackop.top(); 
        stackop.pop();

        TreeNode* x=new TreeNode(stacktop);
        x->right=stacknum.top();
        stacknum.pop();

        x->left=stacknum.top();
        stacknum.pop();
        stacknum.push(x);

    }

    double CalculateTree(){
        return CalculateTree(stacknum.top());
    }

    void CreateExpressionTree(){
        cin.getline(expression,2021);
        int j=0,k=0,i=0;
        while(expression[j++]!='\0'){
            if(expression[j]==' '){
                k=j;
                while(expression[k+1]!='\0'){
                    expression[k]=expression[k+1];
                    k++;
                }
            expression[k]=expression[k+1];
            }
        }

        j=0;
        int a[2]={0};
        while(expression[j]!='\0'){
            if(expression[j]=='(')
                a[0]++;
            if(expression[j]==')')
                a[1]++;
            j++;
        }
        if(a[0]!=a[1]){
            cout <<"error:parentheses not matched"<<endl;
            exit(0);
        }

        while((temp=expression[i++])!='\0'){//i不能改！！！
            if(temp>='1' && temp<='9'){//字符是数字时，构造一个此value为此数字的节点
                stacknum.push(new TreeNode(temp));
                TreeNode* x=stacknum.top();
                j=0;
                while(expression[i]>='1' && expression[i]<='9'||expression[i]=='.'){//当下一位还是数字时，或小数点时
                    x->val[++j]=expression[i++];
                }
            }
            else if(temp=='('){
                if(IsOp(expression[i])){
                    cout <<"input error"<<endl;
                    exit(0);
                }
                stackop.push(temp);
            }
            else if(temp==')'){
                popUntilnull();
            }
            else if(IsOp(temp)){//当temp是运算符时，若stackop为空，直接stackop.push(temp)。若stackop非空，若优先级<=栈顶操作符，则弹出stackop的栈顶操作符，以其为父结点， 以从stacknum弹出的适量结点为子结点，整体压入stacknum，直至比stackop栈顶操作符优先级高。
                if(IsOp(expression[i]) || expression[i]==')'){
                    cout <<"input error"<<endl;
                    exit(0);
                }
                if(stackop.empty()||stackop.top()=='('){
                    stackop.push(temp);

                }
                else {
                    switch(Precede(stackop.top(),temp)){
                        case '<':{     
						stackop.push(temp);
                        
						break;
                    }
                    case '>':{     
						while(!stackop.empty() && stackop.top()!='(' && Precede(stackop.top(),temp)=='>'  ){
                            poponce();
                        }
                        stackop.push(temp);

                        break;
                    }
                    }
                }
                
            }
        }

        popUntilnull();
        if(!stackop.empty() || stacknum.size()!=1){
            cout <<"error!" << endl;
            exit(0);
        }
    }

    double CalculateTree(TreeNode* x){
        if(!(x->val[0]=='+'||x->val[0]=='-'||x->val[0]=='*'||x->val[0]=='/'||x->val[0]=='^'))
            return Converttodouble(x->val);
        if(x->val[0]=='+'){
            return CalculateTree(x->left)+CalculateTree(x->right);
        }
        if(x->val[0]=='-'){
            return CalculateTree(x->left)-CalculateTree(x->right);
        }
        if(x->val[0]=='*'){
            return CalculateTree(x->left)*CalculateTree(x->right);
        }
        if(x->val[0]=='/'){
            double a=CalculateTree(x->left),b=CalculateTree(x->right);
            if(b==0){
                cout <<"The divisor is 0" << endl;
                exit(0);
            }
            return a/b;
        }
        if(x->val[0]=='^'){
            return pow(CalculateTree(x->left),CalculateTree(x->right));
        }
    }
    
    void outputexpression(){
        cout << expression << endl;
    }

    void makeEmpty( TreeNode * t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }



    private:
    char expression[2021];
    stack<char> stackop;
    stack<TreeNode*> stacknum;
    char temp,stacktop;//temp用来存储从expression中取下的字符，stacktop用来存储从stack中弹出的字符

};