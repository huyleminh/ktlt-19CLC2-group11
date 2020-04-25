#include "Lecturers.h"
#include "AllRole.h"

void showLecturerMenu() {
	cout << "**********LECTURER MENU**********" << endl;
	cout << "> 1. View list of courses in the current semester.\n";
	cout << "> 2. View list of students of a course.\n";
	cout << "> 3. View attendance list of a course.\n";
	cout << "> 4. Edit an attendance.\n";
	cout << "> 5. Import scoreboard of a course(midterm, final, lab, bonus) from a csv file.\n";
	cout << "> 6. Edit grade of a student.\n";
	cout << "> 7. View a scoreboard.\n";
	cout << "> 8. Logout and back to login menu.\n";
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
		menu();
	}
}

