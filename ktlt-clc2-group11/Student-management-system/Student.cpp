#include "Student.h"
#include "AllRole.h"
#include "Staff.h"
#pragma warning(disable : 4996)
/*Main student menu*/

void showStudentMenu(User& user) {
	cout << "**********STUDENT MENU**********" << endl;
	cout << "> 1. Check-in.\n";
	cout << "> 2. View check-in result.\n";
	cout << "> 3. View schedules.\n";
	cout << "> 4. View your scores of a course.\n";
	cout << "> 5. Change password.\n";
	cout << "> 6. View student profile infomation.\n";
	cout << "> 7. Logout.\n";
	cout << "> 8. Exit app.\n";

OPTION:
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 8)
		goto OPTION;

	switch (option)
	{
	case 1:
		checkIn(user.username);
		break;
	case 2:
		checkInResult(user.username);
		break;
	case 3:
		viewSchedule();
		break;
	case 4:
		//
		break;
	case 5:
		changeStudentPassword(user);
		break;
	case 6: 
		viewProfile(user);
		break;
	case 7: 
		return;
	case 8:
		exit(0);
	}
	showStudentMenu(user);
}

//1. Check-in.
bool checkStudentInCourse(string ID, string filename, bool& flag) {
	fstream in;
	in.open(filename, ios::in);
	if (!in.is_open()) {
		cout << "Cant open file " << filename << endl;
		flag = false;
		return true;
	}
	string buff;
	while (!in.eof()) {
		getline(in, buff);
		if (buff == ID)
			return true;
	}
	return false;
	in.close();
}

void checkIn(string ID)
{
	bool flag = false;
	string Class, course;
	int buff;

OPTION:
	cout << "1.Input/Input again Class and course \n";
	cout << "2.Back to menu\n";
	cin >> buff;

	if (buff == 2)
		return;

	cin.ignore(1);

	cout << "Input your class:"; cin >> Class;
	cout << "Input your course :"; cin >> course;

	convertToUpper(Class);
	convertToUpper(course);

	string path = Class + "-" + course + ".txt";
	if (checkStudentInCourse(ID, path, flag)) {
		if (flag) {
			cout << "Please input again\n";
			goto OPTION;
		}
	}
	else
	{
		cout << "This ID <" << ID << "> doesn't exist in this course\n";
		cout << "Please input again\n";
		goto OPTION;
	}


	ofstream out;
	path = Class + "-" + course + "-checkin.txt";
	out.open(path, ios::app);
	time_t curtime = time(NULL);
	time(&curtime);
	string time = ctime(&curtime);
	out << ID << endl;
	out << time << endl;
	out.close();
	cout << "\nCheck in successfully.\n";
}

//2. View check-in result.
void checkInResult(string ID) {
	string path, Class, course, time, buff;
	int buff1;
OPTION2:
	cout << "1. Input/Input again Class and course \n";
	cout << "2. Back to menu\n";
	cin >> buff1;
	if (buff1 == 2)
		return;

	cout << "Input your class:"; cin >> Class;
	cout << "Input your course :"; cin >> course;

	convertToUpper(Class);
	convertToUpper(course);

	ifstream in;
	path = Class + "-" + course + "-checkin.txt";
	in.open(path);
	if (!in.is_open()) {
		cout << "Cant open file " << path << endl;
		cout << "Please input again" << endl;
		goto OPTION2;
	}

	bool flag = true;
	system("cls");
	cout << "\n==========Information==========\n";
	cout << "ID:" << ID << endl;
	while (!in.eof()) {
		getline(in, buff);
		//in.ignore(1);
		getline(in, time);
		if (buff == ID)
		{
			flag = false;
			cout << time << endl;
		}
		getline(in, buff);
	}
	if (flag) {
		cout << " NO DATA\n";
	}
	in.close();
}
//3. View schedules.
void loadListClass(int& n, string*& Class)
{
	ifstream data;
	data.open("Classes.txt");

	if (!data.is_open()) {
		cout << "Can not open Classes.txt" << endl;
		return;
	}
	data >> n;
	Class = new string[n];
	data.ignore(1);
	int i = -1;
	while (!data.eof())
	{
		++i;
		getline(data, Class[i], '\n');
	}
	data.close();
}

void createScheduleFile()
{
	int nCourses;
	Course* c;

	loadCoursesFromTXT("Courses.txt", c, nCourses);

	string* classes;
	int nClasses;

	loadListClass(nClasses, classes);

	for (int i = 0; i < nClasses; i++)	
	{
		string filename = "";
		filename = classes[i] + "-Schedule.txt";

		fstream f;

		f.open(filename, ios::out);

		if (!f.is_open())
		{
			cout << "Create " << filename << " error.\n";
			return;
		}

		int k = 0;
		for (int j = 0; j < nCourses; j++)
		{
			if (c[j].classID == classes[i])
			{
				k++;
				if (k == 1)
				{
					f << c[j].ID << endl;
					f << c[j].name << endl;
					f << c[j].classID << endl;
					f << c[j].lecAccount << endl;
					f << c[j].startDate.day << "-" << c[j].startDate.month << "-" << c[j].startDate.year << endl;
					f << c[j].endDate.day << "-" << c[j].endDate.month << "-" << c[j].endDate.year << endl;
					f << c[j].courseTime.dayOfWeek << endl;
					f << c[j].courseTime.startHour << ":" << c[j].courseTime.startMin << endl;
					f << c[j].courseTime.endHour << ":" << c[j].courseTime.endMin << endl;
					f << c[j].room << endl;
				}
				else
				{
					f << endl;
					f << c[j].ID << endl;
					f << c[j].name << endl;
					f << c[j].classID << endl;
					f << c[j].lecAccount << endl;
					f << c[j].startDate.day << "-" << c[j].startDate.month << "-" << c[j].startDate.year << endl;
					f << c[j].endDate.day << "-" << c[j].endDate.month << "-" << c[j].endDate.year << endl;
					f << c[j].courseTime.dayOfWeek << endl;
					f << c[j].courseTime.startHour << ":" << c[j].courseTime.startMin << endl;
					f << c[j].courseTime.endHour << ":" << c[j].courseTime.endMin << endl;
					f << c[j].room << endl;
				}
			}
		}
		f.close();
	}
	delete[] c;
	delete[] classes;
	return;
}

void viewSchedule()
{
	createScheduleFile();

	cin.ignore(1);
	string classID = "";

	cout << "Enter class: ";
	getline(cin, classID);
	cout << endl;

	convertToUpper(classID);

	string filename = classID + "-Schedule.txt";

	fstream f;

	f.open(filename, ios::in);

	if (!f.is_open())
	{
		cout << "Cannot find " << classID << "-Schedule.\n";
		return;
	}

	string ignore = "";
	string buffer = "";
	cout << "==========" << classID << "-Schedule==========\n";
	int i = 1;
	while (!f.eof())
	{
		cout << "#" << i << ":\n";
		getline(f, buffer, '\n');
		cout << "Course ID         : " << buffer << endl;
		getline(f, buffer, '\n');
		cout << "Course Name       : " << buffer << endl;
		getline(f, buffer, '\n');
		cout << "Class ID          : " << buffer << endl;
		getline(f, buffer, '\n');
		cout << "Lecturer Username : " << buffer << endl;
		getline(f, buffer, '\n');
		cout << "Start Date        : " << buffer << endl;
		getline(f, buffer, '\n');
		cout << "End Date          : " << buffer << endl;
		getline(f, buffer, '\n');
		convertToUpper(buffer);
		cout << "Day Of Week       : " << buffer << endl;
		getline(f, buffer, '\n');
		cout << "Start Hour        : " << buffer << endl;
		getline(f, buffer, '\n');
		cout << "End Hour          : " << buffer << endl;
		getline(f, buffer, '\n');
		cout << "Room              : " << buffer << endl;
		getline(f, buffer, '\n');
		cout << endl;
		i++;
	}
	f.close();
}
//4. View your scores of a course.

//5. Change password.
void changeStudentPassword(User& user) {
	Student_User* students;
	int n = 0;

	cin.ignore(1);
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
		fout << endl << students[i].user.username << endl << students[i].user.password << endl << students[i].name << endl;
	}

	fout.close();
	delete[]students;
}

//6. View student profile infomation.
//this function is located in Header.h

//7. Logout.
