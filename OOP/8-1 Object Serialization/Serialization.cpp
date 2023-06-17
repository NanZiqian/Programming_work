#ifndef _SERIALIZATION_CPP
#define _SERIALIZATION_CPP


#include "Serialization.h"

using namespace std;



//binary serialization


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
        travelsal_tuple<0>(out, obj);
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
void binSerial::Serialization::travelsal_tuple(ofstream& out, const T& tuple)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto & element = get<Index>(tuple);
        __serialize(out, element);
        travelsal_tuple<Index + 1>(out, tuple);
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
void binSerial::Deserialization::travelsal_tuple(ifstream& in, T& tuple)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto &element = get<Index>(tuple);
        __deserialize(in, element);
        travelsal_tuple<Index + 1>(in, tuple);
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
            typename T::value_type tmp;
            __deserialize(in, tmp);
            append(obj, tmp);
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
        travelsal_tuple<0>(in, obj);
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
/// @param bin_mode whether to use base64 binary mode to store xml
template<typename T>
void xmlSerial::Serialization::Serialize(const T &obj, string rootname, string dir, bool bin_mode)
{
//Preparation. Create a new empty xml file
    tinyxml2::XMLDocument _xml;
    //<?xml version="1.0" encoding="UTF-8"?>
    tinyxml2::XMLDeclaration* declaration = _xml.NewDeclaration();
    _xml.InsertFirstChild(declaration);
    tinyxml2::XMLElement* root = _xml.NewElement(rootname.c_str());
    _xml.InsertEndChild(root);

//Serialization and insert them to root element "rootname.c_str()"
    tinyxml2::XMLElement* _xml_element = __serialize(obj, _xml);
    if (_xml_element)
    {
        root->InsertEndChild(_xml_element);
    }
    //
    if (!bin_mode)
        xmlDoc.SaveFile(dir.c_str());
    else
    {
        tinyxml2::XMLPrinter* Printer = new tinyxml2::XMLPrinter;
        xmlDoc.Print(Printer);
        encode_base64(Printer->CStr(), dir);
    }
}

/// @brief Serialize an object and transform it to XMLElem
/// @tparam T 
/// @param obj 
/// @param xmlDoc 
/// @return 
template<typename T>
XMLElem xmlSerial::Serialization::__serialize(const T& obj, docType xmlDoc)
{
    XMLElem ret;
    if constexpr (is_same<T, string>::value)
    {
        ret = xmlDoc.NewElement("string");
        ret->SetText(obj.c_str());
        return ret;
    }
    else if constexpr(Utility::isContainer<T>::value)
    {
        ret = xmlDoc.NewElement("container");
        auto size = obj.size();
        for (auto p: obj)
            ret->InsertEndChild(__serialize(p, xmlDoc));
    }
    else if constexpr (Utility::isPointer<T>::value)
    {
        ret = xmlDoc.NewElement("pointer");
        ret->InsertEndChild(__serialize(*obj, xmlDoc));
    }
    else if constexpr (is_class<T>::value)
    {
        ret = xmlDoc.NewElement("tuple");
        travelsal_tuple<0>(obj, ret, xmlDoc);
    }
    else
    {
        ret = xmlDoc.NewElement("value");
        static_assert(Utility::hasOutputMethod<T>::value, "Invalid type!");
        ret->SetText(obj);
    }
    return ret;
}

template <size_t Index, typename T>
void xmlSerial::Serialization::travelsal_tuple(const T& tuple, XMLElem ptr, docType xmlDoc)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto element = get<Index>(tuple);
        ptr->InsertEndChild(__serialize(element, xmlDoc));
        travelsal_tuple<Index + 1>(tuple, ptr, xmlDoc);
    }
}



//xml deserialization


template <size_t Index, typename T>
void xmlSerial::Deserialization::travelsal_tuple(T& tuple, XMLElem ptr)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto &element = get<Index>(tuple);
        __deserialize(element, ptr);
        travelsal_tuple<Index + 1>(tuple, ptr->NextSiblingElement());
    }
}

template<typename T>
void xmlSerial::Deserialization::__deserialize(T& obj, XMLElem xmlElement)
{
    if constexpr (is_same<T, string>::value)
    {
        if (strcmp(xmlElement->Name(), "string"))
        {
            throw invalid_argument("xmlSerial::Deserialization argument invalid!");
        }

        obj = xmlElement->GetText();
        return;
    }
    else if constexpr (Utility::isContainer<T>::value)
    {
        if (strcmp(xmlElement->Name(), "container"))
        {
            throw invalid_argument("xmlSerial::Deserialization argument invalid!");
        }

        XMLElem nElement = xmlElement->FirstChildElement();
        while (nElement != nullptr)
        {
            typename T::value_type tmp;
            __deserialize(tmp, nElement);
            Utility::append(obj, tmp);
            nElement = nElement->NextSiblingElement();
        }
    }
    else if constexpr (Utility::isPointer<T>::value)
    {
        if (strcmp(xmlElement->Name(), "pointer"))
        {
            throw invalid_argument("xmlSerial::Deserialization argument invalid!");
        }

        XMLElem nElement = xmlElement->FirstChildElement();
        __deserialize(*obj, nElement);
    }
    else if constexpr (is_class<T>::value)
    {
        if (strcmp(xmlElement->Name(), "tuple"))
        {
            throw invalid_argument("xmlSerial::Deserialization argument invalid!");
        }

        XMLElem nElement = xmlElement->FirstChildElement();
        travelsal_tuple<0>(obj, nElement);
    }
    else
    {
        if (strcmp(xmlElement->Name(), "value"))
        {
            throw invalid_argument("xmlSerial::Deserialization argument invalid!");
        }

        static_assert(Utility::hasOutputMethod<T>::value, "Invalid type!");
        string str = xmlElement->GetText();
        stringstream ss;
        ss << str;
        ss >> obj;
    }
}

template<typename T>
void xmlSerial::Deserialization::DeSerialize(T &obj, string name, string dir, bool bin_mode)
{
    tinyxml2::XMLDocument xmlDoc;
    if (!bin_mode)
        xmlDoc.LoadFile(dir.c_str());
    else
    {
        char *str = Utility::decode_base64(dir);
        xmlDoc.Parse(str);
    }
    XMLElem root = xmlDoc.RootElement();
    if (string(root->Name()) != name)
    {
        throw ios::failure("xmlSerial::Deserialization argument invalid!");
    }
    __deserialize(obj, root->FirstChildElement());
}

#endif