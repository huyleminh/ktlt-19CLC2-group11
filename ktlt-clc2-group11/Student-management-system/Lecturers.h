#ifndef _LECTURERS_H_
#define _LECTURERS_H_

#include "Header.h"

void showLecturerMenu(User& user);

//1. View list of courses in the current semester.
//2. View list of students of a course.
//3. View attendance list of a course.
//4. Edit an attendance.
//5. Import scoreboard of a course(midterm, final, lab, bonus) from a csv file.
//6. Edit grade of a student.
//7. View a scoreboard.
//8. Change password.
void changeLecPassword(User& user);
//9. View profile infomation.
//this function is located in Header.h

//32 Import scoreboard of a course
void importScoreboard();
#endif