#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "../stemizer/Stemize.h"
using namespace std;

string Base_Dir("../dataset");

static vector<string> Stop_Word_List; // Stop_Word_List contains all the stop words.

vector<string> Generate_All_Path();                                                                           /// This function generates the relative paths of all the scenes and poetries, and return the vector of these paths.
void Stop_Word_Analysis(vector<string> &Paths);                                                               /// This function sorts words by frequency and writes the result into Word_Count.txt for human analysis.
void Build_Stop_Word_List();                                                                                  /// This function fills the static global varible, Stop_Word_List, with Stop_Word_List.txt.
void Generate_Inverted_File_Index(map<string, map<string, int> > &Inverted_File_Index, vector<string> &Paths); /// This function generates the inverted file index we want and stores it in Inverted_File_Index.
void Output_Inverted_File_Index(map<string, map<string, int> > &Inverted_File_Index);                          /// This function prints the inverted file index into Inverted_File_Index.txt.

int main(int argc, char * argv[])
{
    if(argc != 3 || strcmp(argv[1], "-D") != 0 )
    {
        cout << "please use: [ ./app.exe -D <baseDir2Dataset> ]" << endl;
        return 0;
    }
    else
    {
        Base_Dir = argv[2];
    }


    vector<string> Paths = Generate_All_Path();
    vector<string> &ref_Paths = Paths;
    /// g++ -D Stop_Word preprocess.cpp stmr.c Stemize.cpp -o preprocess
#ifdef Stop_Word
    Stop_Word_Analysis(ref_Paths);
#endif
    /// g++ preprocess.cpp stmr.c Stemize.cpp -o preprocess
#ifndef Stop_Word
    Build_Stop_Word_List();
    map<string, map<string, int> > Inverted_File_Index;
    map<string, map<string, int> > &ref_Inverted_File_Index = Inverted_File_Index;
    Generate_Inverted_File_Index(ref_Inverted_File_Index, ref_Paths);
    Output_Inverted_File_Index(ref_Inverted_File_Index);
#endif
}

/// @brief This function provides the basic hierarchy of each Play: the maximum Scene id of each Act of each Play.
/// Why do we use such a complex expression, "the maximum Scene id", instead of the number of Scenes?
/// Because there are omissions in some Acts, and we treat "Prologue" as Scene0.
/// For example, File_Basic_Info["Taming of the Shrew"] = {2, 2, 1, 2, 5, 2}; means that "Taming of the Shrew" has 6 acts,
/// Induction (Act0), Act1, Act3, Act5 have 2 scenes, Act2 has 1 scene, Act4 has 5 scenes.
/// The basic hierarchy of Poetry is not defined here, because they don't have Act and Scene.
void Build_Basic_Hierarchy(map<string, vector<int> > &File_Basic_Info)
{
    File_Basic_Info["All's Well That Ends Well"] = {0, 3, 5, 7, 5, 3};
    File_Basic_Info["As You Like It"] = {0, 3, 7, 5, 3, 4};
    File_Basic_Info["The Comedy of Errors"] = {0, 2, 2, 2, 4, 1};
    File_Basic_Info["Cymbeline"] = {0, 6, 5, 7, 4, 5};
    File_Basic_Info["Love's Labours Lost"] = {0, 2, 1, 1, 3, 2};
    File_Basic_Info["Measure for Measure"] = {0, 4, 4, 2, 6, 1};
    File_Basic_Info["The Merry Wives of Windsor"] = {0, 4, 3, 5, 6, 5};
    File_Basic_Info["The Merchant of Venice"] = {0, 3, 9, 5, 2, 1};
    File_Basic_Info["A Midsummer Night's Dream"] = {0, 2, 2, 2, 2, 1};
    File_Basic_Info["Much Ado About Nothing"] = {0, 3, 3, 5, 2, 4};
    File_Basic_Info["Pericles, Prince of Tyre"] = {0, 4, 5, 4, 6, 3};
    File_Basic_Info["Taming of the Shrew"] = {2, 2, 1, 2, 5, 2};
    File_Basic_Info["The Tempest"] = {0, 2, 2, 3, 1, 1};
    File_Basic_Info["Troilus and Cressida"] = {0, 3, 3, 3, 5, 10};
    File_Basic_Info["Twelfth Night"] = {0, 5, 5, 4, 3, 1};
    File_Basic_Info["Two Gentlemen of Verona"] = {0, 3, 7, 2, 4, 4};
    File_Basic_Info["Winter's Tale"] = {0, 2, 3, 3, 4, 3};
    File_Basic_Info["Henry IV, part 1"] = {0, 3, 4, 2, 4, 5};
    File_Basic_Info["Henry IV, part 2"] = {0, 3, 4, 2, 5, 5};
    File_Basic_Info["Henry V"] = {0, 2, 4, 7, 8, 2};
    File_Basic_Info["Henry VI, part 1"] = {0, 6, 5, 4, 7, 5};
    File_Basic_Info["Henry VI, part 2"] = {0, 4, 4, 3, 10, 3};
    File_Basic_Info["Henry VI, part 3"] = {0, 4, 6, 3, 8, 7};
    File_Basic_Info["Henry VIII"] = {0, 4, 4, 2, 2, 5};
    File_Basic_Info["King John"] = {0, 1, 1, 4, 3, 7};
    File_Basic_Info["Richard II"] = {0, 4, 4, 4, 1, 6};
    File_Basic_Info["Richard III"] = {0, 4, 4, 7, 5, 5};
    File_Basic_Info["Antony and Cleopatra"] = {0, 5, 7, 13, 15, 2};
    File_Basic_Info["Coriolanus"] = {0, 10, 3, 3, 7, 6};
    File_Basic_Info["Hamlet"] = {0, 5, 2, 4, 7, 2};
    File_Basic_Info["Julius Caesar"] = {0, 3, 4, 3, 3, 5};
    File_Basic_Info["King Lear"] = {0, 5, 4, 7, 7, 3};
    File_Basic_Info["Macbeth"] = {0, 7, 4, 6, 3, 8};
    File_Basic_Info["Othello"] = {0, 3, 3, 4, 3, 2};
    File_Basic_Info["Romeo and Juliet"] = {0, 5, 6, 5, 5, 3};
    File_Basic_Info["Timon of Athens"] = {0, 2, 2, 6, 3, 4};
    File_Basic_Info["Titus Andronicus"] = {0, 1, 4, 2, 4, 3};
}

/// @brief This function generates the relative paths of all the scenes and poetries, and return the vector of these paths.
/// @attention: scene is the storage unit of a play.
vector<string> Generate_All_Path()
{
    /// File_Basic_Info contains the basic hierarchy of each play.
    /// The meaning of the map<string, vector<int> > data type is explained in Build_Basic_Hierarchy() function.
    map<string, vector<int> > File_Basic_Info;
    map<string, vector<int> > &ref_File_Basic_Info = File_Basic_Info;
    Build_Basic_Hierarchy(File_Basic_Info);

    /// Paths contains the relative paths of all the scenes and poetries.
    vector<string> Paths;
    string Path;
    for (auto Now_File = File_Basic_Info.begin(); Now_File != File_Basic_Info.end(); Now_File++)
    {
        /// Now_File->first is a string varible, which contains the name of a certain play
        /// Now_File->second is a vector<int> varible, which contains the hierarchy of that certain play
        string File_Name = Now_File->first;
        string Act, Scene;
        for (int i = 0; i < Now_File->second.size(); i++) // traverse through all the Acts
        {
            if (Now_File->second[i] == 0) // if this Act doesn't contain any Scene, then just skip it
            {
                continue;
            }
            Act = "Act" + to_string(i);
            Act = (i == 0) ? "Induction" : Act;            // Act0 means Induction
            for (int j = 0; j <= Now_File->second[i]; j++) // traverse through all the Scenes of a certain Acts
            {
                Scene = "Scene" + to_string(j);
                Scene = (j == 0) ? "Prologue" : Scene;                            // Scene0 means Prologue
                Path = Base_Dir + "/" + File_Name + "/" + Act + "/" + Scene; // Concatenate all the strings to get the relative path
                Paths.push_back(Path);                                            // Add the new path to Paths
            }
            /// Obviously, this step would let some non-existent Scenes being added to Paths, but don't worry,
            /// these Scenes would be deleted later.
        }
    }
    for (int i = 1; i < 155; i++) /// There are 154 sonnets collected.
    {
        Path = Base_Dir + "/The Sonnets/" + to_string(i);
        Paths.push_back(Path);
    }
    /// There are still 4 poetries left.
    Paths.push_back(Base_Dir + "/A Lover's Complaint");
    Paths.push_back(Base_Dir + "/The Rape of Lucrece");
    Paths.push_back(Base_Dir + "/Venus and Adonis");
    Paths.push_back(Base_Dir + "/Funeral Elegy");
    return Paths;
}

/// @brief This function count the frequency of all the words presented in Shakespeare's plays and poetries, and stores these information into Word_List.
/// @param Paths contains the relative paths of all the scenes and poetries.
/// @param Word_List contains words and its corresponding frequencies.
/// For example, Word_List["lord"] = x means that the word "lord" presents for x times.
void Count_All_Words(vector<string> &Paths, map<string, int> &Word_List)
{
    ifstream input;
    for (int i = 0; i < Paths.size(); i++) /// Traverse through all the scenes and poetries.
    {
        input.open(Paths[i], ios::in);
        string word;
        while (input >> word) /// Read in the word till EOF.
        {
            if (word.size() < 2) /// Input of 0 or 1 char won't be calculated since it's meaningless.
            {
                continue;
            }
            /// Stem the word to make the result more precise.
            /// The definition and explanation of this function is in Stemize.cpp.
            word = stemize(word);
            if (word.size() < 2) /// Again, if, after stemizing, the input is of 0 or 1 char, it's also meaningless.
            {
                continue;
            }
            auto pword = Word_List.find(word);
            if (pword == Word_List.end()) /// If the word has't been in Word_List, append.
            {
                Word_List[word] = 1;
            }
            else /// If the word is already in Word_List, increase its frequency.
            {
                pword->second++;
            }
        }
        input.close();
    }
}

/// @brief This function is defined for later sort().
bool comp1(pair<string, int> &a, pair<string, int> &b)
{
    return a.second > b.second;
}

/// @brief This function sorts the Word_List by frequency in non-ascending order, and return the result.
/// @attention The data type of the input and output is different, because map doesn't support sorting based on value.
/// @param Word_List contains words and its corresponding frequencies.
/// @return Word_Frequency_List contains words and its corresponding frequencies in in non-ascending order.
vector<pair<string, int> > Sort_Word_By_Frequency(map<string, int> &Word_List)
{
    vector<pair<string, int> > Word_Frequency_List;
    pair<string, int> word_freq;
    for (auto pword = Word_List.begin(); pword != Word_List.end(); pword++) /// Transfrom the data from one type to another.
    {
        word_freq.first = pword->first;
        word_freq.second = pword->second;
        Word_Frequency_List.push_back(word_freq);
    }
    sort(Word_Frequency_List.begin(), Word_Frequency_List.end(), comp1); /// Sort
    return Word_Frequency_List;
}

/// @brief This function sorts words by frequency and writes the result into Word_Count.txt for human analysis.
/// @param Paths contains the relative paths of all the scenes and poetries.
void Stop_Word_Analysis(vector<string> &Paths)
{
    map<string, int> Word_List;
    map<string, int> &ref_Word_List = Word_List;
    /// This function count the frequency of all the words presented in Shakespeare's plays and poetries, and stores these information into Word_List.
    Count_All_Words(Paths, ref_Word_List);
    /// This function sorts the Word_List by frequency in non-ascending order, and return the result.
    vector<pair<string, int> > Word_Frequency_List = Sort_Word_By_Frequency(ref_Word_List);
    ofstream output;
    output.open("Word_Count.txt", ios::out);
    for (auto pword = Word_Frequency_List.begin(); pword != Word_Frequency_List.end(); pword++)
    {
        output << pword->first << " " << pword->second << endl;
    }
    output.close();
}

/// @brief This function fills the static global varible, Stop_Word_List, with Stop_Word_List.txt.
void Build_Stop_Word_List()
{
    ifstream input;
    input.open("Stop_Word_List.txt", ios::in);
    string word;
    while (input >> word)
    {
        Stop_Word_List.push_back(word);
    }
    input.close();
    sort(Stop_Word_List.begin(), Stop_Word_List.end()); /// Sort the stop words in lexicographical order to speed up later query.
}

/// @brief This function judges whether or not a word belongs to stop words.
/// @param word is the word to be checked.
/// @return true if the word belongs to stop words, else false.
bool Is_Stop(string word)
{
    return find(Stop_Word_List.begin(), Stop_Word_List.end(), word) != Stop_Word_List.end();
}

/// @brief This function generates the inverted file index we want and stores it in Inverted_File_Index.
/// @param Paths contains the relative paths of all the scenes and poetries.
/// @param Inverted_File_Index stores the results.
void Generate_Inverted_File_Index(map<string, map<string, int> > &Inverted_File_Index, vector<string> &Paths)
{
    ifstream input;
    string word;
    for (int i = 0; i < Paths.size(); ++i) /// Traverse through all the scenes and poetries.
    {
        input.open(Paths[i], ios::in);
        while (input >> word) /// Read in the word till EOF.
        {
            word = stemize(word);

            if (!word.size() || Is_Stop(word))
            {
                continue;
            }
            
            auto pid = Inverted_File_Index.find(word);
            if (pid == Inverted_File_Index.end()) /// If the word has't been in Inverted_File_Index, append.
            {
                /// Inverted_File_Index[word] contains all the files that contain word and their corresponding frequency.
                /// Inverted_File_Index[word][Paths[i]] contains the frequency of word in the file whose relative path is Paths[i].
                Inverted_File_Index[word][Paths[i]] = 1;
            }
            else /// If the word is already in Inverted_File_Index, increase its frequency.
            {
                pid->second[Paths[i]]++;
            }
            
        }
        input.close();
    }
}

/// @brief This function prints the inverted file index into Inverted_File_Index.txt.
void Output_Inverted_File_Index(map<string, map<string, int> > &Inverted_File_Index)
{
    ofstream output;
    output.open("Inverted_File_Index.txt", ios::out);
    for (auto pword = Inverted_File_Index.begin(); pword != Inverted_File_Index.end(); pword++) /// Traverse through all the words.
    {
        output << pword->first << endl;
        for (auto pfile = pword->second.begin(); pfile != pword->second.end(); pfile++) /// Traverse through all the files.
        {
            output << pfile->first.substr(Base_Dir.size() + 1) << endl;
            output << pfile->second << endl;
        }
        output << "#" << endl; /// We use "#" to denote the end of a certain word's index.
    }
    output.close();
}
