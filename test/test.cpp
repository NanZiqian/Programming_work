#include <iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> v;
    v.resize(10);
    v.assign(10,1);
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
    v.assign(10,2);
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
    return 0;
}