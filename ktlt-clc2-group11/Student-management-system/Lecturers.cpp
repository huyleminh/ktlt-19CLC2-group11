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
		viewListStudentsOfCourse();
		break;
	case 3:
		viewAttendanceList();
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
//viewListStudentsOfCourse();

//3. View attendance list of a course.
//viewAttendanceList();

//4. Edit an attendance.

//5. Import scoreboard of a course(midterm, final, lab, bonus) from a csv file.
void importScoreboardFromCsvToTXT() {
	string courseID;
	string classID;

	cout << "Input Class ID: ";
	cin >> classID;
	cout << "Input Course ID: ";
	cin >> courseID;

	string filenameCSV = classID + "-" + courseID + "-Scoreboard.csv";
	string filenameTXT = classID + "-" + courseID + "-Scoreboard.txt";

	ifstream fin(filenameCSV);
	ofstream fout(filenameTXT);

	if (!fin.is_open()) {
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
		getline(fin, ignore,'\r');
		++nStudents;
	}

	nStudents--;
	Student* aStudents = new Student[nStudents];
	fin.seekg(0, fin.beg);

	int i = 0;
	getline(fin, ignore, '\r');

	fout << nStudents << endl;
	while (!fin.eof()) {
		//Read each line in csv 
		getline(fin, ignore, ',');
		getline(fin, aStudents[i].ID, ',');
		getline(fin, aStudents[i].fullName, ',');
		fin>>aStudents[i].score.midterm;
		fin.ignore(1);
		fin >> aStudents[i].score.final;
		fin.ignore(1);
		fin >> aStudents[i].score.bonus;
		fin.ignore(1);
		fin >> aStudents[i].score.total;
		fin.ignore(1);
		//Export 
		fout << endl << aStudents[i].ID << endl << aStudents[i].fullName << endl << aStudents[i].score.midterm << endl << aStudents[i].score.final << endl << aStudents[i].score.bonus << endl << aStudents[i].score.total << endl;
		//Test
		cout << endl << aStudents[i].ID << endl << aStudents[i].fullName << endl << aStudents[i].score.midterm << endl << aStudents[i].score.final << endl << aStudents[i].score.bonus << endl << aStudents[i].score.total << endl;
		i++;
	}
	fin.close();
	fout.close();
}

//6. Edit grade of a student.
void editGrade()
{
	string classID, courseID;
}


//7. View a scoreboard.

//8. Change lecturer password.
void changeLecPassword(User& user) {
	Lecturer* lecturers;
	int n = 0;

	cin.ignore(1);
	changePassword(user);
	loadLecturerUser(lecturers, n);
	for (int i = 0; i < n; i++) {
		if (user.username == lecturers[i].user.username) {
			lecturers[i].user.password = user.password;
			break;
		}
	}
	cout << lecturers[0].user.username << endl;
	ofstream fout("Lecturers.txt");
	fout << n << endl;
	for (int i = 0; i < n; i++) {
		fout << endl << lecturers[i].user.username << endl << lecturers[i].user.password << endl << lecturers[i].name << endl;
	}

	fout.close();
	delete[]lecturers;
}

//9. View lecturer profile infomation.
//This function is located in Header.h

//10. Logout.
