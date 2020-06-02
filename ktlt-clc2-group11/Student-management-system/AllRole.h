#ifndef _ALLROLE_H_
#define _ALLROLE_H_

#include "Header.h"

//This is main menu, the program will be started here 
void menu();

//Login menu
void login(User& userLogin, int& loginMode);

//Load user information
void loadStaffUser(Staff*& staffs, int& nStaff); 

void loadLecturerUser(Lecturer*& lecturers, int& nLec);

void loadStudentUser(Student_User*& students, int& nStu);



#endif