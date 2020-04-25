#include "Student.h"
#include "AllRole.h"

void showStudentMenu() {
	cout << "**********STUDENT MENU**********" << endl;
	cout << "> 1. Check-in.\n";
	cout << "> 2. View check-in result.\n";
	cout << "> 3. View schedules.\n";
	cout << "> 4. View your scores of a course.\n";
	cout << "> 5. Logout and back to login menu.\n";

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
		menu();
	}
}