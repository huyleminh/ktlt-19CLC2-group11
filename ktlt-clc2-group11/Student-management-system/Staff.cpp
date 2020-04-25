#include "Staff.h"
#include "AllRole.h"

void showStaffMenu(User& user) {
	cout << "**********STAFF MENU**********" << endl;
	cout << "> 1. Class and student.\n";
	cout << "> 2. Course.\n";
	cout << "> 3. Scoreboard.\n";
	cout << "> 4. Attendance list.\n";
	cout << "> 5. Change password.\n";
	cout << "> 6. View profile infomation.\n";
	cout << "> 7. Logout, back to login menu.\n";

OPTION: 
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 7)
		goto OPTION;

	switch (option)
	{
	case 1: 
		//call classe and student
		break;
	case 2:
		//call course
		break;
	case 3:
		//call scoreboard
		break;
	case 4: 
		//call attendance list
		break;
	case 5:
		changeStaffPassword(user);
		showStaffMenu(user);
	case 6:
		viewProfile(user);
		showStaffMenu(user);
	case 7: 
		menu();
	}
}

void classAndStudentMode() {
	cout << "> 1. Import students from csv.\n";
	cout << "> 2. Add a student to a class.\n";
	cout << "> 3. Edit existing student.\n";
	cout << "> 4. View list of classes.\n";
	cout << "> 5. View list of student in class.\n";
	cout << "> 6. Back to staff menu.\n";

OPTION:
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 4)
		goto OPTION;

	Student* students;
	int nStudent = 0;

	switch (option)
	{
	case 1:
		importStudentsFromCSV(students, nStudent);
		createUserPassword(students, nStudent);
		classAndStudentMode();
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
	}
}

void importStudentsFromCSV(Student*& students, int& nStudent) {
	ifstream fin;
	if (isFileOpen(fin, "Students.csv") == false)
		return;

	ofstream fout;
	fout.open("Students.txt");
	if (!fout.is_open()) {
		cout << "Can not open Students.txt" << endl;
		return;
	}

	nStudent = 0;
	string ignore = "";
	while (!fin.eof()) {
		getline(fin, ignore, '\n');
		++nStudent;
	}
	students = new Student[nStudent];
	
	fin.seekg(0, fin.beg);
	
	ignore = "";
	int i = 0;
	
	fout << nStudent << endl;
	while (!fin.eof()) {
		//Read each line in csv 
		getline(fin, ignore, ',');
		getline(fin, students[i].ID, ',');
		getline(fin, students[i].fullName, ',');
		getline(fin, students[i].gender, ',');
		getline(fin, students[i].DoB, ',');
		getline(fin, students[i].classID, '\n');
		//Export to Students.txt
		fout << endl << students[i].ID << endl << students[i].fullName << endl << students[i].gender << endl << students[i].DoB << endl << students[i].classID << endl;
		i++;
	}
	fin.close();
	fout.close();
}

void createUserPassword(Student* students, const int nStudent) {
	ofstream fout;
	fout.open("StudentUsers.txt");
	if (!fout.is_open()) {
		cout << "Can not open StudentUsers.txt" << endl;
		return;
	}

	fout << nStudent << endl;
	for (int i = 0; i < nStudent; i++) {
		fout << endl << students[i].ID << endl;
		fout << students[i].DoB << endl;
		fout << students[i].fullName << endl;
	}

	fout.close();
}

void viewListClasses(ifstream& data, int& nClasses)
{
	data.open("Classes.txt");

	string buff;
	data >> nClasses;
	cout << "List of Classes:\n\n";
	while (!data.eof())
	{
		getline(data, buff, '\n');
		cout << buff << endl;
	}
	data.close();
}

//Change password
void changeStaffPassword(User& user) {
	Staff* staffs;
	int n = 0;

	changePassword(user);
	loadStaffUser(staffs, n);
	for (int i = 0; i < n; i++) {
		if (user.username == staffs[i].user.username ) {
			staffs[i].user.password = user.password;
			break;
		}
	}

	ofstream fout("Staff.txt");
	fout << n << endl;
	for (int i = 0; i < n; i++) {
		fout << staffs[i].user.username << endl << staffs[i].user.password << endl << staffs[i].name << endl;
	}

	fout.close();
	delete[]staffs;
}