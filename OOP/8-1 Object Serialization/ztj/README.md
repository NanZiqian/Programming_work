# The serialization project

> 赵天健 3210101830

- **I COMPLETED BOTH OF THE BONUS**.

- To run the project, you need to first have the `tinyxml2.h` file in your include path, then you just need to execute `run.sh` in the zip file to test the project.

- Note that the serialization itself might not be portable between different operating systems (if the `typeinfo::hash_code()` function implements differently in different compilers).

- If you want to test the serialization of user-defined types, you can either use the `MyClass` I wrote in `test.cpp` or write a class of your own. But if you choose the latter, you **MUST** implement the following functions and declare them inside the `prepSerial.h` file (or just define them in that file is OK): 

  ```c++
  template <size_t Index>
  struct std::tuple_element<Index, YourClass>;
  
  template <>
  struct std::tuple_size<YourClass>;
  
  template <size_t Index>
  typename tuple_element<Index, YourClass>::type& std::get(YourClass& obj);
  
  template <size_t Index>
  const typename tuple_element<Index, YourClass>::type& std::get(const YourClass& obj);
  ```