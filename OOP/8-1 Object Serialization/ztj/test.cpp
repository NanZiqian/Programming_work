#include "MySerial.h"

//note that you MUST declare your self-designed classes in prepSerial.h first
struct MyClass {
    int idx;
    string name;
    vector<double> data;
};

template <size_t Index>
struct std::tuple_element<Index, MyClass> {
    using type = typename conditional<Index == 0, int,
                 typename conditional<Index == 1, string, vector<double> >::type>::type;
};

template <>
struct std::tuple_size<MyClass>: integral_constant<size_t, 3> {};

template <size_t Index>
typename tuple_element<Index, MyClass>::type& std::get(MyClass& obj) {
    
    if constexpr (Index == 0) {
        return obj.idx;
    } else if constexpr (Index == 1) {
        return obj.name;
    } else {
        return obj.data;
    }
}

template <size_t Index>
const typename tuple_element<Index, MyClass>::type& std::get(const MyClass& obj) {
    
    if constexpr (Index == 0) {
        return obj.idx;
    } else if constexpr (Index == 1) {
        return obj.name;
    } else {
        return obj.data;
    }
}

/**
 * In the main function are some tests you can use to
 * test my program. Note that if you want to define a
 * new class and serialize it, please declare it first
 * (or define it) in `prepSerial.h`.
 */

int main()
{
    vector<MyClass> a;
    for (int i = 0; i < 10; i++)
        a.push_back((MyClass){i, "tommyzhao", vector<double>(1, 1.1)});
    // MyClass a{1, 3.14, "tommyzhao"};
    // string a = "abc";
    // unique_ptr<MyClass> a(new MyClass);
    // a->value = 1;
    // a->ratio = 3.14;
    // a->name = "tommyzhao";
    binSerial::Serialization::Serialize(a, "DataFile.dat");
    // xmlSerial::Serialization::Serialize_xml(a, "serialization", "data.xml", 1);
    vector<MyClass> b;
    // MyClass b;
    // string b;
    // unique_ptr<MyClass> b(new MyClass);
    binSerial::Deserialization::Deserialize(b, "DataFile.dat");
    // xmlSerial::Deserialization::Deserialize_xml(b, "serialization", "data.xml", 1);
    for (auto x: b)
        cout << x.idx << ' ' << x.name << ' ' << x.data[0] << endl;
    // cout << *b << endl;
    // cout << b << endl;
    // cout << b.value << ' ' << b.ratio << ' ' << b.name << endl;
    // cout << b->value << ' ' << b->ratio << ' ' << b->name << endl;
    // const string &s = std::get<2>(a);
    // cout << s << endl;
    return 0;
}