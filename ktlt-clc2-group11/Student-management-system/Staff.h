#ifndef _STAFF_H_
#define _STAFF_H_

#include "Header.h"

void showStaffMenu(User& user);

//1. Class and student.
void classAndStudentMode();
void importStudentsFromCSV(Student*& students, int& nStudent);
void createUserPassword(Student* students, const int nStudent);
void viewListClasses(ifstream& data, int& nClasses);
//5. Change password.
void changeStaffPassword(User& user); 
//6. View profile infomation.
//This function is located in Header.h

#endif
