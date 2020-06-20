#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "Header.h"
#include <ctime>

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
void viewSchedule(User u);
//4. View your scores of a course.
void loadClassSchedule(string classID, int& n, Course*& courses);
void viewScore(User u);
//5. Change password.
void changeStudentPassword(User& user);

//6. View student profile infomation.
//this function is located in Header.cpp

//7. Logout

#endif 
