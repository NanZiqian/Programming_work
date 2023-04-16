#include<iostream>
#include<string>

// Macro Definition
#define max(x, y) (x) > (y) ? (x) : (y)
#define min(x, y) (x) < (y) ? (x) : (y)

using namespace std;

// The class defined below is used for storing student's name and scores
class Student
{
    private:
        string name;
        int score[3];
    public:
        friend istream &operator >> (istream &in, Student &A);
        friend ostream &operator << (ostream &out, Student &A);
        float average() {return 1.0 * (score[0] + score[1] + score[2]) / 3;} // return student's average score
        int getscore(int i) { return score[i];} // get student's score
};

// Overloading operators
istream &operator >> (istream &in, Student &A)
{
    in >> A.name >> A.score[0] >> A.score[1] >> A.score[2]; // Input information of one student
    return in;
}

ostream &operator << (ostream &out, Student &A)
{
    out << A.name << '\t';
    out << A.score[0] << '\t';
    out << A.score[1] << '\t';
    out << A.score[2]; // Output student's information
    return out;
}

int main()
{
    Student students[10];
    int max[3] = {0, 0, 0};
    int min[3] = {1<<30, 1<<30, 1<<30};
    float aver[3] = {0, 0, 0};
    // Input
    for(int i = 0; i < 10;i++)
    {
        cin >> students[i];
        for(int j = 0;j < 3;j++)
        {
            max[j] = max(max[j], students[i].getscore(j)); // Find the highest score for each course
            min[j] = min(min[j], students[i].getscore(j)); // Find the lowest score for each course
            aver[j] += (float)students[i].getscore(j); // Calculate students' average score for each course
        }
    }
    for(int i = 0;i < 3;i++) aver[i] /= 10;
    
    // Output the list
    cout << "no\tname\tscore1\tscore2\tscore3\taverage" << endl;
    for(int i = 0;i < 10;i++)
    {
        cout << i + 1 << '\t';
        cout << students[i] << '\t';
        cout << students[i].average() << endl;
    }

    cout << "\taverage\t" << aver[0] << '\t' << aver[1] << '\t' << aver[2] << endl;
    cout << "\tmin\t" << min[0] << '\t' << min[1] << '\t' << min[2] << endl;
    cout << "\tmax\t" << max[0] << '\t' << max[1] << '\t' << max[2] << endl;

    return 0;
}