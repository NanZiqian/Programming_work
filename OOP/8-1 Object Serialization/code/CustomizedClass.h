
#ifndef _CUSTOMIZED_CLASS_H
#define _CUSTOMIZED_CLASS_H

/// Your class MUST have functions of std::tuple_element,
//      std::tuple_size and std::get(the const and none const versions) in order to be serialized.
/// It is recommended that you define those functions and declare other objects here and define other objects else where.

struct MyClass {
    int idx;
    string name;
    vector<pair<int,double>> data;
    //list<int> data2;
    set<int> data3;
    map<int,double> data4;
};

//std::ostream& operator<<(ostream& out,MyClass & rhs){
//    out << "idx: "<< rhs.idx <<endl;
//    out << "name: "<< rhs.name <<endl;
//    for (auto p : rhs.data) {
//        out << "data[].first= " << p.first << " data[].second= " << p.second << endl;
//    }
//    for (auto p : rhs.data2) {
//        out << " data2[]= " << p << endl;
//    }
//    for (auto p : rhs.data3) {
//        out << " data3[]= " << p << endl;
//    }
//    for (auto p : rhs.data4) {
//        out << "data4[].first= " << p.first << " data4[].second= " << p.second << endl;
//    }
//    return out;
//}

template <size_t Index>
struct std::tuple_element<Index, MyClass> {
    using type = typename conditional<Index == 0, int,
                typename conditional<Index == 1, string, 
                typename conditional<Index == 2, vector<pair<int,double>>,
                //typename conditional<Index == 3, list<int>,
                typename conditional<Index == 3, set<int>, map<int,double>>::type>::type>::type>::type;
};

template <>
struct std::tuple_size<MyClass>: integral_constant<size_t, 6> {};

template <size_t Index>
typename tuple_element<Index, MyClass>::type& get(MyClass& obj) {
    
    if constexpr (Index == 0) {
        return obj.idx;
    } else if constexpr (Index == 1) {
        return obj.name;
    } else if constexpr (Index == 2) {
        return obj.data;
    } else if constexpr (Index == 3) {
        /*return obj.data2;
    } else if constexpr (Index == 4) {*/
        return obj.data3;
    } else{
        return obj.data4;
    }
}

template <size_t Index>
const typename tuple_element<Index, MyClass>::type& get(const MyClass& obj) {
    
    if constexpr (Index == 0) {
        return obj.idx;
    } else if constexpr (Index == 1) {
        return obj.name;
    } else if constexpr (Index == 2) {
        return obj.data;
    } else if constexpr (Index == 3) {
        /*return obj.data2;
    } else if constexpr (Index == 4) {*/
        return obj.data3;
    } else{
        return obj.data4;
    }
}

#endif