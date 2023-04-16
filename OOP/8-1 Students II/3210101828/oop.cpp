#include <functional>

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

#include <string>
#include <vector>
#include <map>
#include <set>

using std::vector, std::map, std::set, std::function;
using std::string, std::stringstream, std::to_string;
using std::cin, std::cout, std::endl, std::setprecision, std::fstream, std::istream;

/** LinQ **/

template <class T>
vector<T> filter(vector<T> src, function<bool(T &)> cond_func) {
    vector<T> dst;

    for(T &v : src)
        if(cond_func(v))
            dst.push_back(v);

    return dst;
}

template <class T, class R>
vector<R> select(vector<T> src, function<R(T &)> map_func) {
    vector<R> dst;

    for(T &v : src)
        dst.push_back(map_func(v));

    return dst;
}

template <class K, class V, class R>
vector<R> select(map<K, V> src, function<R(K, V &)> map_func) {
    vector<R> dst;

    for(auto& [k, v] : src)
        dst.push_back(map_func(k, v));

    return dst;
}

template <class T, class R>
R reduce(vector<T> src, function<R(R, T &s)> reduce_func, R initial = R()) {
    R ans = initial;

    for(T &v : src)
        ans = reduce_func(ans, v);

    return ans;
}

template <class T>
T sum(vector<T> src) {
    return reduce<T, T>(src, [](T a, T & b)
    { return a + b; });
}

template <class T>
T min(vector<T> src) {
    return reduce<T, T>(src, [](T a, T & b)
    { return a < b ? a : b; }, 0x7FFFFFFF);
}

template <class T>
T max(vector<T> src) {
    return reduce<T, T>(src, [](T a, T & b)
    { return a > b ? a : b; });
}

template <class T>
T avg(vector<T> src) {
    if(src.size() == 0)
        return 0;

    return sum(src) / src.size();
}

// [s1, s2, ..., sn] -> s1+sep+s2+sep+...+sn
string join(vector<string> s, string sep) {
    if(s.size() == 0) return "";

    stringstream ss;
    ss << s[0];

    for(int i = 1; i < s.size(); i++)
        ss << sep << s[i];

    return ss.str();
}

/** Data Model **/

set<string> courses_set;

struct Record {
    int id;
    string name;
    map<string, float> scores;

    static Record parse(istream &_s) {
        Record r;
        char line[100];
        // NOTE skip the '\n'
        _s >> r.id >> r.name;
        _s.getline(line, sizeof(line));
        auto s = stringstream(line);

        while(!s.eof()) {
            string name; float score;
            s >> name >> score;
            r.scores[name] = score;
            courses_set.insert(name);
        }

        return r;
    }

    float averageScore() {
        return avg(select<string, float, float>(scores, [](auto k, auto v) {return v;}));
    }
};

string f2s(float f, int precision = 4) {
    std::stringstream ss;
    ss << setprecision(precision) << f;
    return ss.str();
}

int main() {
    // help text
    cout << "input format:" << endl;
    cout << "firstly input #stu as int" << endl;
    cout << "then lines of: " << endl
         << "id name class1 score1 class2 score2 ..." << endl;
    // use `fin` for "input.txt"
    // or you can use `cin` for console
    fstream fin("input.txt");
    istream &in = fin;
    // read data
    int N;
    in >> N;
    vector<Record> records;

    for(int i = 0; i < N; i++)
        records.push_back(Record::parse(in));

    vector<string> cources(courses_set.begin(), courses_set.end());
    // print score data items
    cout << endl
         << endl;
    cout << "no\tname\t" << join(cources, "\t") << "\taverage" << endl;
    
    // print student score
    auto scores2str = [&](Record & r) {
        return join(select<string, string>(cources, [&r](auto & c) {
            if(r.scores.find(c) != r.scores.end())
                return f2s(r.scores[c]);
            return string("--");
        }), "\t");
    };
    for(auto &r : records)
        cout << r.id << "\t" << r.name << "\t"
             << scores2str(r) << "\t" << r.averageScore() << endl;

    // print statistics of score

    // `f = int(vector<int>)`
    auto aggregate_scores = [&](auto f) {
        return join(select<string, string>(cources, [&](auto & c) {
            auto filtered = filter<Record>(records, [&](Record & r) { return r.scores.find(c) != r.scores.end();});
            auto sc = select<Record, float>(filtered, [&](Record & r) { return r.scores[c];});
            return f2s(f(sc));
        }), "\t");
    };
    cout << "\tmin\t" << aggregate_scores(min<float>) << endl;
    cout << "\tmax\t" << aggregate_scores(max<float>) << endl;
    cout << "\tavg\t" << aggregate_scores(avg<float>) << endl;

    return 0;
}