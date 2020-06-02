#include "Lecturers.h"
#include "AllRole.h"
#include "Staff.h"

/*Main lecturer menu*/

void showLecturerMenu(User& user) {
	cout << "**********LECTURER MENU**********" << endl;
	cout << "> 1. View list of courses in the current semester.\n";
	cout << "> 2. View list of students of a course.\n";
	cout << "> 3. View attendance list of a course.\n";
	cout << "> 4. Edit an attendance.\n";
	cout << "> 5. Import scoreboard of a course(midterm, final, lab, bonus) from a csv file.\n";
	cout << "> 6. Edit grade of a student.\n";
	cout << "> 7. View a scoreboard.\n";
	cout << "> 8. Change password.\n";
	cout << "> 9. View lecturer profile infomation.\n";
	cout << "> 10. Logout.\n";
	cout << "> 11. Exit app.\n";

OPTION:
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 11)
		goto OPTION;

	switch (option)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6: 
		break;
	case 7: 
		break;
	case 8:
		changeLecPassword(user);
		break;
	case 9:
		viewProfile(user);
		break;
	case 10: 
		return;
	case 11:
		exit(0);
	}
	showLecturerMenu(user);
}

//1. View list of courses in the current semester.
//2. View list of students of a course.
//3. View attendance list of a course.
//4. Edit an attendance.
//5. Import scoreboard of a course(midterm, final, lab, bonus) from a csv file.
//6. Edit grade of a student.
//7. View a scoreboard.

//8. Change lecturer password.
void changeLecPassword(User& user) {
	Lecturer* lecturers;
	int n = 0;

	changePassword(user);
	loadLecturerUser(lecturers, n);
	for (int i = 0; i < n; i++) {
		if (user.username == lecturers[i].user.username) {
			lecturers[i].user.password = user.password;
			break;
		}
	}

	ofstream fout("Lecturers.txt");
	fout << n << endl;
	for (int i = 0; i < n; i++) {
		fout << lecturers[i].user.username << endl << lecturers[i].user.password << endl << lecturers[i].name << endl;
	}

	fout.close();
	delete[]lecturers;
}

//32 import scoreboard of a course

void importScoreboard()
{
	string courseID;
	string classID;

	cout << "Input Class ID: ";
	cin >> classID;
	cout << "Input Course ID: ";
	cin >> courseID;

	//Course* aCourses;
	//int nCourses;

	//loadCoursesFromTXT("Courses.txt", aCourses, nCourses);

	//Course course;
	//course.ID = "";
	//for (int i = 0; i < nCourses; i++)
	//{
	//	if (aCourses[i].ID.compare(courseID) == 0 || aCourses[i].classID.compare(classID) == 0)
	//	{
	//		course = aCourses[i];
	//		break;
	//	}
	//}
	//if (course.ID.compare("") == 0)
	//{
	//	cout << "Cant find the inputted course" << endl;
	//	return;
	//}

	string filenameCSV = classID + "-" + courseID + "-Scoreboard.csv";
	string filenameTXT = classID + "-" + courseID + "-Scoreboard.txt";
	////

	ifstream fin(filenameCSV);
	ofstream fout(filenameTXT);


	if (!fin.is_open())
	{
		cout << "Can not open " << filenameCSV <<endl;
		return;
	}
	if (!fout.is_open()) {
		cout << "Can not open " << filenameTXT<< endl;
		return;
	}

	int nStudents = 0;
	string ignore = "";
	while (!fin.eof()) {
		getline(fin, ignore);
		++nStudents;
	}

	//int nStudents = 4;
	Student* aStudents = new Student[nStudents];

	fin.seekg(0, fin.beg);
	//string ignore = "";
	int i = 0;
	getline(fin, ignore, '\n');
	fout << nStudents << endl;
	while (!fin.eof()) {
		//Read each line in csv 
		getline(fin, ignore, ',');
		getline(fin, aStudents[i].ID, ',');
		getline(fin, aStudents[i].fullName, ',');
		fin>>aStudents[i].score.midterm;
		//getline(fin, ignore, ',');
		fin.ignore(1);
		fin >> aStudents[i].score.final;
		fin.ignore(1);
		//getline(fin, ignore, ',');
		fin >> aStudents[i].score.bonus;
		fin.ignore(1);
		//getline(fin, ignore, ',');
		fin >> aStudents[i].score.total;
		fin.ignore(1);
		//getline(fin, ignore, ',');
		//Export 
		fout << endl << aStudents[i].ID << endl << aStudents[i].fullName << endl << aStudents[i].score.midterm << endl << aStudents[i].score.final << endl << aStudents[i].score.bonus << endl << aStudents[i].score.total << endl;
		cout << endl << aStudents[i].ID << endl << aStudents[i].fullName << endl << aStudents[i].score.midterm << endl << aStudents[i].score.final << endl << aStudents[i].score.bonus << endl << aStudents[i].score.total << endl;
		i++;
	}
	fin.close();
	fout.close();
}
//9. View lecturer profile infomation.
//This function is located in Header.h

//10. Logout.
