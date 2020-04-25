#ifndef _ALLROLE_H_
#define _ALLROLE_H_

#include "Header.h"


void login(User& userLogin, int& loginMode);

void loadStaffUser(Staff*& staffs, int& nStaff);
void loadLecturerUser(Lecturer*& lecturers, int& nLec);
void loadStudentUser(Student_User*& students, int& nStu);

void menu();

#endif
