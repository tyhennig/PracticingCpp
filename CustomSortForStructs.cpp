#include <iostream>
#include <string> //std::string
#include <vector> //std::vector
#include <algorithm> //std::sort()

/*
A short program displaying how std::sort() can be applied to user-made types (structs)

User inputs number of students, their names and grades.
Sorts by grade.
*/

struct Student
{
    std::string name{};
    int grade{};
};

//typedef not completely necessary
using studentsVec = std::vector<Student>;


//custom compare for std::sort(), return true if a should be before b
bool compareStudentGrades(const Student& a, const Student& b)
{
    return (a.grade > b.grade);
}



void fillStudents(studentsVec& v)
{
    for (auto& temp : v)
    {
        std::cout << "Name: ";
        std::cin >> temp.name;
        //std::cout << '\n';

        std::cout << "Grade: ";
        std::cin >> temp.grade;
        std::cout << "\n";
    }
}

void printStudents(const studentsVec& v)
{
    for (auto& temp : v)
    {
        std::cout << temp.name << " got a grade of " << temp.grade << '\n';
    }
}

int main()
{
    std::cout << "How many students? ";
    int numStudents{};
    std::cin >> numStudents;
    std::cout << '\n';

    studentsVec v(numStudents);

    fillStudents(v);
    std::sort(v.begin(), v.end(), compareStudentGrades);    
    printStudents(v);
    
    return 0;
}
