#include"vector.h"

int main(){
    //testing null ctor, empty(), print(), size(), capacity()
    Vector<int> a,b(3);
    cout << "a is empty? "<< a.empty() << " ";
    a.print();

    //testing ctor(int)
    cout << "b is empty? "<< b.empty() << " ";
    b.print();

    //testing push_back(),inflate()
    b.push_back(1);
    b.push_back(3);
    b.push_back(4);
    b.push_back(2);
    b.print();
    cout << "b[1]= " << b[1] <<" b.at(1)= " << b.at(1) << " b.at(20)= ";
    try{
        cout<<b[20]<<endl;
    }catch(OutOfRange &e){
        e.what();
    }
    cout << endl;

    //testing copy ctor
    Vector<int> c(b);
    c.print();

    //testing resize(), clear()
    c.resize();
    c.print();

    return 0;
}   