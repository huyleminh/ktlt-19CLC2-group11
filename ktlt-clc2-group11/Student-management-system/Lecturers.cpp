#include "Lecturers.h"
#include "AllRole.h"

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
	cout << "> 9. View profile infomation.\n";
	cout << "> 10. Logout and back to login menu.\n";
OPTION:
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 7)
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
		showLecturerMenu(user);
		break;
	case 9:
		viewProfile(user);
		showLecturerMenu(user);
		break;
	case 10: 
		menu();
		break;
	}
}

//8. Change password.
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