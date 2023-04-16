#include <iomanip>
#include <model.h>

Student::Student(std::string name, int score1, int score2, int score3) {
    this->name = name;
    this->score[0] = score1;
    this->score[1] = score2;
    this->score[2] = score3;
}

std::string Student::getName() const {
    return this->name;
}

int Student::getScore(int index) const {
    return this->score[index];
}

int Student::getSum() const {
    // get the sum of the three scores
    return this->score[0] + this->score[1] + this->score[2];
}

float Student::getAverage() const {
    // get the average of the three scores
    return this->getSum() / 3.0;
}

std::ostream &operator<<(std::ostream &output, const Student &stu) { 
    // format output the student information
    output << std::setw(8) << std::left << stu.name
        << std::setw(8) << std::left << stu.score[0]
        << std::setw(8) << std::left << stu.score[1]
        << std::setw(8) << std::left << stu.score[2]
        << std::setw(7) << std::left << std::setprecision(6) << stu.getAverage();
    return output;
}

//---------------------------------------------------------------------------------

StudentTable::StudentTable() {
    this->columnNum = 0;
    column.clear();
}

StudentTable::~StudentTable() {
    column.clear();
}

void StudentTable::insert(const Student &stu) {
    // insert a student into the table
    this->column.push_back(stu);
    this->columnNum++;
}

void StudentTable::remove(int index) {
    // remove the (index)th student from the table
    this->column.erase(this->column.begin() + index);
    this->columnNum--;
}

float StudentTable::getScoreAverage(int index) const {
    // get the average score of the (index)th course
    float sum = 0;
    for (int i = 0; i < this->columnNum; i++) {
        sum += this->column[i].getScore(index);
    }
    return sum / this->columnNum;
}

int StudentTable::getScoreMin(int index) const {
    // get the minimum score of the (index)th course
    if (this->columnNum == 0) {
        // if the table is empty, return 0
        return 0;
    }
    int min = this->column[0].getScore(index);
    for (int i = 1; i < this->columnNum; i++) {
        if (this->column[i].getScore(index) < min) {
            min = this->column[i].getScore(index);
        }
    }
    return min;
}

int StudentTable::getScoreMax(int index) const {
    // get the maximum score of the (index)th course
    if (this->columnNum == 0) {
        // if the table is empty, return 0
        return 0;
    }
    int max = this->column[0].getScore(index);
    for (int i = 1; i < this->columnNum; i++) {
        if (this->column[i].getScore(index) > max) {
            max = this->column[i].getScore(index);
        }
    }
    return max;
}

std::string StudentTable::getStatisticalScore() const {
    // get the statistical score of the table
    std::ostringstream os;
    os << std::setw(8) << std::left << ""
        << std::setw(8) << std::left << "average";
    for (int i = 0; i < 3; i++) {
        // output the average score of the ith course
        os << std::setw(8) << std::left << std::setprecision(2) << this->getScoreAverage(i);
    }
    os << std::endl;

    os << std::setw(8) << std::left << ""
        << std::setw(8) << std::left << "min";
    for (int i = 0; i < 3; i++) {
        // output the min score of the ith course
        os << std::setw(8) << std::left << this->getScoreMin(i);
    }
    os << std::endl;

    os << std::setw(8) << std::left << ""
        << std::setw(8) << std::left << "max";
    for (int i = 0; i < 3; i++) {
        // output the max score of the ith course
        os << std::setw(8) << std::left << this->getScoreMax(i);
    }
    os << std::endl;

    return os.str();
}

std::ostream &operator<<(std::ostream &output, const StudentTable &table) {
    // format output the table

    // output the field names
    output << std::setw(8) << std::left << "no"
        << std::setw(8) << std::left << "name"
        << std::setw(8) << std::left << "score1"
        << std::setw(8) << std::left << "score2"
        << std::setw(8) << std::left << "score3"
        << std::setw(7) << std::left << "average" << std::endl;
    for (int i = 0; i < table.columnNum; i++) {
        // output the ith student information with index
        output << std::setw(8) << std::left << i + 1 << table.column[i] << std::endl;
    }
    return output;
}