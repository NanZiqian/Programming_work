#include"Adventrue.h"

int main(){
    Adventrue x;
    int flag = 1;
    while(flag){
        x.startgame();
        flag=x.Menu();
    }
    return 0;
}