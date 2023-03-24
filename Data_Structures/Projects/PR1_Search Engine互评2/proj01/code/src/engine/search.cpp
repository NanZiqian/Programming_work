#include "search.h"
#include "../stemizer/Stemize.h"
#include <cstdio>
#include <cassert>

using std::pair;
using std::make_pair;
using std::sort;

Corpus::Corpus() {
    string directoryPath = ".";
    indices = ReadInvertedFileIndex(directoryPath);
}

Corpus::Corpus(const string &directoryPath) {
    indices = ReadInvertedFileIndex(directoryPath);
}

void Corpus::Read(const string &directoryPath) {
    indices = ReadInvertedFileIndex(directoryPath);
}

#include <iostream>
#include <fstream>
#include <string.h>
using std::ifstream;
using std::cout;
using std::endl;

/**
 * @brief Read the inverted file index from the disk.
 * 
 * @param directoryPath 
 * @return ** map<string, FileIndex> 
 */
map<string, FileIndex> Corpus::ReadInvertedFileIndex(const string &directoryPath) {
    map<string, FileIndex> ret;

    string path = directoryPath + "/Inverted_File_Index.txt";
    ifstream file(path);

    if (!file.is_open()) {
        cout << "Fatal Error" << path << " not Found."<< endl;
        exit(1);
    }

    const int size_ = 100;
    char word[size_], sec[size_];
    int cnt;

    while (!file.eof()) {
        file.getline(word, size_);

        if (strlen(word) == 0) {
            break;
        }
        
        map<string, int> count;
        while (true) {
            file.getline(sec, size_);

            if (sec[0] == '#') {
                break;
            }

            file >> cnt;
            file.get();
            count[sec] = cnt;
        }

        ret[word] = (FileIndex){0, count};
    }

    string path_c = directoryPath + "/Word_Count.txt";
    ifstream file_c(path_c);

    if (!file_c.is_open()) {
        cout << "Fatal Error" << path << " not Found."<< endl;
        exit(1);
    }

    int sum;
    while (!file_c.eof()) {
        file_c >> word >> sum;
        file_c.get();

        if (strlen(word) == 0) {
            break;
        }

        if (ret.find(word) != ret.end()) {
            ret[word].countTotal = sum;
        }
    }

    return ret;
}

/**
 * @brief Deduplicate the locations of the keywords.
 * 
 * @param count 
 * @param precision 
 * @return ** map<string, int> 
 */
static map<string, int> Deduplicate(const map<string, int> &count, const string &precision = "Scene") {
    map<string, int> ret;

    for (auto it = count.begin(); it != count.end(); it ++) {
        string loc = it->first;

        if (precision == "Scene") {
            // do nothing
        }
        if (precision == "Act") {
            int pos = loc.find("/Scene");
            if (pos != -1) {
                loc = loc.substr(0, pos);
            }
        }
        if (precision == "Document") {
            int pos = loc.find("/Act");
            if (pos != -1) {
                loc = loc.substr(0, pos);
            }
        }

        int cnt = it->second;
        if (ret.find(loc) != ret.end()) {
            ret[loc] += cnt;
        } else {
            ret[loc] = cnt;
        }
    }

    return ret;
}

/**
 * @brief Search the corpus with keywords.
 * 
 * @param keywords 
 * @param precision 
 * @return ** vector<string> 
 */

vector<string> Corpus::Search(const vector<string> &keywords) {
    return Search(keywords, "Document");
}

vector<string> Corpus::Search(const vector<string> &keywords, const string &precision) {
    assert(precision == "Scene" or precision == "Act" or precision == "Document");

    vector<string> ret;

    // Select keywords in the corpus with at least `FREQUENCY_LIMIT` frequencies.
    vector<pair<string, FileIndex>> words;
    for (auto it = keywords.begin(); it != keywords.end(); it ++) {
        string keyword = stemize(*it);
        FileIndex idx = indices[keyword];
        if (idx.countTotal < FREQUENCY_LIMIT) {
            words.push_back(make_pair(keyword, idx));
        }
    }

    // Find the intersection of the locations of the keywords.
    vector<pair<string, int>> results;
    for (auto it = words.begin(); it != words.end(); it ++) {
        map<string, int> count = Deduplicate(it->second.countPerSection, precision);

        if (it == words.begin()) {
            for (auto iter = count.begin(); iter != count.end(); iter ++) {
                results.push_back(*iter);
            }
        } else {
            for (auto iter = results.begin(); iter != results.end(); ) {
                if (count.find(iter->first) == count.end()) {
                    iter = results.erase(iter);
                } else {
                    iter->second += count[iter->first];
                    iter ++;
                }
            }
        }
    }

    // Lambda function to sort keywords by their weights.
    auto comp = [](pair<string, int> &a, pair<string, int> &b) -> bool {
        return a.second > b.second;
    };
    sort(results.begin(), results.end(), comp);

    // Select first `RESULT_NUM_LIMIT` files that have the largest weights.
    if (results.size() > RESULT_NUM_LIMIT) {
        results.erase(results.begin() + RESULT_NUM_LIMIT, results.end());
    }

    // Return the keywords.
    for (auto it = results.begin(); it != results.end(); it ++) {
        ret.push_back(it->first);
    }

    return ret;
}
