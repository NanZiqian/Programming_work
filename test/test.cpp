#include <iostream>
#include <vector>

using namespace std;

int main(){

    vector<int> a(3);
    a.at(3);
    cout << std::is_same<int, signed int>::value << endl;
    return 0;
}