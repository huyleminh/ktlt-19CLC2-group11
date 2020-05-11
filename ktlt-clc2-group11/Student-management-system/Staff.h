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
void addNewCourse(Course& c);


#endif
