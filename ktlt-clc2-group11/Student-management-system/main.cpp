/*
	*COURSE: PROGRAM TECHNIQUES
	*CLASS: 19CLC2
	*GROUP: GA CHIEN
	*ID: 11

	This is the first version of Student Manegement System, built on development environment,
	it will be updated some features and public soon.

*/
/*
	We notice that in main function, it's only renders menu() function, and menu() will render the program.
*/

#include "Header.h"
#include "AllRole.h"
#include "Staff.h"
#include "Lecturers.h"
#include "Student.h"


int main() {
	/*cout << "STUDENTS MANAGEMENT SYSTEM DEMO VERSION 0.5" << endl;
	menu();*/

	//importScoreboardFromCsvToTXT();
	//editGrade();
	Student* a;
	int n, i = 0;
	importStudentsFromCSV(a,n);
	for (int i = 0; i < n; i++);
	{
		cout << a[i].fullName;
	}
	return 0;
}