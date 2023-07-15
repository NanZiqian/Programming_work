#include <iostream>

using namespace std;

#define NUM 8

int location[NUM];//location[i]记录第i列皇后的位置
int row[NUM];//a[i]记录行i是否安全，安全为1，行从0开始
int solution_number=0;
int L[2*NUM-1],R[2*NUM-1];//L[i+j]记录(i,j)所在的反对角线是否安全，R[i-j+7]记录(i,j)所在的对角线是否安全

void dfs(int index){//index代表正在配置第index列皇后的位置
    if(index == NUM){
        for(int i=0;i<NUM;i++){
            cout << location[i] << " ";
        }
        cout << endl;
        solution_number++;
        
        return;
    }else{
        for(int i=0;i<NUM;i++){//探讨第index列是否可以放在i行
            if(row[i] && L[i+index] && R[i-index+7]){//如果行i、L[i+index]、R[i-index+7]安全，可以将第index列皇后放在行i
                location[index]=i;
                row[i]=0;
                L[i+index]=0;
                R[i-index+7]=0;
                dfs(index+1);

                //back tracking
                row[i]=1;
                L[i+index]=1;
                R[i-index+7]=1;
            }
        }
        return;//return到index-1，说明index-1在行i不行，进行下一行判断
    }
}

int main(){
    
    for(int i=0;i<NUM;i++){
        row[i]=1;
    }

    for(int i=0;i<NUM;i++){
        location[i]=-1;
    }

    for(int i=0;i<2*NUM-1;i++){
        L[i]=R[i]=1;
    }

    // for(int i=0;i<2*NUM-1;i++){
    //     cout << L[i] << " " << R[i] << endl;
    // }
    dfs(0);
    cout << "solution number: " << solution_number << endl;

    return 0;

}