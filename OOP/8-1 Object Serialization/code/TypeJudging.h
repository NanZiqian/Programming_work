#include <bits/stdc++.h>

using namespace std;

template<typename T>
class hasOutputMethod
{
    //"->" is used to assign what auto means
    template<typename C>
    static constexpr auto check(C*)
    -> typename is_same< ostream&, decltype(declval<ostream&>() << declval<C>()) >::type;

    template<typename C>
    static constexpr false_type check(...);

    typedef decltype(check<T>(0)) type;
public:
    static constexpr bool value = type::value;
};

template<typename T>
class isContainer {
    template<typename C>
    static constexpr true_type check(vector<C>);

    template<typename C>
    static constexpr true_type check(list<C>);

    template<typename C>
    static constexpr true_type check(set<C>);

    template<typename C1, typename C2>
    static constexpr true_type check(map<C1, C2>);

    static constexpr true_type check(string);

    static constexpr false_type check(...);

    typedef decltype(check(declval<T>())) type;
public:
    static constexpr bool value = type::value;
};

template<typename T>
class isPointer {
    template<typename C>
    static constexpr true_type check(unique_ptr<C>);

    template<typename C>
    static constexpr true_type check(shared_ptr<C>);

    static constexpr false_type check(...);

    typedef decltype(check(declval<T>())) type;
public:
    static constexpr bool value = type::value;
};

template<typename T>
class isPair{

    template<typename C1,typename C2>
    static constexpr true_type check(pair<C1, C2>);

    static constexpr false_type check(...);

    typedef decltype(check(declval<T>())) type;
public:
    static constexpr bool value = type::value;
};

template<typename T>
class hasPushback {
    template<typename C>
    static constexpr auto check(C* container)
    -> decltype(container->push_back(declval<typename C::value_type>()), true_type());

    template<typename C>
    static constexpr false_type check(...);
public:
    static constexpr bool value = decltype(check<T>(nullptr))::value;
};


/// @brief Insert a value at the end of a container object.
/// @tparam T 
/// @param obj 
/// @param x 
template <typename T>
void append(T &obj, const typename T::value_type &x)
{
    if constexpr (hasPushback<T>::value)
        obj.push_back(x);
    else
        obj.insert(x);
}