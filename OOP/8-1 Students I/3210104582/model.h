#ifndef _MODEL_H
#define _MODEL_H

#include <iostream>
#include <string>
#include <vector>

class Student {
    private:
        std::string name;
        int score[3];

    public:
        Student(std::string name, int score1, int score2, int score3);

        std::string getName() const;

        int getScore(int index) const;

        int getSum() const;

        float getAverage() const;

        friend std::ostream &operator<<(std::ostream &output, const Student &stu);
};

class StudentTable {
    private:
        int columnNum;
        std::vector<Student> column;

    public:
        StudentTable();

        ~StudentTable();

        void insert(const Student &stu);

        void remove(int index);

        float getScoreAverage(int index) const;

        int getScoreMin(int index) const;

        int getScoreMax(int index) const;

        std::string getStatisticalScore() const;

        friend std::ostream &operator<<(std::ostream &output, const StudentTable &table);
};

#endif