#ifndef _SERIALIZATION_H
#define _SERIALIZATION_H

#include "TypeJudging.h"
using namespace std;

//Declaration is this file
//Implementation in Serialization.cpp

namespace binSerial {

    class Serialization{
    public:
        template <typename T>
        static void Serialize(const T &obj, string dir);

    private:
        template <typename T>
        static void write(ofstream& out, const T &obj);

        template <size_t Index, typename T>
        static void travelsal_tuple(ofstream& out, const T& tuple);

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
        static void travelsal_tuple(ifstream& in, T& tuple);

        template <typename T>
        static void __deserialize(ifstream &in, T &obj);
    };
}

#include "tinyxml2.h"
#include "RFC_4648.h"
using XMLElem = tinyxml2::XMLElement*;
using docType = tinyxml2::XMLDocument&;

namespace xmlSerial {
    class Serialization{
        template <typename T>
        static void Serialize(const T &obj, string name, string dir, bool bin_mode);
        
        template <size_t Index, typename T>
        static void travelsal_tuple(const T& tuple, XMLElem ptr, docType xmlDoc);

        template<typename T>
        static XMLElem __serialize(const T& obj, docType xmlDoc);
    };

    class Deserialization{
        template <typename T>
        static void DeSerialize(T &obj, string name, string dir, bool bin_mode);

        template <size_t Index, typename T>
        static void travelsal_tuple(T& tuple, XMLElem ptr);

        template<typename T>
        static void __deserialize(T& obj, XMLElem xmlElement);
    };
}



#include "Serialization.cpp"
#endif