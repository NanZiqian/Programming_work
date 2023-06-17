#ifndef _SERIALIZATION_CPP
#define _SERIALIZATION_CPP


#include "Serialization.h"

using namespace std;


//Useful function


/// @brief convert string to arithmetic and convert arithmetic to string
/// @tparam out_type 
/// @tparam in_value 
/// @param var 
/// @return 
template<class out_type, class in_value>
out_type convert(const in_value& var) {
    stringstream stream;
    stream << var;  
    out_type result; 
    stream >> result; 
    return result;
}



//Binary serialization


/// @brief serialization ordered by typeid(obj).hash_code, size of a container(if it is), content(depth first search)
/// @tparam T 
/// @param obj 
/// @param dir 
template <typename T>
void binSerial::Serialization::Serialize(const T &obj, string dir)
{
    ofstream out(dir);
    if (!out.good())
    {
        throw exception();
    }
    __serialize(out, obj);
    out.close();
}

/// @brief use function to avoid complicated expression "out.write((char *)(&obj), sizeof(obj))"
/// @tparam T 
/// @param out 
/// @param obj 
template <typename T>
void binSerial::Serialization::write(ofstream& out, const T &obj)
{
    out.write((char *)(&obj), sizeof(obj));
}

/// @brief core process of serialization
/// @tparam T 
/// @param out 
/// @param obj 
template <typename T>
void binSerial::Serialization::__serialize(ofstream& out, const T &obj)
{
    //fout T's hash_code
    write(out, typeid(T).hash_code());
    // cout << "typeid(T).name(): " << typeid(T).name() << endl;
    // cout << "typeid(T).hash_code(): " << typeid(T).hash_code() << endl;
//case 1: T is arithmetic
    if(is_arithmetic<T>::value){
        write(out, obj);
    }
//case 2: T is container. vector list set map string pair
    else if constexpr (isContainer<T>::value)
    {
        //fout size of obj
        //cout << "Container " << typeid(T).name() << "'s size: " << obj.size() << endl;
        write<size_t>(out, obj.size());
        // iterator p's hash code is identical to T::value_type.hash_code()
        for (auto p: obj)
            __serialize(out, p);
    }
//case 3: T is pointer, including smart pointer. If two hash code are next to each other, then there is a pointer.
    else if constexpr (isPointer<T>::value)
    {
        __serialize(out, *obj);
    }
//case 4: T is class
    else if constexpr (is_class<T>::value )//&& !isPair<T>::value
    {
        auto size = tuple_size<T>::value;
        //cout << "Container " << typeid(T).name() << "'s tuple_size: " << size << endl;
        write(out, size);
        traversal_tuple<0>(out, obj);
    }
//case 4: T is pair
    else if constexpr (isPair<T>::value){
        __serialize(out, obj.first);
        __serialize(out, obj.second);
    }
//case 6: T is other unknown type
    else
    {
        static_assert(hasOutputMethod<T>::value, "Invalid type!");
        write(out, obj);
    }
}

/// @brief Handle the situation of customized class. Serialize all the objects in the class
/// @tparam T 
/// @tparam Index 
/// @param out 
/// @param tuple 
template <size_t Index, typename T>
void binSerial::Serialization::traversal_tuple(ofstream& out, const T& tuple)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto & element = get<Index>(tuple);
        __serialize(out, element);
        traversal_tuple<Index + 1>(out, tuple);
    }
}



//binary deserialization


/// @brief The structure is alike
/// @tparam T 
/// @param obj 
/// @param dir 
template <typename T>
void binSerial::Deserialization::Deserialize(T &obj, string dir)
{
    ifstream in(dir);
    if (!in.good())
    {
        throw ios::failure("Can't open the file!");
    }
    __deserialize(in, obj);
    in.close();
}

template <typename T>
void binSerial::Deserialization::read(ifstream &in, T &obj)
{
    in.read((char *)&obj, sizeof(T));
}

template <size_t Index, typename T>
void binSerial::Deserialization::traversal_tuple(ifstream& in, T& tuple)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto &element = get<Index>(tuple);
        __deserialize(in, element);
        traversal_tuple<Index + 1>(in, tuple);
    }
}

/// @brief The deserialization process is th
/// @tparam T 
/// @param in 
/// @param obj 
template <typename T>
void binSerial::Deserialization::__deserialize(ifstream &in, T &obj)
{
    size_t hash;
    read<size_t>(in, hash);
    // cout << "hash: " << hash << endl;
    // cout << "typeid(T).name(): " << typeid(T).name() << endl;
    // cout << "typeid(T).hash_code(): " << typeid(T).hash_code() << endl;
    if (hash != typeid(T).hash_code())
    {
        throw invalid_argument("binSerial::Deserialization argument invalid!");
    }
    if(is_arithmetic<T>::value){
        //cout << "arithmatic(T).value(): " << obj << endl; can't work
        read(in, obj);
    }
    else if constexpr (isContainer<T>::value)
    {
        size_t size;
        read(in, size);
        cout << "Container " << typeid(T).name() << "'s size: " << size << endl;
        for (int i = 0; i < size; i++)
        {
            typename T::value_type value;
            __deserialize(in, value);
            append(obj, value);
        }
    }
    else if constexpr (isPointer<T>::value)
    {
        auto &tarObj = *obj;
        __deserialize(in, tarObj);
    }
    else if constexpr (is_class<T>::value)// && !isPair<T>::value
    {
        size_t size;
        read(in, size);
        traversal_tuple<0>(in, obj);
    }
    else if constexpr (isPair<T>::value){
        auto &tarObj1 = obj.first;
        __deserialize(in, tarObj1);
        auto &tarObj2 = obj.second;
        __deserialize(in, tarObj2);
    }
    else
    {
        static_assert(hasOutputMethod<T>::value, "Invalid type!");
        read(in, obj);
    }
}





//xml serialization


/// @brief 
/// @tparam T 
/// @param obj the object to be serialized
/// @param rootname the root name, for example "serialization"
/// @param dir The output file's path
/// @param bin whether to use base64 binary mode to store xml
template<typename T>
void xmlSerial::Serialization::Serialize(const T &obj, string rootname, string dir, bool bin)
{
//Preparation. Create a new empty xml file
    tinyxml2::XMLDocument _xml;
    //<?xml version="1.0" encoding="UTF-8"?>
    tinyxml2::XMLDeclaration* declaration = _xml.NewDeclaration();
    _xml.InsertFirstChild(declaration);
    XMLElem root = _xml.NewElement(rootname.c_str());
    _xml.InsertEndChild(root);

//Serialization and insert them to root element "rootname.c_str()"
    XMLElem _xml_element = __serialize(obj, _xml);
    if (_xml_element)
    {
        root->InsertEndChild(_xml_element);
    }
    //
    if (!bin)
        _xml.SaveFile(dir.c_str());
    else
    {
        tinyxml2::XMLPrinter* Printer = new tinyxml2::XMLPrinter;
        _xml.Print(Printer);
        encode_base64(Printer->CStr(), dir);
    }
}

/// @brief Serialize an object and transform it to XMLElem
/// @tparam T 
/// @param obj 
/// @param _xml 
/// @return 
template<typename T>
XMLElem xmlSerial::Serialization::__serialize(const T& obj, docType _xml)
{
    XMLElem _xml_elem;
//case 1: <String>string text</String>
    if constexpr (is_same<T, string>::value)
    {
        _xml_elem = _xml.NewElement("string");
        _xml_elem->SetText(obj.c_str());
        return _xml_elem;
    }
//case 2: <Container><Element1><Element2>...</Element2></Element1></Container>
    else if constexpr(isContainer<T>::value)
    {
        _xml_elem = _xml.NewElement("container");
        auto size = obj.size();
        for (auto p: obj)
            _xml_elem->InsertEndChild(__serialize(p, _xml));
    }
//case 3: <Pointer><Element></Element></Pointer>
    else if constexpr (isPointer<T>::value)
    {
        _xml_elem = _xml.NewElement("pointer");
        _xml_elem->InsertEndChild(__serialize(*obj, _xml));
    }
//case 4: <Class><Element1><Element2>...</Element2></Element1></Class>
    else if constexpr (is_class<T>::value)
    {
        _xml_elem = _xml.NewElement("class");
        traversal_tuple<0>(obj, _xml_elem, _xml);
    }
//case 5: <Arithmetic>value</Arithmetic>
    else
    {
        _xml_elem = _xml.NewElement("hasOutputMethod: Arithmetic or char");
        static_assert(hasOutputMethod<T>::value, "Invalid type!");
        _xml_elem->SetText(obj);
    }
    return _xml_elem;
}

template <size_t Index, typename T>
void xmlSerial::Serialization::traversal_tuple(const T& obj, XMLElem _xml_elem, docType _xml)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto element = get<Index>(obj);
        _xml_elem->InsertEndChild(__serialize(element, _xml));
        traversal_tuple<Index + 1>(obj,_xml_elem, _xml);
    }
}



//xml deserialization


template<typename T>
void xmlSerial::Deserialization::Deserialize(T& obj, string dir, bool bin)
{
    tinyxml2::XMLDocument _xml;
    if (!bin)
        _xml.LoadFile(dir.c_str());
    else
    {
        char* str = decode_base64(dir);
        _xml.Parse(str);
    }
    XMLElem root = _xml.RootElement();
    __deserialize(obj, root->FirstChildElement());
}

template <size_t Index, typename T>
void xmlSerial::Deserialization::traversal_tuple(T& obj, XMLElem _xml_elem)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto &element = get<Index>(obj);
        __deserialize(element, _xml_elem);
        //NextSiblingElement() won't be nullptr if size is correct
        traversal_tuple<Index + 1>(obj, _xml_elem->NextSiblingElement());
    }
}

template<typename T>
void xmlSerial::Deserialization::__deserialize(T& obj, XMLElem _xml_elem)
{
//case 1: _xml_elem is string, need to Gettext()
    if constexpr (is_same<T, string>::value)
    {
        // if (strcmp(_xml_elem->Name(), "string"))
        // {
        //     throw invalid_argument("xmlSerial::Deserialization argument invalid! _xml_elem Is not a string!");
        // }

        obj = _xml_elem->GetText();
        return;
    }
//case 2: _xml_elem is container need to get values from children by FirstChildElement() and NextSiblingElement()
    else if constexpr (isContainer<T>::value)
    {
        // if (strcmp(_xml_elem->Name(), "container"))
        // {
        //     throw invalid_argument("xmlSerial::Deserialization argument invalid! _xml_elem Is not a container!");
        // }

        XMLElem temp = _xml_elem->FirstChildElement();
        while (temp != nullptr)
        {
            typename T::value_type value;
            __deserialize(value, temp);
            append(obj, value);
            temp = temp->NextSiblingElement();
        }
    }
//case 3: _xml_elem is a pointer, need FirstChildElement() to get element.
    else if constexpr (isPointer<T>::value)
    {
        // if (strcmp(_xml_elem->Name(), "pointer"))
        // {
        //     throw invalid_argument("xmlSerial::Deserialization argument invalid! _xml_elem Is not a pointer!");
        // }

        XMLElem temp = _xml_elem->FirstChildElement();
        __deserialize(*obj, temp);
    }
//case 4: _xml_elem is a class, need to get values from children in function traversal_tuple().
    else if constexpr (is_class<T>::value)
    {
        // if (strcmp(_xml_elem->Name(), "class"))
        // {
        //     throw invalid_argument("xmlSerial::Deserialization argument invalid! _xml_elem Is not a class!");
        // }

        XMLElem temp = _xml_elem->FirstChildElement();
        traversal_tuple<0>(obj, temp);
    }
//case 5: _xml_elem has output method.
    else
    {
        // if (strcmp(_xml_elem->Name(), "hasOutputMethod: Arithmetic or char"))
        // {
        //     throw invalid_argument("xmlSerial::Deserialization argument invalid! _xml_elem doesn't have Output Method!");
        // }

        static_assert(hasOutputMethod<T>::value, "Invalid type!");
        string temp = _xml_elem->GetText();

        obj = convert<T>(temp);
    }
}


#endif