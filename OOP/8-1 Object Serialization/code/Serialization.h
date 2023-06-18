#ifndef _SERIALIZATION_H
#define _SERIALIZATION_H

#include "TypeJudging.h"
#include "tinyxml2.h"
using namespace std;

//Declaration is this file
//Implementation in Serialization.cpp




//namespace binSerial


namespace binSerial {

    class Serialization{
    public:
        template <typename T>
        static void Serialize(const T &obj, string dir);

    private:
        template <typename T>
        static void write(ofstream& out, const T &obj);

        template <size_t Index, typename T>
        static void traversal_tuple(ofstream& out, const T& tuple);

        template <typename T>
        static void __serialize(ofstream& out, const T &obj);

        
    };

    class Deserialization{
    public:
        template <typename T>
        static void Deserialize(T &obj, string dir);

    private:
        template <typename T>
        static void read(ifstream &in, T &obj);

        template <size_t Index, typename T>
        static void traversal_tuple(ifstream& in, T& tuple);

        template <typename T>
        static void __deserialize(ifstream &in, T &obj);
    };
}



//namespace xmlSerial


/// @brief to simplify the name.
using XMLElem = tinyxml2::XMLElement*;
using docType = tinyxml2::XMLDocument&;

namespace xmlSerial {
    class Serialization{
    public:
        template <typename T>
        static void Serialize(const T &obj, string rootname, string dir, bool bin);
    private:
        template <size_t Index, typename T>
        static void traversal_tuple(const T& obj, XMLElem _xml_elem, docType _xml);

        template<typename T>
        static XMLElem __serialize(const T& obj, docType _xml);
    };

    class Deserialization{
    public:
        template <typename T>
        static void Deserialize(T &obj, string dir, bool bin);

    private:
        template <size_t Index, typename T>
        static void traversal_tuple(T& obj, XMLElem _xml_elem);

        template<typename T>
        static void __deserialize(T& obj, XMLElem _xml_elem);
    };
}



#include "Serialization.cpp"
#endif