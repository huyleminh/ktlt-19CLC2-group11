#ifndef _STAFF_H_
#define _STAFF_H_

#include "Header.h"

void showStaffMenu();
void classAndStudentMode();
void importStudentsFromCSV(Student*& students, int& nStudent);
void createUserPassword(Student* students, const int nStudent);
void viewListClasses(ifstream& data, int& nClasses);

#endif
