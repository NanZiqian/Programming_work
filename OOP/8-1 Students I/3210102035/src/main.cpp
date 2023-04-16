#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

#define GAP "\t" // use what to split while printing
using namespace std;

/// @brief a function split a string by given char
/// @param str the string needs to be split
/// @param sign the char to split
/// @return the vector of split string items
vector<string> split(const string& str, char sign) {
    stringstream ss(str);
    string item;
    vector<string> res;
    while (getline(ss, item, sign)) { // split by sign
        if (!item.empty()) {
            res.push_back(item);
        }
    }
    return res;
}

/// @brief a class to store one record and offer some functions
class oneRecord{
public:
    int id; // the id
    string name; // the name
    int score[3]; // the scores

private:
    /// @brief calculate one's average score
    /// @return the average score
    double calAverage() {
        return (double(score[0])+double(score[1])+double(score[2])) / 3.0;
    }
    /// @brief judge whether a score is an int
    /// @param score the score
    /// @return true if is int
    bool isInt(double score) {
        if (score == int(score)) return true;
        return false;
    }

public:
    /// @brief basic init function for onerecord
    /// @param initId the id
    /// @param initName the name
    /// @param initScore the scores of one person
    oneRecord(int initId, string initName, int initScore[3]){
        id = initId;
        name = initName;
        for (int i = 0; i < 3; i ++) score[i] = initScore[i];
    }
    /// @brief use concated string to initialize onerecord
    /// @param initId the id
    /// @param all a string of name and scores in format
    oneRecord(int initId, string all) {
        id = initId;
        auto parts = split(all, '/'); // split by '/'
        if (parts.size() != 4) {
            cout << "error record!" << endl;
            return;
        }else {
            name = parts[0];
            for (int i = 0; i < 3; i ++) {
                stringstream ss(parts[i + 1]);
                ss >> score[i];
            }
        }
    }

    /// @brief output one record in format
    void output() {
        cout << id << GAP << name << GAP \
        << score[0] << GAP << score[1] << GAP << score[2] << GAP \
        << fixed << (isInt(calAverage()) ? setprecision(0) : setprecision(6))\
        << calAverage() << endl;
    }
};

/// @brief a database class for store all records
class dataBase{
private:
    map<int, oneRecord> records; // records of a database

private:
    /// @brief a function help output scores
    /// @tparam T int/double
    /// @param prompt the prompt of what's the meaning of scores
    /// @param scores the scores to output
    template <typename T>
    void outputScores(string prompt, vector<T> scores) {
        cout << prompt << GAP << fixed << setprecision(1)\
        << scores[0] << GAP << scores[1] << GAP << scores[2] << endl;
    }

public:
    /// @brief a init function by offering a path of file
    /// @param path the path of file
    dataBase(string path) {
        ifstream input(path);
        string row;
        int no = 1;
        while(getline(input, row)) { //split by rows
            // add one record
            oneRecord test = oneRecord(no, row);
            records.insert(pair<int, oneRecord>(no, test));
            no ++;
        }
    }

    /// @brief calculate average scores of a database
    /// @return scores 
    vector<double> calAverageScores() {
        vector<double> res(3);
        res[0] = res[1] = res[2] = 0.0;
        int len = records.size();
        for (auto item : records) {
            res[0] += item.second.score[0];
            res[1] += item.second.score[1];
            res[2] += item.second.score[2];
        }
        res[0] /= len;
        res[1] /= len;
        res[2] /= len;
        return res;
    }
    /// @brief calculate highest scores of a database
    /// @return scores 
    vector<int> getMaxScores() {
        vector<int> res(3);
        res[0] = res[1] = res[2] = 1;
        for (auto item : records) {
            res[0] = max(item.second.score[0], res[0]);
            res[1] = max(item.second.score[1], res[1]);
            res[2] = max(item.second.score[2], res[2]);
        }
        return res;
    }
    /// @brief calculate lowest scores of a database
    /// @return scores 
    vector<int> getMinScores() {
        vector<int> res(3);
        res[0] = res[1] = res[2] = 5;
        for (auto item : records) {
            res[0] = min(item.second.score[0], res[0]);
            res[1] = min(item.second.score[1], res[1]);
            res[2] = min(item.second.score[2], res[2]);
        }
        return res;
    }
    /// @brief output all records of the database in format
    void outputAllRecords() {
        cout << "no" << GAP << "name" << GAP \
        << "score1" << GAP << "score2" << GAP << "score3" << GAP \
        << "average" << endl;
        for (auto item : records) {
            item.second.output();
        }
    }
    /// @brief the function outputs all records in format and the average/max/min scores
    void outputAll() {
        outputAllRecords();
        vector<double> averages = calAverageScores();
        cout << GAP; outputScores("average", averages);
        vector<int> mins = getMinScores();
        cout << GAP; outputScores("min", mins);
        vector<int> maxs = getMaxScores();
        cout << GAP; outputScores("max", maxs);
    }
};

/// @brief main function
/// @param argc number of inputs
/// @param argv input strings
/// @return errcode, 0 if success
int main(int argc, char *argv[]) {
    // modify the path of records
    string path = "../data/records.txt";
    if (argc == 2) path = argv[1];

    // initialize one database
    dataBase db = dataBase(path);
    db.outputAll();

    return 0;
}