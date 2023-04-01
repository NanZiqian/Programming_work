#include "search.h"
#include <cstdio>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/**
 * @brief User interface.
 * 
 * @return ** int 
 */
int main() {
    Corpus corpus;

    vector<string> keywords;

    cout << "Please input the words you want to search (delimited by <Space>), and then press <Enter> to end the input." << endl;

    string word;
    cin >> word;
    while (true) {
        if (getchar() == '\n') {
            keywords.push_back(word);
            break;
        }
        keywords.push_back(word);
        cin >> word;
    }

    // Do search.
    string precision = "Document";
    vector<string> list = corpus.Search(keywords, precision);

    // Print out the search result
    for (auto it = list.begin(); it != list.end(); it ++) {
        cout << *it << endl;
    }

    return 0;
}
