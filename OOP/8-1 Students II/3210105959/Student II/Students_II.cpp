#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<cmath>

/* define the MAX score */
#define MAX (65535)
using namespace std;

/* the class of Student */
/* A Student has name, courses and scores corresponding to courses*/
/* And Student offers methods to add course and score or to calculate the average of scores*/
class Student{
    public:
        string name;
        vector<string> courses;
        map<string, double> scores;

        void addCourse(string course, double score){
            if(find(courses.begin(), courses.end(), course) != courses.end()){ // Determine whether the course has been existed 
                cout<< "Element has been existed";
                exit(1);
            }
            courses.push_back(course);
            scores[course] = score;
        }

        double getAverage(){
            double sum = 0;
            for(auto v : scores){
                sum += v.second;
            }
            return sum/scores.size();
        }
};

/* the class of Course */
/* A Course has name, number of occurrences, the total scores, the max scorses and the min scores*/
/* And Course offers a method to calculate the average of the scores*/
class Course{
    public:
        string course;
        int count = 0; //number of occurrences
        double sum = 0;
        double max = 0;
        double min = MAX;

        double getAverage(){
            return sum/count;
        }
};

/* Function of ShowData*/
/* Usage : show the scores of all courses of all studens */
/* Parameter: the Student Vector and the Course Vector */
/* If a student don't choose the course, its scores will be NULL */
void ShowData(vector<Student> stuArray, vector<Course> courseArray){
    system("cls");
    cout << "no\t" << "name\t";
    for(Course s : courseArray){
        cout << s.course << "\t";
    }
    cout << "average" << endl;
    
    int num = 0; // num as student ID
    for(Student stu : stuArray){ // Loop for students
        num++;
        cout << num << "\t" << stu.name << "\t";
        
        for (Course c : courseArray){ // Loop for courses
            if(find(stu.courses.begin(), stu.courses.end(), c.course) != stu.courses.end()){ // find the course whether is learnt by the student
                cout << stu.scores[c.course] << "\t";
            }
            else{
                cout << "NULL\t";
            }
        }
        cout << stu.getAverage() << "\t" << endl;
    }

    for(int i=0; i < 3; i++){
        switch (i)
        {
            case 0: cout << "\taverage\t"; break;
            case 1: cout << "\tmin\t"; break;
            case 2: cout << "\tmax\t"; break;
            default: break;
        }
        for(Course c : courseArray){
            switch (i)
            {
                case 0: cout << c.getAverage() << "\t"; break;
                case 1: cout << c.min << "\t"; break;
                case 2: cout << c.max << "\t"; break;
                default: break;
            }
        }
        cout << endl;
    }
    system("pause");
}

/* Main Function */
/* User can input 1,2,3,4 four numbers to choose their action */
/* 1: To insert data of students, data format should be <student name> <course name> <score> <course name> <score> ... <'#' or '##'>, '#' is mean to insert another student, '##' is mean to end the insertion */
/* 2: To Show the Data */
/* 3: Clear the Data */
/* 4. Exit the Program */
/* Please Ensure Your Scores Be Number*/
/* And string should be less than 8 characters*/
int main(){
    vector<Student> stuArray;
    vector<Course> courseArray;
    int choose;
    bool _exit = false;
    while(!_exit){
        system("cls");
        cout << "Please enter your choice:" << endl;
        cout << "1. Insert your data" << endl;
        cout << "2. Show your data" <<endl;
        cout << "3. Clear Data" <<endl;
        cout << "4. Exit" <<endl;
        cin >> choose;
        switch (choose)
        {
            case 1:{
                system("cls");
                bool flagInput = true;
                while(flagInput){
                    cout << "-------------------------------------------" << endl;
                    cout << "input '#' for next student" << endl;
                    cout << "input '##' for exit" << endl;
                    string name;
                    string course;
                    double score;
                    cout << "Please Input Student Name:";
                    cin >> name;
                    cout << "Please input Course:";
                    cin >> course;

                    if(course == "##") {  //finish the insertion
                        flagInput = false;
                        break;
                    }

                    while (course != "#" && course != "##"){
                        cout << "Please input Score:";
                        cin >> score;
                        if(!score){
                            cout << "Please Input Correct Score!" << endl;
                            exit(1);
                        }
                        
                        // Determine whether the student is already in the vector
                        bool flag = false; 
                        for(Student& stu : stuArray){
                            if(stu.name == name){ // If exist, just add course and score
                                stu.addCourse(course, score);
                                flag = true;
                                break;
                            }
                        }

                        if(flag == false){ // If not, add a new student
                            Student _student;
                            _student.name = name;
                            _student.addCourse(course, score);
                            stuArray.push_back(_student);
                        }

                        // Determine whether the course is already in the vector
                        flag = false;
                        for(Course& c : courseArray){
                            if(c.course == course){ // If exist, update the count, sum, min and max
                                c.count++;
                                c.sum += score;
                                c.min = min(c.min, score);
                                c.max = max(c.max, score);
                                flag = true;
                            }
                        }

                        if(flag == false){  // If not, add a new course
                            Course _course;
                            _course.course = course;
                            _course.count = 1;
                            _course.sum = score;
                            _course.min = score;
                            _course.max = score;
                            courseArray.push_back(_course);
                        }

                        cout << "Please input Course:";
                        cin >> course;

                        if(course == "#") break; //next student
                        if(course == "##") {  //finish the insertion
                            flagInput = false;
                            break;
                        }
                    }
                }
            }
                break;
            case 2:{
                //show data
                ShowData(stuArray, courseArray);
                break;
            }
            case 3:{
                //clear the data
                stuArray.clear();
                courseArray.clear();
                break;
            }
            case 4:{
                //exit
                _exit = true;
                break;
            }
            default:
                break;
        }
    }
    system("pause");
    return 0;
}