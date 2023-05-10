#include <iostream>
#include<string>

using namespace std;

int main(){
    string temp;
    int a=10000;
    temp='-';
    temp = temp + to_string(a);
    cout << temp << endl;
    return 0;
}