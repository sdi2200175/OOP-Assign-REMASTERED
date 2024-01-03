#include <iostream>
#include "Secretary.hpp"
using namespace std;

const string StudentDataFile = "./data/Students.txt";
const string ProfessorDataFile = "./data/Professors.txt";
const string CourseDataFile = "./data/Courses.txt";

int main() {

    Secretary sec;
    sec.parseStudents(StudentDataFile);
    sec.parseProfessors(ProfessorDataFile);
    sec.parseCourses(CourseDataFile);

    cout << *(sec.studentSearch("Eva Nik Rag"));
    cout << *(sec.professorSearch("Anastasia - Lygizou"));
    cout << *(sec.courseSearch("Object Oriented Programming"));

    cout << sec;

    return 0;
}