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
	if (option < 1 || option > 6)
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
		addStudentToClass();
		classAndStudentMode();
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

void addStudentToClass() {
	Student newStudent;

	cout << "> Enter student infomation: \n";
	cout << " Full name: "; getline(cin, newStudent.fullName, '\n');
	cout << " ID: "; getline(cin, newStudent.ID, '\n');
	cout << " Gender: "; getline(cin, newStudent.gender, '\n');
	cout << " Date of birth: "; getline(cin, newStudent.DoB, '\n');
	cout << " Class ID: "; getline(cin, newStudent.classID, '\n');

	User newUser;

	newUser.name = newStudent.fullName;
	newUser.username = newStudent.ID;
	newUser.password = newStudent.DoB;

	ofstream fout;
	
	fout.open("Students.txt", ios::app); 
	if (!fout.is_open()) {
		cout << "Can not open Students.txt\n";
		return;
	}

	fout << endl << newStudent.ID << endl << newStudent.fullName << endl << newStudent.gender << endl <<
		newStudent.DoB << endl << newStudent.classID << endl;
	fout.close();

	fout.open("StudentUsers.txt", ios::app);
	if (!fout.is_open()) {
		cout << "Can not open StudentUsers.txt\n";
		return;
	}

	fout << newUser.username << endl << newUser.password << endl << newUser.name << endl;
	fout.close();

	string file = newStudent.classID + "-Students.txt";

	fout.open(file, ios::app);
	if (!fout.is_open()) {
		cout << "Can not open Students.txt\n";
		return;
	}

	fout << endl << newStudent.ID << endl << newStudent.fullName << endl << newStudent.gender << endl <<
		newStudent.DoB << endl << newStudent.classID << endl;

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
void getListClass(int& n, string*& Class)
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
		getline(data, Class[i], '\n');
		cout << i << ". " << Class[i] << endl;
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
		case 1: 
			deleteStudent(Class[buffer]);
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


//Course mode:
void courseMode() {
	cout << "> 1. Edit academic years and semesters.\n";
	cout << "> 2. Import courses from csv file to txt file.\n";
	cout << "> 3. Manually add a new course.\n";
	cout << "> 4. Edit an existing course.\n";
	cout << "> 5. Remove a course.\n";
	cout << "> 6. Remove a specific student from a course.\n";
	cout << "> 7. Add a specific student to a course.\n";
	cout << "> 8. View list of courses in the current semester.\n";
 	cout << "> 9. View list of students of a course.\n";
	cout << "> 10. View attendance list of a course.\n";
	cout << "> 11. Create / update / delete / view all lecturers.\n";
	cout << "> 12. Back to staff menu.\n";

OPTION:
	int option = 0;

	cout << "> Which mode do you want to access ? \n";
	cin >> option;
	if (option < 1 || option > 12)
		goto OPTION;

	Course *courses;
	int nCourse = 0;

	switch (option)
	{
	case 1:
		break;
	case 2:
		//importCoursesFromCsvFile(courses, nCourse);
		courseMode();
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
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	}
}

//14
void importCoursesFromCsvFile(Course*& courses, int& nCourse) {
	ifstream fin;
	if (isFileOpen(fin, "Courses.csv") == false)
		return;

	ofstream fout;
	fout.open("Courses.txt", ios::out);
	if (!fout.is_open()) {
		cout << "Can not open Courses.txt.\n";
		return;
	}

	string ignore = "";
	while (!fin.eof()) {
		getline(fin, ignore, '\n');
		nCourse++;
	}

	courses = new Course[nCourse];
	fout << nCourse << endl;

	ignore = "";

	fin.seekg(0, fin.beg);
	int i = 0;
	while (!fin.eof())
	{
		getline(fin, ignore, ',');

		getline(fin, courses[i].ID, ',');

		getline(fin, courses[i].name, ',');

		getline(fin, courses[i].classID, ',');

		getline(fin, courses[i].lecAccount, ',');

		fin >> courses[i].startDate.year;
		getline(fin, ignore, '-');
		fin >> courses[i].startDate.month;
		getline(fin, ignore, '-');
		fin >> courses[i].startDate.day;
		getline(fin, ignore, ',');

		fin >> courses[i].endDate.year;
		getline(fin, ignore, '-');
		fin >> courses[i].endDate.month;
		getline(fin, ignore, '-');
		fin >> courses[i].endDate.day;
		getline(fin, ignore, ',');

		getline(fin, courses[i].courseTime.dayOfWeek, ',');

		getline(fin, courses[i].courseTime.startHour, ':');
		getline(fin, courses[i].courseTime.startMin, ',');

		getline(fin, courses[i].courseTime.endHour, ':');
		getline(fin, courses[i].courseTime.endMin, ',');

		getline(fin, courses[i].room, '\n');

		fout << endl << courses[i].ID << endl;
		fout << courses[i].name << endl;
		fout << courses[i].classID << endl;
		fout << courses[i].lecAccount << endl;
		fout << courses[i].startDate.year << '-' << courses[i].startDate.month << '-' << courses[i].startDate.day << endl;
		fout << courses[i].endDate.year << '-' << courses[i].endDate.month << '-' << courses[i].endDate.day << endl;
		fout << courses[i].courseTime.dayOfWeek << endl;
		fout << courses[i].courseTime.startHour << ':' << courses[i].courseTime.startMin << endl;
		fout << courses[i].courseTime.endHour << ':' << courses[i].courseTime.endMin << endl;
		fout << courses[i].room << endl;

		i++;
	}

	fin.close();
	fout.close();
}

//Create course-class file 
void createClassCourse(Course*& courses, const int nCourse) {
	ofstream f;
	f.open("ListCourses.txt");
	if(!f.is_open()){
		cout << "Can not open ListCourses.txt.\n";
		return;
	}
	
	string filename = "";
	convertToUpper(courses[0].classID);
	convertToUpper(courses[0].ID);
	filename += courses[0].classID + "-" + courses[0].ID + ".txt";
	
	f << filename << endl;

	ofstream fout;
	fout.open(filename);
	if (!fout.is_open()) {
		cout << "Can not open " << filename << endl;
		return;
	}
	fout.close();

	for (int i = 1; i < nCourse; i++) {
		if (courses[i].classID == courses[i - 1].classID && courses[i].ID == courses[i - 1].ID)
			continue;
		filename = "";
		convertToUpper(courses[i].classID);
		convertToUpper(courses[i].ID);
		filename += courses[i].classID + "-" + courses[i].ID + ".txt";

		f << filename << endl;

		ofstream fout;
		fout.open(filename);
		if (!fout.is_open()) {
			cout << "Can not open " << filename << endl;
			return;
		}
		fout.close();
	}

	f.close();
}

//add student into file course
void addStudentIntoCourse() {
	Student* students;
	int nstu;

}

//15. Manually add a new course
void addNewCourse(Course& c)
{
	cout << "Enter course ID: ";
	getline(cin, c.ID);
	cout << endl;
	
	cout << "Enter course name: ";
	getline(cin, c.name);
	cout << endl;

	cout << "Enter class: ";
	getline(cin, c.classID);
	convertToUpper(c.classID);
	cout << endl;

	cout << "Enter lecturer account: ";
	getline(cin, c.lecAccount);
	cout << endl;

	cout << "Enter start date:\n";
	cout << "Day: ";
	cin >> c.startDate.day;
	cout << "Month: ";
	cin >> c.startDate.month;
	cout << "Year: ";
	cin >> c.startDate.year;
	cout << endl;

	cout << "Enter end date:\n";
	cout << "Day: ";
	cin >> c.endDate.day;
	cout << "Month: ";
	cin >> c.endDate.month;
	cout << "Year: ";
	cin >> c.endDate.year;
	cout << endl;

	cin.ignore(1);

	cout << "Enter day of week: ";
	getline(cin, c.courseTime.dayOfWeek);
	cout << endl;

	cout << "Enter start hour: ";
	getline(cin, c.courseTime.startHour);
	cout << "Enter start min: ";
	getline(cin, c.courseTime.startMin);
	cout << endl;

	cout << "Enter end hour: ";
	getline(cin, c.courseTime.endHour);
	cout << "Enter end min: ";
	getline(cin, c.courseTime.endMin);
	cout << endl;

	cout << "Enter room: ";
	getline(cin, c.room);
	convertToUpper(c.room);
	cout << endl;
}
