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
		viewSchedule(user);
		break;
	case 4:
		viewScore(user);
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
	
	ifstream fin;
	Student* s;
	int n = 0;

	loadStudent(fin, "Students.txt", s, n);

	string classID = "";
	for (int i = 0; i < n; i++)
		if (s[i].ID == ID)
		{
			classID = s[i].classID;
			break;
		}

	delete[] s;

	Course* c;
	int nCourses;

	loadClassSchedule(classID, nCourses, c);

	int index = 0;
	cout << "==========Your_Courses==========\n";
	for (int i = 0; i < nCourses; i++)
	{
		cout << "#" << i + 1 << endl;
		cout << "Course ID         : " << c[i].ID << endl;
		cout << "Course Name       : " << c[i].name << endl;
		cout << endl;
	}
	cout << "================================\n\n";
	cout << "Enter course you want to check in (by number): ";
	cin >> index;

	index--;
	course = c[index].ID;
	cout << endl;

OPTION:
	//cout << "1.Input/Input again Class and course \n";
	cout << "1. Check in \n";
	cout << "2. Back to menu\n";
	cin >> buff;

	if (buff == 2)
		return;

	cin.ignore(1);
	Class = classID;
	//cout << "Input your class:"; cin >> Class;
	//cout << "Input your course :"; cin >> course;

	//convertToUpper(Class);
	//convertToUpper(course);

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
	delete[] c;
}

//2. View check-in result.
void checkInResult(string ID) {
	string path, Class, course, time, buff;
	int buff1;

	ifstream fin;
	Student* s;
	int n = 0;

	loadStudent(fin, "Students.txt", s, n);

	string classID = "";
	for (int i = 0; i < n; i++)
		if (s[i].ID == ID)
		{
			classID = s[i].classID;
			break;
		}

	delete[] s;

	Course* c;
	int nCourses;

	loadClassSchedule(classID, nCourses, c);

	int index = 0;
	cout << "==========Your_Courses==========\n";
	for (int i = 0; i < nCourses; i++)
	{
		cout << "#" << i + 1 << endl;
		cout << "Course ID         : " << c[i].ID << endl;
		cout << "Course Name       : " << c[i].name << endl;
		cout << endl;
	}
	cout << "================================\n\n";
	cout << "Enter course you want view check in (by number): ";
	cin >> index;

	index--;
	course = c[index].ID;
	Class = classID;
	cout << endl;

OPTION2:
	//cout << "1. Input/Input again Class and course \n";
	cout << "1. View \n";
	cout << "2. Back to menu\n";
	cin >> buff1;
	if (buff1 == 2)
		return;

	//cout << "Input your class:"; cin >> Class;
	//cout << "Input your course :"; cin >> course;

	//convertToUpper(Class);
	//convertToUpper(course);

	ifstream in;
	path = Class + "-" + course + "-checkin.txt";
	in.open(path);
	if (!in.is_open()) {
		cout << "Cant open file " << path << endl;
		cout << "Please input again" << endl;
		goto OPTION2;
	}

	bool flag = true;

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
	delete[] c;
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
	data.ignore();
	Class = new string[n];
	for (int i = 0; i < n; i++)
		getline(data, Class[i], '\n');
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
					f << c[j].startDate.year << "-" << c[j].startDate.month << "-" << c[j].startDate.day << endl;
					f << c[j].endDate.year << "-" << c[j].endDate.month << "-" << c[j].endDate.day << endl;
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
					f << c[j].startDate.year << "-" << c[j].startDate.month << "-" << c[j].startDate.day << endl;
					f << c[j].endDate.year << "-" << c[j].endDate.month << "-" << c[j].endDate.day << endl;
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

void viewSchedule(User u)
{
	//createScheduleFile();

	ifstream fin;
	Student* s;
	int n = 0;

	loadStudent(fin, "Students.txt", s, n);

	string classID = "";
	for (int i = 0; i < n; i++)
		if (s[i].ID == u.username)
		{
			classID = s[i].classID;
			break;
		}

	delete[] s;

	string filename = classID + "-Schedule.txt";

	fstream f;

	f.open(filename, ios::in);

	if (!f.is_open())
	{
		cout << "Can not find " << classID << "-Schedule.txt\n";
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
void loadClassSchedule(string classID, int& n, Course*& courses)
{
	string filename = classID + "-Schedule.txt";
	fstream f;

	f.open(filename, ios::in);

	if (!f.is_open())
		return;

	int temp = 0;
	string ignore = "";
	while (!f.eof())
	{
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		getline(f, ignore, '\n');
		temp++;
	}

	f.close();

	f.open(filename, ios::in);

	if (!f.is_open())
		return;

	courses = new Course[temp];
	n = temp;

	int i = 0;
	while (!f.eof())
	{
		getline(f, courses[i].ID, '\n');
		getline(f, courses[i].name, '\n');
		getline(f, courses[i].classID, '\n');
		getline(f, courses[i].lecAccount, '\n');
		string temp = "";
		getline(f, temp, '-');
		courses[i].startDate.year = stoi(temp);
		getline(f, temp, '-');
		courses[i].startDate.month = stoi(temp);
		getline(f, temp, '\n');
		courses[i].startDate.day = stoi(temp);
		getline(f, temp, '-');
		courses[i].endDate.year = stoi(temp);
		getline(f, temp, '-');
		courses[i].endDate.month = stoi(temp);
		getline(f, temp, '\n');
		courses[i].endDate.day = stoi(temp);
		getline(f, courses[i].courseTime.dayOfWeek, '\n');
		getline(f, courses[i].courseTime.startHour, ':');
		getline(f, courses[i].courseTime.startMin, '\n');
		getline(f, courses[i].courseTime.endHour, ':');
		getline(f, courses[i].courseTime.endMin, '\n');
		getline(f, courses[i].room, '\n');
		getline(f, ignore, '\n');
		i++;
	}
	f.close();
}

void viewScore(User u)
{
	createScheduleFile();
	ifstream f;
	Student* s;
	int n = 0;

	loadStudent(f, "Students.txt", s, n);

	string classID = "";
	for (int i = 0; i < n; i++)
		if (s[i].ID == u.username)
		{
			classID = s[i].classID;
			break;
		}
	Course* c;
	int nCourses;

	loadClassSchedule(classID, nCourses, c);
	bool flag = false;
	int index = 0;
	cout << "==========Your_Courses==========\n";
	for (int i = 0; i < nCourses; i++)
	{
		cout << "#" << i + 1 << endl;
		cout << "Course ID         : " << c[i].ID << endl;
		cout << "Course Name       : " << c[i].name << endl;
		cout << endl;
		flag = true;
	}
	if (flag == false)
		cout << "No Data.\n";
	cout << "================================\n\n";
OPTION:
	if (flag == true)
		cout << "Enter course you want to view scores (by number): ";
	else
		return;
	cin >> index;
	if ((index < 1) || (index > nCourses))
		goto OPTION;
	index--;

	string fileScore = classID + "-" + c[index].ID + "-" + "Scoreboard.txt";

	fstream file;

	file.open(fileScore, ios::in);

	if (!file.is_open())
	{
		cout << "Cannot find " << fileScore << ".\n";
		return;
	}

	string buffer = "";

	cout << "\n================================\n\n";
	cout << "Course ID         : " << c[index].ID << endl;
	cout << "Course Name       : " << c[index].name << endl;
	cout << endl;
	cout << "=============Scores=============\n\n";
	while (!file.eof())
	{
		getline(file, buffer, '\n');
		if (buffer == u.username)
		{
			getline(file, buffer, '\n');
			getline(file, buffer, '\n');
			cout << "Midterm : " << buffer << endl;
			getline(file, buffer, '\n');
			cout << "Final   : " << buffer << endl;
			getline(file, buffer, '\n');
			cout << "Bonus   : " << buffer << endl;
			getline(file, buffer, '\n');
			cout << "Total   : " << buffer << endl;
			break;
		}
	}
	cout << "\n================================\n\n";
	file.close();
	delete[] s;
	delete[] c;
}

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
//this function is located in Header.cpp

//7. Logout.
