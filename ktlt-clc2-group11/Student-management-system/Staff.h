#ifndef _STAFF_H_
#define _STAFF_H_

#include "Header.h"

/*Main staff menu*/ 

void showStaffMenu(User& user);

//**1. Class and student.
void classAndStudentMode();

//1. Import students from csv file.
void importStudentsFromCSV(Student*& students, int& nStudent);
void filterStudentToClass(string filename);
void createUserPassword(Student* students, const int nStudent);

//2. Add a student to a class.
void addStudentToClass();
void loadStudent(ifstream& fin, string filename, Student*& students, int& n);
void writeStudent(ofstream& fout, string filename, const Student* students, const int n);
//3. Edit existing student.
void getListStudents(string classID, Student*& Students, int& nStudents);
void saveStudent(Student* Students, int nStudent, string fclass);
void deleteStudent(string Aclass);
void Changeclass(string origin, string des);
void Edit();

//4. View list of classes.
void getListClass(int& n, string*& Class); // use to view in mode 3 and this mode

//5. View list of student in class.
void viewListStudents(string classID);
void convertToUpper(string& s);

//6. Back to staff menu.
//Call classAndStudentMode();

//**2. Courses.
void courseMode();

//1. Edit academic years and semesters.
void menuAcademicYear();
void createAcademicYear();
void createSemester(Semester& temp,string classID,string startYear, string endYear,string HK);
void createCourse(Course& course,string classID);
void deleteCourses();
void deleteSemester();
void deleteYear();
void createSemesterAlone();
//2. Import courses from csv file to txt file.
void importCoursesFromCsvFile(Course*& courses, int& nCourse);
void createClassCourse(Course*& courses, const int nCourse);
void splitClassID(string& str);
void addStudentIntoCourse(const int n);
//3. Manually add a new course.
void addNewCourse();
//4. Edit an existing course.
void editCourse();
//5. Remove a course.
void loadCoursesFromTXT(string filename, Course*& courses, int& n);
void removeCourse();
//6. Remove a specific student from a course.
void removeSpecificStudent();
//7. Add a specific student to a course.
void addStudentToCourse();
//8. View list of courses in the current semester.
//9. View list of students of a course.
void viewListStudentsOfCourse();
//10. View attendance list of a course.
void loadDataCourse(string filename, Student*& aStudents, int& n);
void viewAttendanceList();
//11. Create / update / delete / view all lecturers.
void convertToLower(string& s);
void createUsername(string& username, string name);
void createNewLecturer();
void createDupUsername(string& username, string name);
void updateLecturer();
void deleteLecturer();
void viewAllLecturers();
void editLecturers();

//12. Back to staff menu.
//Call showStaffMenu.

//**3. Scoreboard.
void scoreBoardMode();
void createListOfScoreBoard();
//1. Search and view the scoreboard of a course.
void viewScoreBoard(string sourceTXT);
void loadScoreBoard(string filename);
//2. Export a scoreboard to a csv file.
void getDestinationTXT(const string sourceTXT, string& destinationCSV);
void export_A_ScoreboardToCsv(string sourceTXT, string destinationCSV);
//3. Export all scoreboard to a csv files.
void exportScoreBoardToCSV();

//**4. Attendance list.
void attendanceListMode();
//1. Search and view attendance list of a course.
void viewAttendanceList();
//2. Export a attendance list to a csv file.
void exportAttendanceListToCSV();
void exportAttendanceListToTXT();
//3. Back to staff menu.

//**5. Change staff password.
void changeStaffPassword(User& user); 

//**6. View profile information.
//This function is located in Header.h

//**7. Log out

#endif