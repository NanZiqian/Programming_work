#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

//撒谎的werewolf可以有1~M-1个。撒谎的人刚好有L个；可以假设撒谎的狼人有x个，x从1到M-1循环。
//输出的解要降序，有两个解，且该两个解前k个人序号相同，第K+1个人序号A大，那么就取A  
class werewolf{
public:
    werewolf(){
        inputNML();
        sequence.resize(M);
        identity.resize(N);
        temp_wolf.resize(M);
        info.resize(N);
        input_info();
    }

    void printVector(vector<int>& v) {
        for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }

    void input_info(){
        for(int k=0;k<N;k++){
            cin >> info[k];
        }
    }

    void inputNML(){
        cin >> N >> M >> L;
    }

    int lie(int id,int x){
        if(x>0 && id || x<0 && !id){
            return 0;
        }else{
            return 1;
        }
    }

    int judge(){//1是解，0不是解
        lying_players=lying_wolves=0;
        identity.assign(N,1);
        for(int it=0;it<M;it++){//将temp_wolf变为identity
            identity[temp_wolf[it]]=0;
        }
        //identity stored
        for(int it=0;it<N;it++){
            int x=info[it];//下标为it的人说的信息，小心abs(x)是他说的人的下标+1
            int id=identity[abs(x)-1];//下标为it的人说的那个人是人1还是狼人0
            //cout << "the player " << it << " says " << x <<" and actually its id is " << id << " so " <<lie(id,x) <<"  ";
            if(lie(id,x)){//下标为it的人说谎了
                lying_players++;
                if(identity[it]==0)//下标为it的人是狼人
                    lying_wolves++;
            }
        }
        //cout << "has  lying_wolves: " << lying_wolves << "; has lying_players: " << lying_players << endl;
        if(lying_wolves < 1 || lying_wolves == M)
            return 0;
        if(lying_players != L)
            return 0;
        return 1;
    }

    void method(){
        
        method(0,N-1);
        if(flag==0){
            cout <<"No Solution";
        }
    }

    void method(int i,int j) {//递归方法,i是循环数，i>0；j用来控制没被选中的数字
        if(flag)
            return;
        i++;//确定第i层循环
        for(int k=j;k>=0;k--) {
            temp_wolf[i-1]=k;//每一层循环都将抽取一个数字，记录其下标
            
            if(i!=M) {//深入到下一层循环
                j--;//在前一循环初始条件的基础上+1
                method(i,j);
            }else {//已经在第M层循环
                //printVector(temp_wolf);
                if(judge()){
                    cout << temp_wolf[0]+1;
                    for(int it=1;it<M;it++){
                        cout << " " << temp_wolf[it]+1 ;
                    }
                    flag = 1;
                    return;
                }
            }
        }//结束for循环
        
    }//结束method方法

    
private:
    int N,M,L;//N为玩家人数，每人会说一句话；M为狼人人数；
    int lying_wolves;
    int lying_players;
    int flag=0;
    vector<int> info;//用于存储每个人说的话
    vector<int> sequence;//用于存储最大解
    vector<int> identity;//用于将temp_wolf转化为每个人的身份
    vector<int> temp_wolf;//C_N^M个情况中的一种，记录着所有狼人的下标

};

int main(){
    werewolf a;
    a.method();
    return 0;
}