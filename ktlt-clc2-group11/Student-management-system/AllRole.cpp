#include "AllRole.h"
#include "Staff.h"

void login(User& userLogin, int& loginMode) {
	cout << " > Enter your User name : "; 
	getline(cin, userLogin.username, '\n');

	cout << " > Enter your password : ";
	getline(cin, userLogin.password, '\n');

	Staff* staffs; 
	Lecturer* lecturers;
	Student_User* students;
	int nStaff = 0, nLec = 0, nStu = 0;

	loadStaffUser(staffs, nStaff);
	for (int i = 0; i < nStaff; i++) {
		if (userLogin.username == staffs[i].user.username && userLogin.password == staffs[i].user.password) {
			userLogin.name = staffs[i].name;
			loginMode = 1; 
			delete[]staffs;
			return;
		}
	}

	loadLecturerUser(lecturers, nLec);
	for (int i = 0; i < nLec; i++) {
		if (userLogin.username == lecturers[i].user.username && userLogin.password == lecturers[i].user.password) {
			userLogin.name = lecturers[i].name;
			loginMode = 2;
			delete[]lecturers;
			return;
		}
	}

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

void menu() {
	User user;
	user.username = "";
	user.password = "";
	int loginMode = 0; // 1: Staff, 2: Lecturer, 3: Student

	login(user, loginMode);

	switch (loginMode) {
	case 1:
		showStaffMenu(user);
		break;
	case 2:
		
		break;
	case 3:
		
		break;
	default:
		cout << "Wrong user name or password." << endl;
		menu();
		break;
	}
}