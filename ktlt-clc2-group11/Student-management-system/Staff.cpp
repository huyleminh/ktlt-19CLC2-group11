#include "Staff.h"
#include "AllRole.h"

void showStaffMenu(User& user) {
	cout << "**********STAFF MENU**********" << endl;
	cout << "> 1. Class and student.\n";
	cout << "> 2. Course.\n";
	cout << "> 3. Scoreboard.\n";
	cout << "> 4. Attendance list.\n";
	cout << "> 5. Change password.\n";
	cout << "> 6. View profile information.\n";
	cout << "> 7. Logout, back to login menu.\n";

OPTION: 
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 7)
		goto OPTION;

	switch (option)
	{
	case 1: 
		//call class and student
		break;
	case 2:
		//call course
		break;
	case 3:
		//call scoreboard
		break;
	case 4: 
		//call attendance list
		break;
	case 5:
		changeStaffPassword(user);
		showStaffMenu(user);
	case 6:
		viewProfile(user);
		showStaffMenu(user);
	case 7: 
		menu();
	}
}

void classAndStudentMode() {
	cout << "> 1. Import students from csv file.\n";
	cout << "> 2. Add a student to a class.\n";
	cout << "> 3. Edit existing student.\n";
	cout << "> 4. View list of classes.\n";
	cout << "> 5. View list of student in class.\n";
	cout << "> 6. Back to staff menu.\n";

OPTION:
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 4)
		goto OPTION;

	Student* students;
	int nStudent = 0;

	switch (option)
	{
	case 1:
		importStudentsFromCSV(students, nStudent);
		createUserPassword(students, nStudent);
		classAndStudentMode();
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
	}
}

//void edit


void importStudentsFromCSV(Student*& students, int& nStudent) {
	ifstream fin;
	if (isFileOpen(fin, "Students.csv") == false)
		return;

	ofstream fout;
	fout.open("Students.txt");
	if (!fout.is_open()) {
		cout << "Can not open Students.txt" << endl;
		return;
	}

	nStudent = 0;
	string ignore = "";
	while (!fin.eof()) {
		getline(fin, ignore, '\n');
		++nStudent;
	}
	students = new Student[nStudent];
	
	fin.seekg(0, fin.beg);
	ignore = "";
	int i = 0;
	
	fout << nStudent << endl;
	while (!fin.eof()) {
		//Read each line in csv 
		getline(fin, ignore, ',');
		getline(fin, students[i].ID, ',');
		getline(fin, students[i].fullName, ',');
		getline(fin, students[i].gender, ',');
		getline(fin, students[i].DoB, ',');
		getline(fin, students[i].classID, '\n');
		//Export to Students.txt
		fout << endl << students[i].ID << endl << students[i].fullName << endl << students[i].gender << endl << students[i].DoB << endl << students[i].classID << endl;
		i++;
	}
	fin.close();
	fout.close();
}

void createUserPassword(Student* students, const int nStudent) {
	ofstream fout;
	fout.open("StudentUsers.txt");
	if (!fout.is_open()) {
		cout << "Can not open StudentUsers.txt" << endl;
		return;
	}

	fout << nStudent << endl;
	for (int i = 0; i < nStudent; i++) {
		fout << endl << students[i].ID << endl;
		fout << students[i].DoB << endl;
		fout << students[i].fullName << endl;
	}

	fout.close();
}
// viewFunction
///remember delete dynamic array when call this  function
void getListClass(int& n,string*&Class)
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
	cout << "List of Classes:\n\n";
	int i = -1;
	while (!data.eof())
	{
		++i;
		getline(data,Class[i], '\n');
		cout <<i<<". "<<Class[i]<< endl;
	}
	data.close();
}

///remember delete dynamic array when call this  function
void getListStudents(string classID,Student*&Students,int &nStudents)
{
	ifstream data;
	string inputPath = "";
	string extension = "-Students.txt";
	convertToUpper(classID);
	inputPath = classID + extension;
	
	data.open(inputPath);

	if (!data.is_open()) {
		cout << "Can not open file" << endl;
		return;
	}
	string buff;
	data >> nStudents;
	Students = new Student[nStudents];
	getline(data, buff, '\n');

	cout << "Total students in class " << classID << " is " << nStudents << endl << endl;
	cout << "List of students in class " << classID << ":\n\n";
	int i = -1;
	while (!data.eof())
	{
		++i;
		getline(data, buff, '\n');
		cout << "Name: " << buff << endl;

		getline(data, buff, '\n');
		cout << "ID  : " << buff << endl;

		getline(data, buff, '\n');
		cout << "active  : " << buff << endl;
	}
	data.close();
}

void saveStudent(Student* Students,int nStudent,string fclass) {
	ofstream data;
	data.open(fclass);
	if (!data.is_open()) {
		cout << "can't open file " << fclass;
	}
	else {
		data << nStudent<<endl;
		for (int i = 0; i < nStudent; i++) {
			data << Students[i].ID;
			data << Students[i].fullName;
			data << Students[i].gender;
			data << Students[i].DoB;
			data << Students[i].active;
		}
	}
	delete[] Students;
	data.close();
}

void deleteStudent(string Aclass) {
	Student* Students;
	int nStudents;
	getListStudents(Aclass, Students, nStudents);
	string ID;
	cout << "Input ID want to delete :"; cin >> ID;
	bool flag = true;
	for (int i = 0; i < nStudents; i++) {
		if (Students[i].ID == ID) {
			Students[i].active = false;
			flag = true;
		}
		break;
	}
	if (flag == true) {
		cout << "Don't have ID <" << ID << "> in this class.\n";
	}
	else
	{
		string inputPath = "";
		string extension = "-Students.txt";
		inputPath = Aclass + extension;
		saveStudent(Students, nStudents, inputPath);
	}
}

void Changeclass(string origin, string des) {
	Student* Students,*Students2;
	int nStudents,nStudents2;
	getListStudents(origin, Students, nStudents);
	getListStudents(des, Students2, nStudents2);
	string ID;
	cout << "Input ID want to delete :"; cin >> ID;
	bool flag = true;
	for (int i = 0; i < nStudents; i++) {
		if (Students[i].ID == ID) {
			nStudents2 += 1;
			Students2[nStudents2] = Students[i];
			Students[i].active = false;
			flag = false;
		}
		break;
	}
	if (flag == true) {
		cout << "Don't have ID <" << ID << "> in this class.\n";
	}
	else
	{
		string inputPath = "";
		string extension = "-Students.txt";
		inputPath = origin + extension;
		saveStudent(Students, nStudents, inputPath);
		inputPath = des + extension;
		saveStudent(Students2, nStudents2, inputPath);
	}
}

void Edit() {
	string* Class;
	int n;
	getListClass(n, Class);
	int buffer,buffer2;
	cout << "choose your class you want to edit:\n";
	cin >> buffer;
	cout << "Choose mode:\n";
	cin >> buffer2;
	cout << "1.delete a student.\n";
	cout << "2. change class a student.\n";
	switch (buffer2) {
		case 1: deleteStudent(Class[buffer]);
		break;
		case 2:
			int buffer3;
			cout << "choose class destination :";
			cin >> buffer3;
			Changeclass(Class[buffer], Class[buffer3]);
			break;
		default:
			cout << "Error";
	}
	delete[] Class;
}

void viewListStudents(string classID)
{
	ifstream data;

	string inputPath = "";
	string extension = "-Students.txt";
	convertToUpper(classID);
	inputPath = classID + extension;

	data.open(inputPath);

	if (!data.is_open()) {
		cout << "Can not open file" << endl;
		return;
	}

	string buff;
	int nStudents;
	data >> nStudents;

	getline(data, buff, '\n');

	cout << "Total students in class " << classID << " is " << nStudents << endl << endl;
	cout << "List of students in class " << classID << ":\n\n";

	while (!data.eof())
	{
		getline(data, buff, '\n');
		cout << "Name: " << buff << endl;
		getline(data, buff, '\n');
		cout << "ID  : " << buff << endl;
	}
	data.close();
}

void convertToUpper(string& s)
{
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		s[i] = (char)toupper(s[i]);
	}
}

//Change password
void changeStaffPassword(User& user) {
	Staff* staffs;
	int n = 0;

	changePassword(user);
	loadStaffUser(staffs, n);
	for (int i = 0; i < n; i++) {
		if (user.username == staffs[i].user.username) {
			staffs[i].user.password = user.password;
			break;
		}
	}

	ofstream fout("Staff.txt");
	fout << n << endl;
	for (int i = 0; i < n; i++) {
		fout << staffs[i].user.username << endl << staffs[i].user.password << endl << staffs[i].name << endl;
	}

	fout.close();
	delete[]staffs;
}
//1.
//2.
//3.
