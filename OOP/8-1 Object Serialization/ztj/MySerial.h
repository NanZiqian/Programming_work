#ifndef _MySerial_h
#define _MySerial_h

//The header file that contains all definitions of 
//the functions used for serialization and deserialization.

#include <bits/stdc++.h>

using namespace std;

namespace binSerial {

    class Serialization {

        /**
         * @brief Write a union type object to a stream. 
         * 
         * @tparam T 
         * @param out the output file stream
         * @param obj the union type object
         */
        template <typename T>
        static void write_bin(ofstream& out, const T &obj);

        /**
         * @brief The recursive function to process a tuple
         * and serialize all its members.
         * 
         * @tparam Index now processing the Index-th member
         * @tparam T 
         * @param out the output file stream
         * @param tuple a tuple-like object
         */
        template <size_t Index, typename T>
        static void __proc_tuple(ofstream& out, const T& tuple);


        /**
         * @brief Recursively serialize an object.
         * 
         * @tparam T 
         * @param out the output file stream
         * @param obj the object we need to serialize
         */
        template <typename T>
        static void __serialize(ofstream& out, const T &obj);

    public:

        /**
         * @brief Serialize an object to a binary file
         * 
         * @tparam T 
         * @param obj the object
         * @param dir the path of the binary file
         */
        template <typename T>
        static void Serialize(const T &obj, string dir);
    };

    class Deserialization {
        
        /**
         * @brief Read an object from the binary file.
         * 
         * @tparam T 
         * @param in the input file stream
         * @param obj the place where you store the
         * read object
         */
        template <typename T>
        static void read_bin(ifstream &in, T &obj);

        /**
         * @brief The recursive function to process a tuple
         * and deserialize all its members.
         * 
         * @tparam Index now processing the Index-th member
         * @tparam T 
         * @param in the input file stream
         * @param tuple a tuple-like object
         */
        template <size_t Index, typename T>
        static void __proc_tuple(ifstream& in, T& tuple);

        /**
         * @brief Recursively deserialize an object
         * 
         * @tparam T 
         * @param in the input file stream
         * @param obj the object where we store the
         * deserialization result
         */
        template <typename T>
        static void __deserialize(ifstream &in, T &obj);

    public:

        /**
         * @brief Deserialize an object from the binary
         *  file.
         * 
         * @tparam T 
         * @param obj the object where we store the
         * deserialization result
         * @param dir the path of the binary file
         */
        template <typename T>
        static void Deserialize(T &obj, string dir);
    };
}

#include "tinyxml2.h"
using pNode = tinyxml2::XMLElement*;
using docType = tinyxml2::XMLDocument&;

namespace xmlSerial {

    class Serialization {
        
        /**
         * @brief The recursive function to process a tuple
         * and serialize all its members.
         * 
         * @tparam Index now processing the Index-th member
         * @tparam T 
         * @param tuple the tuple being serialized
         * @param ptr the XMLElement pointer used to store the
         * tuple
         * @param xmlDoc the XMLDocument previously created
         */
        template <size_t Index, typename T>
        static void __proc_tuple(const T& tuple, pNode ptr, docType xmlDoc);

        /**
         * @brief Recursively serialize an object.
         * 
         * @tparam T 
         * @param obj the object being serialized
         * @param xmlDoc the XMLDocument previously created
         * @return the XMLElement pointer that stores the
         * result of the serialization of the current object
         */
        template<typename T>
        static pNode __serialize(const T& obj, docType xmlDoc);

    public:
        /**
         * @brief Serialize an object in xml form.
         * (SUPPORTS BINARY MODE)
         * 
         * @tparam T 
         * @param obj the object being serialized
         * @param name the name of the xml root element
         * @param dir the path of the xml file
         * @param bin_mode whether to serialize in binary
         *  mode (base64)
         */
        template <typename T>
        static void Serialize_xml(const T &obj, string name, string dir, bool bin_mode);
    };

    class Deserialization {

        /**
         * @brief The recursive function to process a tuple
         * and deserialize all its members.
         * 
         * @tparam Index now processing the Index-th member
         * @tparam T 
         * @param tuple a tuple-like object
         * @param ptr the XMLElement pointer that stores the
         * current memeber
         */
        template <size_t Index, typename T>
        static void __proc_tuple(T& tuple, pNode ptr);

        /**
         * @brief Recursively deserialize an object
         * 
         * @tparam T 
         * @param obj the object where we store the
         * deserialization result
         * @param xmlElement the XMLElement pointer that
         * stores the current member
         */
        template<typename T>
        static void __deserialize(T& obj, pNode xmlElement);

    public:
        /**
         * @brief Deserialize an object from a xml file.
         * (SUPPORTS BINARY MODE)
         * 
         * @tparam T 
         * @param obj the object where we store the
         * deserialization result
         * @param name the name of the xml root element
         * @param dir the path of the xml file
         * @param bin_mode whether to deserialize in binary
         * mode (base64)
         */
        template <typename T>
        static void Deserialize_xml(T &obj, string name, string dir, bool bin_mode);
    };
}

//self-designed class
#include "prepSerial.h"

//realization
#include "MySerial.cpp"
#endif