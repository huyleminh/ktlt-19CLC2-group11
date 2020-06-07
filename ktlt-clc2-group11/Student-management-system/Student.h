#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "Header.h"

/*Main student menu*/

void showStudentMenu(User& user);

//1. Check-in.
bool checkStudentInCourse(string ID, string filename,bool& flag);
void checkIn(string ID);
//2. View check-in result.
void checkInResult(string ID);
//3. View schedules.
void loadListClass(int& n, string*& Class);
void createScheduleFile();
void viewSchedule();
//4. View your scores of a course.

//5. Change password.
void changeStudentPassword(User& user);

//6. View student profile infomation.
//this function is located in Header.h

//7. Logout

#endif 
