#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "Header.h"
#include "Staff.h"

/*Main student menu*/

void showStudentMenu(User& user);

//1. Check-in.
//2. View check-in result.
//3. View schedules.
void loadListClass(int& n, string*& Class);
void createScheduleFile();
//4. View your scores of a course.

//5. Change password.
void changeStudentPassword(User& user);

//6. View student profile infomation.
//this function is located in Header.h

//7. Logout

#endif 
