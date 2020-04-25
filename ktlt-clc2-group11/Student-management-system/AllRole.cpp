/*There are 5 main roles in this section:
1. Login            : enabale user login to system.
2. Show menu		: print main menu to console.
3. View profile info: view current user profile.
4. Change password	: enable user change his/her password to login to system.
5. Logout			: logout, come back to login.
*/

#include "AllRole.h"
#include "Staff.h"

void menu() {
	User user;
	user.username = "";
	user.password = "";
	unsigned int loginMode = 0; // 1: Staff, 2: Lecturer, 3: Student

	login(user, loginMode);
	system("cls");

	switch (loginMode) {
	case 1: 
		showStaffMenu();
		break;
	case 2:
		//showLecturerMenu();
		break;
	case 3:
		//showStudentMenu();
		break;
	default: 
		cout << "Wrong user name or password." << endl;
		menu();
		break;
	}
}

void login(User user, unsigned int& loginMode) {
	cout << " > Enter your Username : "; 
	getline(cin, user.username, '\n');
	cout << " > Enter your password : ";
	getline(cin, user.password, '\n');

	if (isStaffLogin(user) == true) {
		loginMode = 1;
		return;
	}
	if (isLecturerLogin(user) == true) {
		loginMode = 2;
		return;
	}
	if (isStudentLogin(user) == true) {
		loginMode = 3;
		return;
	}
}

bool isStaffLogin(const User loginUser) {
	ifstream fin;
	if (isFileOpen(fin, "Staff.txt") == false)
		return false;

	Staff staffUser;
	int nStaff = 0;
	string ignoreLine;
	
	fin >> nStaff;
	
	while(!fin.eof()) {
		getline(fin, ignoreLine);
		getline(fin, staffUser.user.username, '\n');
		getline(fin, staffUser.user.password, '\n');
		getline(fin, staffUser.name, '\n');

		if (loginUser.username == staffUser.user.username && loginUser.password == staffUser.user.password) {
			cout << "**********WELCOME " << staffUser.name << "**********" << endl;
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

bool isLecturerLogin(const User loginUser) {
	ifstream fin; 
	if (isFileOpen(fin, "Lecturers.txt") == false)
		return false;

	Lecturer lecUser;
	int nLec;
	string ignoreLine;
	
	fin >> nLec;
	
	while (!fin.eof()) {
		getline(fin, ignoreLine);
		getline(fin, lecUser.user.username, '\n');
		getline(fin, lecUser.user.password, '\n');
		getline(fin, lecUser.name, '\n');

		if (loginUser.username == lecUser.user.username && loginUser.password == lecUser.user.password) {
			cout << "**********WELCOME " << lecUser.name << "**********" << endl;
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

bool isStudentLogin(const User loginUser) {
	ifstream fin;
	if (isFileOpen(fin, "StudentUsers.txt") == false)
		return false;

	Student_User stuUser;
	int nStu = 0;
	string ignoreLine;

	fin >> nStu;

	while (!fin.is_open()) {
		getline(fin, ignoreLine);
		getline(fin, stuUser.user.username, '\n');
		getline(fin, stuUser.user.password, '\n');
		getline(fin, stuUser.name, '\n');

		if (loginUser.username == stuUser.user.username && loginUser.password == stuUser.user.password) {
			cout << "**********WELCOME " << stuUser.name << "**********" << endl;
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}
//void showLecturerMenu() {
//
//}
//
//void showStudentMenu() {
//
//}
//
//void viewProfileInfo(){
//
//}
//
//void changePassword() {
//
//}
//
//void logout() {
//
//}
