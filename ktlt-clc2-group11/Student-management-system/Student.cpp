#include "Student.h"
#include "AllRole.h"

void showStudentMenu(User& user) {
	cout << "**********STUDENT MENU**********" << endl;
	cout << "> 1. Check-in.\n";
	cout << "> 2. View check-in result.\n";
	cout << "> 3. View schedules.\n";
	cout << "> 4. View your scores of a course.\n";
	cout << "> 5. Change password.\n";
	cout << "> 6. View profile infomation.\n";
	cout << "> 7. Logout and back to login menu.\n";

OPTION:
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 5)
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
		showStudentMenu(user);
		break;
	case 6: 
		viewProfile(user);
		showStudentMenu(user);
		break;
	case 7: 
		menu();
		break;
	}
}

//5. Change password.
void changeStudentPassword(User& user) {
	Student_User* students;
	int n = 0;

	changePassword(user);
	loadStudentUser(students, n);
	for (int i = 0; i < n; i++) {
		if (user.username == students[i].user.username) {
			students[i].user.password = user.password;
			break;
		}
	}

	ofstream fout("StudentUsers.txt");
	fout << n << endl;
	for (int i = 0; i < n; i++) {
		fout << students[i].user.username << endl << students[i].user.password << endl << students[i].name << endl;
	}

	fout.close();
	delete[]students;
}
