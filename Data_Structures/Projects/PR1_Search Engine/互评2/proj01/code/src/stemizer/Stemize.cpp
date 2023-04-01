#include "Stemize.h"
using namespace std;

/// @brief This Function removes all the non-letter chars on the left side of the word.
string Clear_Left_Side(string word)
{
    if (word.size())
    {
        if (!Is_Char(word[0])) /// Judge whether or not the first char is a letter.
        {
            word.erase(0, 1);
            word = Clear_Left_Side(word); /// Recursively to remove all the useless chars.
        }
    }
    return word;
}

/// @brief This Function removes all the non-letter chars on the right side of the word.
string Clear_Right_Side(string word)
{
    if (word.size())
    {
        if (!Is_Char(word[word.size() - 1])) /// Judge whether or not the last char is a letter.
        {
            word.erase(word.size() - 1, 1);
            word = Clear_Right_Side(word); /// Recursively to remove all the useless chars.
        }
    }
    return word;
}

/// @brief This function stem the word with the help of stmr lib.
string stemize(string word)
{
    word = Clear_Left_Side(word);  /// This Function removes all the non-letter chars on the left side of the word.
    word = Clear_Right_Side(word); /// This Function removes all the non-letter chars on the right side of the word.
    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z') /// Case-insensitive.
        {
            word[i] = word[i] - 'A' + 'a';
        }
    }
    char word_[word.size() + 1];
    strcpy(word_, word.c_str());             /// transform a varible of string type into char[] type
    int k = stem(word_, 0, word.size() - 1); /// The definition and explanation of stem() is in stmr.c.
    word = word_;                            /// transform a varible of char[] type into string type
    word.resize(k + 1);
    word = Clear_Right_Side(word); /// After the stemize, some inside useless chars may be exposed, this condition almost only occurs on the right side.
    return word;
}