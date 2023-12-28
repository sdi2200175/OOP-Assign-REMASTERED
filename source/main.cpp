#include <iostream>
#include "Secretary.hpp"
using namespace std;

const string StudentDataFile = "./data/Students.txt";
const string ProfessorDataFile = "./data/Professors.txt";

int main() {

    Secretary sec;
    sec.parseStudents(StudentDataFile);
    sec.parseProfessors(ProfessorDataFile);

    cout << sec;

    return 0;
}