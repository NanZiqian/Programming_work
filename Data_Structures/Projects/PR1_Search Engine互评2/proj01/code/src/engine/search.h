#ifndef __SEARCH__
#define __SEARCH__

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

using std::vector;
using std::string;
using std::map;

#define FREQUENCY_LIMIT     4000    // keywords that have at least `FREQUENCY_LIMIT` frequencies.
#define RESULT_NUM_LIMIT    10      // first `RESULT_NUM_LIMIT` files that have the largest weights.

struct FileIndex {
    int countTotal;
    map<string, int> countPerSection;
};

class Corpus {
private:
    map<string, FileIndex> indices;
    map<string, FileIndex> ReadInvertedFileIndex(const string &directoryPath);

public:
    Corpus();
    Corpus(const string &directoryPath);
    void Read(const string &directoryPath);
    vector<string> Search(const vector<string> &keywords);
    vector<string> Search(const vector<string> &keywords, const string &precision);
};

#endif
