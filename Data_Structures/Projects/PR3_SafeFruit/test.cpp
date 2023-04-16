#include<iostream>

using namespace std;

int digit(int x){
    int i=1;  //一定要初始化，这里初始化为1是因为循环一开始就将num去掉了一位数
	while(x/=10)   //数完一位数就去掉一位
	{
		i++;   //计数
	} 
    return i;
}

void int_with_zeros(int x){//00x or 010(x=10)
    for(int it=0;it<3-digit(x);it++)
        cout <<"0";
    cout << x;
}

void cout_tongyu(int x,int m,int max){//输出mod m余数为x，小于等于max的所有数
    for(int i=x;i<=max;i+=m)//空格左边
        for(int j=i+m;j<=max;j+=m){
            int_with_zeros(i);
            cout << " ";
            int_with_zeros(j);
            cout <<endl;
        }
}


//水果少，不安全的tips多。n=100个tips，m=15种水果。
void cout_tips1(int a,int b){//00a 00a+1到00b-1 00b
    for(int i=a;i<=b-1;i++)//空格左边
        for(int j=i+1;j<=b;j++){//空格右边
            for(int it=0;it<3-digit(i);it++)
                cout <<"0";
            cout << i<<" ";
            for(int it=0;it<3-digit(j);it++)
                cout <<"0";
            cout << j << endl;
        }
}

//水果多，但不安全的tips少；有一个较大的解.
void cout_tips2(){
    for(int i=1;i<=10;i++){
        cout << "001 ";
        for(int it=0;it<3-digit(i);it++)
            cout <<"0";
        cout << i << endl;
    }
        
}

//90个tips，36个水果，有6个大小为6的解。x为6，有x个不同的余数
void cout_tips(int x){
    for(int i=1;i<=x;i++){
        cout_tongyu(i,x,x*x);
    }
}



void cout_price(int m){
    for(int i=1;i<=m;i++){
        for(int it=0;it<3-digit(i);it++)
            cout <<"0";
        cout << i<<" " <<i << endl;
    }
}

int main(){
    
    //cout_tips1(12,25);
    cout_price(25);
    return 0;
}