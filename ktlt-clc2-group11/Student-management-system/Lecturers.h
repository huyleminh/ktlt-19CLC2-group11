#ifndef _LECTURERS_H_
#define _LECTURERS_H_

#include "Header.h"

/*Main lecturer menu*/

void showLecturerMenu(User& user);

//1. View list of courses in the current semester.

//2. View list of students of a course.
//viewListStudentsOfCourse();

//3. View attendance list of a course.
//viewAttendanceList();

//4. Edit an attendance.
void editAttendace();

//5. Import scoreboard of a course(midterm, final, lab, bonus) from a csv file.
void importScoreboardFromCsvToTXT();
void exportScoreboardToCSV();
//6. Edit grade of a student.
void editGrade();
//7. View a scoreboard.
void viewaScoreboard(User user);
//8. Change lecturer password.
void changeLecPassword(User& user);

//9. View lecturer profile infomation.
//This function is located in Header.cpp

//10. Logout

#endif