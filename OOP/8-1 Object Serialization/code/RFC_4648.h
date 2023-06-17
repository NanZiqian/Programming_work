#ifndef RFC_4648_H
#define RFC_4648_H

#include<bits/stdc++.h>

using namespace std;

static const string base64_arr = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

/// @brief Encode a string by the RFC 4648 standard
/// @param str the string to get encoded
/// @param dir the path of the file
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

/// @brief Decode a base64 string according to the RFC 4648 standard.
/// @param dir the path of the file
/// @return the decoded string
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



#endif