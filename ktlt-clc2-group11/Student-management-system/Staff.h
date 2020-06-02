#ifndef _STAFF_H_
#define _STAFF_H_

#include "Header.h"

void showStaffMenu(User& user);

//1. Class and student.
void classAndStudentMode();
void importStudentsFromCSV(Student*& students, int& nStudent);
void createUserPassword(Student* students, const int nStudent);

void addStudentToClass();

void getListStudents(string classID, Student*& Students, int& nStudents);
void saveStudent(Student* Students, int nStudent, string fclass);
void deleteStudent(string Aclass);
void Changeclass(string origin, string des);
void Edit();
void getListClass(int& n, string*& Class);
void viewListStudents(string classID);
void convertToUpper(string& s);

//5. Change password.
void changeStaffPassword(User& user); 
//6. View profile information.
//This function is located in Header.h

//Course
void addNewCourse(int& nCourses);
void editLecturers();
void convertToLower(string& s);
void createUsername(string& username, string name);
void createNewLecturer();
//2 Courses.
void courseMode();
void importCoursesFromCsvFile(Course*& courses, int& nCourse);
void createClassCourse(Course*& courses, const int nCourse);
//add student into file course
void splitClassID(string& str);
void addStudentIntoCourse();


void addNewCourse(Course& c);

//22
void viewAttendanceList();
void loadCoursesFromTXT(string filename1, Course*& courses, int & n);
void loadDataCourse(string filename, Student*& aStudents, int& n);

//19
void addStudentToCourse();
#endif