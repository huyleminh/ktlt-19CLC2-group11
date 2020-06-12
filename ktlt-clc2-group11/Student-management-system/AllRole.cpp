#include "AllRole.h"
#include "Staff.h"
#include "Lecturers.h"
#include "Student.h"

void menu() {
	/*
		*We start with mode 0: none
		*Login successfully: 
			*Mode 1: Staff
			*Mode 2: Lecturer	
			*Mode 3: Student
		*Login failed: Login mode return 0 and back to main menu 	
	*/

	User user;
	user.username = "";
	user.password = "";
	int loginMode = 0;
	

	login(user, loginMode);
	string welcomeName = user.name;
	convertToUpper(welcomeName);

	switch (loginMode) {
		case 1:
			cout << "WELLCOME " << welcomeName << endl;
			showStaffMenu(user);
			break;
		case 2:
			cout << "WELLCOME " << welcomeName << endl;
			showLecturerMenu(user);
			break;
		case 3:
			cout << "WELLCOME " << welcomeName << endl;
			showStudentMenu(user);
			break;
		default:
			cout << "!!! Wrong user name or password !!!" << endl;
			break;
	}
	menu();
}

void login(User& userLogin, int& loginMode) {
	cout << "##############################\n";
	cout << "#                            #\n";
	cout << "#         LOGIN MENU         #\n";
	cout << "#                            #\n";
	cout << "##############################\n";

	int option = 0;
OPTION: 
	cout << "1. Start app.\n";
	cout << "2. Exit.\n";
	cin >> option;

	if(option != 1 && option != 2)
		goto OPTION;
	else {
		if(option == 2) 
			exit(0);
	}

	cin.ignore(1);
	cout << " > Enter your Username : "; 
	getline(cin, userLogin.username, '\n');

	cout << " > Enter your password : ";
	getline(cin, userLogin.password, '\n');

	//Check is Staff
	Staff* staffs; 
	int nStaff = 0;

	loadStaffUser(staffs, nStaff);
	for (int i = 0; i < nStaff; i++) {
		if (userLogin.username == staffs[i].user.username && userLogin.password == staffs[i].user.password) {
			userLogin.name = staffs[i].name;
			loginMode = 1; 
			delete[]staffs;
			return;
		}
	}

	//Check is lecturer
	Lecturer* lecturers;
	int nLec = 0;

	loadLecturerUser(lecturers, nLec);
	for (int i = 0; i < nLec; i++) {
		if (userLogin.username == lecturers[i].user.username && userLogin.password == lecturers[i].user.password) {
			userLogin.name = lecturers[i].name;
			loginMode = 2;
			delete[]lecturers;
			return;
		}
	}

	//Check is Student
	Student_User* students;
	int  nStu = 0;

	loadStudentUser(students, nStu);
	for (int i = 0; i < nStu; i++) {
		if (userLogin.username == students[i].user.username && userLogin.password == students[i].user.password) {
			userLogin.name = students[i].name;
			loginMode = 3;
			delete[]students;
			return;
		}
	}

	delete[]staffs;
	delete[]lecturers;
	delete[]students;
}

void loadStaffUser(Staff*& staffs, int& nStaff) {
	ifstream fin;
	if (isFileOpen(fin, "Staff.txt") == false)
		return;

	fin >> nStaff;
	staffs = new Staff[nStaff];

	string ignore = "";
	fin.ignore(1);

	for (int i = 0; i < nStaff; i++) {
		getline(fin, ignore, '\n');
		getline(fin, staffs[i].user.username, '\n');
		getline(fin, staffs[i].user.password, '\n');
		getline(fin, staffs[i].name, '\n');
	}

	fin.close();
}

void loadLecturerUser(Lecturer*& lecturers, int& nLec) {
	ifstream fin;
	if (isFileOpen(fin, "Lecturers.txt") == false)
		return;

	fin >> nLec;
	lecturers = new Lecturer[nLec];

	string ignore = "";
	fin.ignore(1);

	for (int i = 0; i < nLec; i++) {
		getline(fin, ignore, '\n');
		getline(fin, lecturers[i].user.username, '\n');
		getline(fin, lecturers[i].user.password, '\n');
		getline(fin, lecturers[i].name, '\n');
	}

	fin.close();
}

void loadStudentUser(Student_User*& students, int& nStu) {
	ifstream fin;
	if (isFileOpen(fin, "StudentUsers.txt") == false)
		return;

	fin >> nStu;
	students = new Student_User[nStu];

	string ignore = "";
	fin.ignore(1);

	for (int i = 0; i < nStu; i++) {
		getline(fin, ignore, '\n');
		getline(fin, students[i].user.username, '\n');
		getline(fin, students[i].user.password, '\n');
		getline(fin, students[i].name, '\n');
	}

	fin.close();
}