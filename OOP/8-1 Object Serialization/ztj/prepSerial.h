/**
 * Write a definition/declaration of your self-designed class here.
 * Your class MUST have specialization functions of std::tuple_element,
 * std::tuple_size and std::get(the const and none const versions) in
 * order to be serialized.
*/

#ifndef _prep_Serial_h
#define _prep_Serial_h

class MyClass;

//the specialization of the required functions
template <size_t Index>
struct std::tuple_element<Index, MyClass>;

template <>
struct std::tuple_size<MyClass>;

template <size_t Index>
typename tuple_element<Index, MyClass>::type& std::get(MyClass& obj);

template <size_t Index>
const typename tuple_element<Index, MyClass>::type& std::get(const MyClass& obj);

#endif
//those four functions are mandatory.