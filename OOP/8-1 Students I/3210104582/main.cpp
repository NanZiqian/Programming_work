#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <model.h>

std::string randomName();

int main() {
    StudentTable table;

    // initialize the random seed
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        // insert 10 random students information into the table
        table.insert(Student(randomName(), rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1));
    }

    // output the table and the statistical data
    std::cout << table << table.getStatisticalScore() << std::endl;

    return 0;
}

std::string randomName() {
    // generate a random name in the format "X.XXXX"
    std::string name = "";

    name += rand() % 26 + 'A';
    name += '.';

    int length = rand() % 5 + 1;
    for (int i = 0; i < length; i++) {
        name += rand() % 26 + 'A';
    }

    return name;
}