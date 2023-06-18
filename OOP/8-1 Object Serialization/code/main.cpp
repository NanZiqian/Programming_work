#include "Serialization.h"
#include "CustomizedClass.h"


int main(){

//Part 1: binary serialization
    MyClass a,b;
    a.idx=0;
    a.name = "I love Elden ring.";
    a.data.push_back(make_pair(0,100));
    //a.data2.assign(1,5);
    a.data3.insert(100);
    a.data4.insert(make_pair(0,100));

    //binSerial::Serialization::Serialize(a, "MyClass_a.dat");
    //binSerial::Deserialization::Deserialize(b, "MyClass_a.dat");

    // cout << "idx: " << b.idx << endl;
    // cout << "name: " << b.name << endl;
    // for (auto p : b.data) {
    //     cout << "data[].fisrt= " << p.first << " data[].second= " << p.second << endl;
    // }
    // /*for (auto p : b.data2) {
    //     cout << " data2[]= " << p << endl;
    // }*/
    // for (auto p : b.data3) {
    //     cout << " data3[]= " << p << endl;
    // }
    // for (auto p : b.data4) {
    //     cout << "data4[].fisrt= " << p.first << " data4[].second= " << p.second << endl;
    // }

//Part 2 xml serialization
    xmlSerial::Serialization::Serialize(a, "XMLSerializaiton","MyClass_a.xml",0);
    xmlSerial::Deserialization::Deserialize(b, "MyClass_a.xml",0);

    //Part 2.2 bin mode xml serialization
    //xmlSerial::Serialization::Serialize(a, "XMLSerializaiton","MyClass_a.xml",1);
    //xmlSerial::Deserialization::Deserialize(b, "MyClass_a.xml",1);

    cout << "idx: " << b.idx << endl;
    cout << "name: " << b.name << endl;
    for (auto p : b.data) {
        cout << "data[].fisrt= " << p.first << " data[].second= " << p.second << endl;
    }
    /*for (auto p : b.data2) {
        cout << " data2[]= " << p << endl;
    }*/
    for (auto p : b.data3) {
        cout << " data3[]= " << p << endl;
    }
    for (auto p : b.data4) {
        cout << "data4[].fisrt= " << p.first << " data4[].second= " << p.second << endl;
    }


    return 0;

}