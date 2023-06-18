#include "MySerial.h"

using namespace std;

/**
 * @brief Some traits class and functions that will be
 * of use in the realizations of the functions in
 * `MySerial.h`
 * 
 */
namespace Utility {
    template<typename T>
    class hasOutputMethod
    {
        template<typename C>
        static constexpr auto check(C*)
        -> typename is_same<
            ostream&,
            decltype(declval<ostream&>() << declval<C>())
        >::type;

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
    class hasPushback {
        template<typename C>
        static constexpr auto check(C* container)
        -> decltype(container->push_back(declval<typename C::value_type>()), true_type());

        template<typename C>
        static constexpr false_type check(...);
    public:
        static constexpr bool value = decltype(check<T>(nullptr))::value;
    };

    /**
     * @brief Insert a value at the end of a container object.
     * 
     * @tparam T 
     * @param obj the container object
     * @param x the value
     */
    template <typename T>
    void append(T &obj, const typename T::value_type &x)
    {
        if constexpr (hasPushback<T>::value)
            obj.push_back(x);
        else
            obj.insert(x);
    }
    



    static const string base64_arr = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    /**
     * @brief Encode a string by the RFC 4648 standard
     * and write the encoded string to a certain file.
     * 
     * @param str the string to be encoded
     * @param dir the path of the file
     */
    void encode_base64(const char* str, string dir)//RFC 4648
    {
        int n = strlen(str), cur = 0;
        string out_str;
        int pad_len = (n + 2) / 3 * 3, pad = pad_len - n;

        char ch[3];
        for (int i = 0; i < pad_len; i++)
        {
            ch[cur++] = (i < n ? str[i] : 0);
            if (cur == 3)
            {
                char idx[4] = {
                    (ch[0] >> 2), 
                    ((ch[0] & 3) << 4) | (ch[1] >> 4),
                    ((ch[1] & 0xf) << 2) | (ch[2] >> 6),
                    (ch[2] & 0x3f)
                };
                int bound = (i >= n ? 4 - pad : 4);
                for (int j = 0; j < bound; j++)
                    out_str += base64_arr[idx[j]];
                cur = 0;
            }
        }
        for (int i = 0; i < pad; i++) out_str += '=';
        ofstream out(dir);
        out << out_str << endl;
    }

    /**
     * @brief Decode a base64 string according to the
     * RFC 4648 standard.
     * 
     * @param dir the path of the file
     * @return the decoded string
     */
    char* decode_base64(string dir)
    {
        ifstream in(dir);
        string ori; in >> ori;
        if (ori.size() % 4 != 0)
        {
            throw ios::failure("File format not base64!");
        }

        char* str = new char[ori.size() / 4 * 3 + 1];
        vector<char> inv(256, -1);
        for (int i = 0; i < 64; i++)
            inv[base64_arr[i]] = i;
        int cur = 0;
        for (int i = 0; i < ori.size(); i += 4)
        {
            char val[4];
            for (int j = 0; j < 4; j++)
                val[j] = (ori[i + j] != '=' ? inv[ori[i + j]] : 0);
            char ch[3] = {
                (val[0] << 2) | (val[1] >> 4),
                ((val[1] & 0xf) << 4) | (val[2] >> 2),
                ((val[2] & 3) << 6) | val[3]
            };
            for (int j = 0; j < 3; j++)
                str[cur++] = ch[j];
        }
        str[cur++] = '\0';
        return str;
    }
}


//binSerial


template <typename T>
void binSerial::Serialization::write_bin(ofstream& out, const T &obj)
{
    out.write((char *)(&obj), sizeof(obj));
}

template <size_t Index, typename T>
void binSerial::Serialization::__proc_tuple(ofstream& out, const T& tuple)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto element = get<Index>(tuple);
        __serialize(out, element);
        __proc_tuple<Index + 1>(out, tuple);
    }
}


template <typename T>
void binSerial::Serialization::__serialize(ofstream& out, const T &obj)
{
    write_bin(out, typeid(obj).hash_code());
    if constexpr (Utility::isContainer<T>::value)
    {
        write_bin(out, obj.size());
        typedef typename T::value_type type;
        if constexpr (is_class<type>::value)
        {
            for (auto p: obj)
                __serialize(out, p);
        }
        else
        {
            write_bin(out, typeid(type).hash_code());
            for (auto p: obj)
                write_bin(out, p);
        }
    }
    else if constexpr (Utility::isPointer<T>::value)
    {
        __serialize(out, *obj);
    }
    else if constexpr (is_class<T>::value)
    {
        //should be tuple-like
        auto size = tuple_size<T>::value;
        write_bin(out, size);
        __proc_tuple<0>(out, obj);
    }
    else
    {
        static_assert(Utility::hasOutputMethod<T>::value, "Invalid type!");
        write_bin(out, obj);
    }
}


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





template <typename T>
void binSerial::Deserialization::read_bin(ifstream &in, T &obj)
{
    in.read((char *)&obj, sizeof(T));
}

template <size_t Index, typename T>
void binSerial::Deserialization::__proc_tuple(ifstream& in, T& tuple)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto &element = get<Index>(tuple);
        __deserialize(in, element);
        __proc_tuple<Index + 1>(in, tuple);
    }
}

template <typename T>
void binSerial::Deserialization::__deserialize(ifstream &in, T &obj)
{
    size_t hash;
    read_bin(in, hash);
    if (hash != typeid(T).hash_code())
    {
        throw invalid_argument("binSerial::Deserialization argument invalid!");
    }
    if constexpr (Utility::isContainer<T>::value)
    {
        size_t size;
        read_bin(in, size);
        typedef typename T::value_type type;
        if constexpr (is_class<type>::value)
        {
            for (int i = 0; i < size; i++)
            {
                type tmp;
                __deserialize(in, tmp);
                Utility::append(obj, tmp);
            }
        }
        else
        {
            size_t hash2;
            read_bin(in, hash2);
            if (hash2 != typeid(type).hash_code())
            {
                throw invalid_argument("binSerial::Deserialization argument invalid!");
            }
            for (int i = 0; i < size; i++)
            {
                type tmp;
                read_bin(in, tmp);
                Utility::append(obj, tmp);
            }
        }
    }
    else if constexpr (Utility::isPointer<T>::value)
    {
        auto &tarObj = *obj;
        __deserialize(in, tarObj);
    }
    else if constexpr (is_class<T>::value)
    {
        size_t size;
        read_bin(in, size);
        __proc_tuple<0>(in, obj);
    }
    else
    {
        static_assert(Utility::hasOutputMethod<T>::value, "Invalid type!");
        read_bin(in, obj);
    }
}

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





//xmlSerial


template <size_t Index, typename T>
void xmlSerial::Serialization::__proc_tuple(const T& tuple, pNode ptr, docType xmlDoc)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto element = get<Index>(tuple);
        ptr->InsertEndChild(__serialize(element, xmlDoc));
        __proc_tuple<Index + 1>(tuple, ptr, xmlDoc);
    }
}

template<typename T>
pNode xmlSerial::Serialization::__serialize(const T& obj, docType xmlDoc)
{
    pNode ret;
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
        __proc_tuple<0>(obj, ret, xmlDoc);
    }
    else
    {
        ret = xmlDoc.NewElement("value");
        static_assert(Utility::hasOutputMethod<T>::value, "Invalid type!");
        ret->SetText(obj);
    }
    return ret;
}




template<typename T>
void xmlSerial::Serialization::Serialize_xml(const T &obj, string name, string dir, bool bin_mode)
{
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLElement* rootElement = xmlDoc.NewElement(name.c_str());
    xmlDoc.InsertEndChild(rootElement);

    tinyxml2::XMLElement* serializedElement = __serialize(obj, xmlDoc);
    if (serializedElement)
    {
        rootElement->InsertEndChild(serializedElement);
    }
    if (!bin_mode)
        xmlDoc.SaveFile(dir.c_str());
    else
    {
        tinyxml2::XMLPrinter* Printer = new tinyxml2::XMLPrinter;
        xmlDoc.Print(Printer);
        Utility::encode_base64(Printer->CStr(), dir);
    }
}

template <size_t Index, typename T>
void xmlSerial::Deserialization::__proc_tuple(T& tuple, pNode ptr)
{
    if constexpr (Index < tuple_size_v<T>)
    {
        auto &element = get<Index>(tuple);
        __deserialize(element, ptr);
        __proc_tuple<Index + 1>(tuple, ptr->NextSiblingElement());
    }
}

template<typename T>
void xmlSerial::Deserialization::__deserialize(T& obj, pNode xmlElement)
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

        pNode nElement = xmlElement->FirstChildElement();
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

        pNode nElement = xmlElement->FirstChildElement();
        __deserialize(*obj, nElement);
    }
    else if constexpr (is_class<T>::value)
    {
        if (strcmp(xmlElement->Name(), "tuple"))
        {
            throw invalid_argument("xmlSerial::Deserialization argument invalid!");
        }

        pNode nElement = xmlElement->FirstChildElement();
        __proc_tuple<0>(obj, nElement);
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
void xmlSerial::Deserialization::Deserialize_xml(T &obj, string name, string dir, bool bin_mode)
{
    tinyxml2::XMLDocument xmlDoc;
    if (!bin_mode)
        xmlDoc.LoadFile(dir.c_str());
    else
    {
        char *str = Utility::decode_base64(dir);
        xmlDoc.Parse(str);
    }
    pNode root = xmlDoc.RootElement();
    if (string(root->Name()) != name)
    {
        throw ios::failure("xmlSerial::Deserialization argument invalid!");
    }
    __deserialize(obj, root->FirstChildElement());
}
