#include <iostream>
struct X {
    X() {
        std::cout <<"X::X(" << std ::endl;
    }
    ~X() {
        std::cout <<"X::~XO" << std :: endl;
    }
};

struct Y {
    Y(){
    std::cout << "Y: :Yo" << std ::endl;
    }
    ~Y(){
    std::cout <<"Y: :~Y()" << std ::endl;
    }
};

struct Parent {
    Parent() {
        std::cout << "Parent : :Parent(" << std :: endl;
    }
    ~Parent() {
        std::cout << "Parent: : ~Parent(" << std :: endl;
    }
    X x;
};

struct Child : public Parent {
    Child() {
        std ::cout << "Child : : Child()" << std :: endl;
    }
    ~Child() {
        std ::cout << "Child : : ~Child()" << std :: endl;
    }
    Y y;
};

int main() {
Child c;
return 0;
}