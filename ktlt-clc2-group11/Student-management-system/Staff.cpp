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
		classAndStudentMode();
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

void filterStudentToClass(string filename)
{
	ifstream in(filename);
	int nStudents;
	if (!in.is_open())
	{
		cout << "Cant open file" << endl;
		return;
	}

	in >> nStudents;

	Student* a = new Student[nStudents];

	importStudentsFromCSV(a, nStudents);

	for (int i = 0; i < nStudents; i++)
	{
		string classFile = a[i].classID + "-Students.txt";
		ofstream fout(classFile, ofstream::app);
		if (!fout.is_open())
		{
			cout << "Cant create file" << endl;
			return;
		}
		fout << a[i].ID << endl << a[i].fullName << endl << a[i].DoB << endl << a[i].gender << endl;
		fout.close();
	}
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
		fout << courses[i].active << endl;

		i++;
	}

	fin.close();
	fout.close();

	createClassCourse(courses, nCourse);
	addStudentIntoCourse();
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

//19CLC2-CS162.txt  
//19CLC2-CS160.txt
//19CLC1-CS162.txt  

//add student into file course
void splitClassID(string& str) {
	string classId = "";
	for(int i = 0; str[i] != '-'; i++) {
		classId += str[i];
	}
	str = classId;
}

void addStudentIntoCourse() {
	string fileCourse = "";
	string source = "";

	ifstream finCourse;
	if(isFileOpen(finCourse, "ListCourses.txt") == false) 
		return;

	while(!finCourse.eof()){
		getline(finCourse, fileCourse, '\n');
		source = fileCourse;
		splitClassID(source);
		source += "-Students.txt";  

		copyFile(source, fileCourse);
	}
	finCourse.close();
}

//15. Manually add a new course
void addNewCourse(int& nCourses)
{
	Course c;
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

	ofstream out;
	
	out.open("Courses.csv", ios::app);

	if (!out.is_open())
	{
		cout << "Cannot open file Courses.csv\n";
		return;
	}

	nCourses++;

	out << endl;
	out << nCourses << ",";
	out << c.ID << ",";
	out << c.name << ",";
	out << c.classID << ",";
	out << c.lecAccount << ",";
	out << c.startDate.year << "-" << c.startDate.month << "-" << c.startDate.day << ",";
	out << c.endDate.year << "-" << c.endDate.month << "-" << c.endDate.day << ",";
	out << c.courseTime.dayOfWeek << ",";
	out << c.courseTime.startHour << ":" << c.courseTime.startMin << ",";
	out << c.courseTime.endHour << ":" << c.courseTime.endMin << ",";
	out << c.room;

	out.close();
}

void loadCoursesFromTXT(string filename, Course*& courses, int n) {
	ifstream fin;
	if(isFileOpen(fin, filename) == false)
		return;

	fin >> n;
	courses = new Course[n];
	string ignore = "";

	fin.ignore(1);

	for (int i = 0; i < n; i++) {
		getline(fin, ignore, '\n');
		getline(fin, courses[i].ID, '\n');
		getline(fin, courses[i].classID, '\n');
		getline(fin, courses[i].name, '\n');
		getline(fin, courses[i].lecAccount, '\n');

		fin >> courses[i].startDate.day;
		getline(fin, ignore, '-');
		fin >> courses[i].startDate.month;
		getline(fin, ignore, '-');
		fin >> courses[i].startDate.year;
		
		fin >> courses[i].endDate.day;
		getline(fin, ignore, '-');
		fin >> courses[i].endDate.month;
		getline(fin, ignore, '-');
		fin >> courses[i].endDate.year;

		getline(fin, courses[i].courseTime.dayOfWeek);
		
		fin >> courses[i].courseTime.startHour;
		getline(fin, ignore, ':');
		fin >> courses[i].courseTime.startMin;

		fin >> courses[i].courseTime.endHour;
		getline(fin, ignore, ':');
		fin >> courses[i].courseTime.endMin;

		getline(fin, courses[i].room);
	}

	fin.close();
}

void removeCourse () {
	Course course;

	cout << "> Enter course ID: "; 
	cin >> course.ID;
	cout << "> Enter course class ID: ";
	cin >> course.classID;

	Course* courses;
	int n = 0;

	loadCoursesFromTXT("Courses.txt", courses, n);

	for(int i = 0; i < n; i++) {
		if(courses[i].ID == course.ID && courses[i].classID == course.classID) {
			courses[i].active == false;
			break;
		}
	}

	ofstream fout;
	fout.open("Courses.txt", ios::out);
	if(!fout.is_open()) {
		cout << "Can not open Courses.txt.\n";
		return;
	}

	fout << n << endl;

	for(int i = 0; i < n; i++) {
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
		fout << courses[i].active << endl;
	}
	fout.close();
}

//23. Create/Update/Delete/View all lectures

void convertToLower(string& s)
{
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		s[i] = (char)tolower(s[i]);
	}
}

void createUsername(string& username, string name)
{
	convertToLower(name);
	username = "";

	username += name[0];

	int len = name.length();

	char ignore = ' ';
	int temp = 0;

	for (int i = 1; i < len; i++)
	{
		if (name[i] == ignore)
			temp++;
	}

	for (int i = 1; i < len; i++)
	{
		if (temp != 1)
		{
			if (name[i] == ignore)
			{
				int index = i + 1;
				username += name[index];
				temp--;
			}
		}
		else
		{
			if (name[i] == ignore)
			{
				for (int j = i + 1; j < len; j++)
					username += name[j];
			}
		}
	}
}

void createNewLecturer()
{
	string name;

	cout << "Lecturer Infomation:\n";
	cout << "Enter name: ";
	getline(cin, name);

	string username;

	createUsername(username, name);

	string password;

	cout << "Enter password: ";
	getline(cin, password);

	Lecturer* lec;
	int nLec;
	loadLecturerUser(lec, nLec);

	nLec;

	ofstream data;

	data.open("Lecturers.txt");

	if (!data.is_open())
	{
		cout << "Read file error.\n";
		return;
	}

	data << nLec + 1 << endl << endl;
	for (int i = 0; i < nLec; i++)
	{
		data << lec[i].user.username << endl;
		data << lec[i].user.password << endl;
		data << lec[i].name << endl;
		data << endl;
	}

	data << username << endl;
	data << password << endl;
	data << name << endl;

	data.close();
	delete[] lec;
}

//25. Export a scoreboard to a csv file.

void getDestinationTXT(const string sourceTXT, string& destinationCSV) {
	destinationCSV = "";

	for (int i = 0; i != '.'; i++)
		destinationCSV += sourceTXT[i];
	
	destinationCSV += ".csv";
}

void export_A_ScoreboardToCsv(string sourceTXT, string destinationCSV) {
	ifstream fin;
	if(isFileOpen(fin, sourceTXT) == false)
		return;

	ofstream fout;
	fout.open(destinationCSV, ios::out);
	if(!fout.is_open()) {
		cout << "Can not open " << destinationCSV << endl;
		return;
	}

	ScoreBoard* scores;
	int nScor = 0;

	//read score from .txt
	fin.close();

	// for (int i = 0; i < nScor; i++) {
	// 	fout << nScor + 1 << ',';
	// 	fout << scores[i].studentID << ',';
	// 	fout << scores[i].name << ',';
	// 	fout << scores[i]._midTerm << ',';
	// 	fout << scores[i]._final<< ',';
	// 	fout << scores[i]._bonus << ',';
	// 	fout << scores[i]._total << endl;
	// }
	fout.close();

	//delete scores[];
}

void exportScoreBoardToCSV () {
	ifstream fin; 
	if(isFileOpen(fin, "ListScoreBoard.txt") == false) {
		cout << "Can not open ListScoreBoard.txt.\n";
		return;
	}

	string filename = "";

	while(!fin.eof()) {
		getline(fin, filename, '\n');

		string temp = filename;
		getDestinationTXT(filename, temp);

		export_A_ScoreboardToCsv(filename, temp);
	}

	fin.close();
void createDupUsername(string& username, string name)
{
	convertToLower(name);
	username = "";

	username += name[0];

	int len = name.length();

	char ignore = ' ';
	int temp = 0;

	for (int i = 1; i < len; i++)
	{
		if (name[i] == ignore)
			temp++;
	}

	for (int i = 1; i < len; i++)
	{
		if (temp != 1)
		{
			if (name[i] == ignore)
			{
				int index = i + 1;
				while (name[index] != ignore)
				{
					username += name[index];
					index++;
				}
				temp--;
			}
		}
		else
		{
			if (name[i] == ignore)
			{
				for (int j = i + 1; j < len; j++)
					username += name[j];
			}
		}
	}
}

void updateLecturer()
{
	Lecturer* lec;
	int nLec;
	loadLecturerUser(lec, nLec);

	int mode = 0;
	cout << "==========Features==========\n";
	cout << "1. Update password.\n";
	cout << "2. Fix duplicate username.\n";
	cout << "Enter mode: ";
	cin >> mode;

	if (mode == 1)
	{
		string username = "";

		cout << "Enter username: ";
		getline(cin, username);

		for (int i = 0; i < nLec; i++)
		{
			if (lec[i].user.username == username)
			{
				changePassword(lec[i].user);
				break;
			}
		}
		cout << "\nChange password successfully.\n";
	}

	if (mode == 2)
	{
		for (int i = 0; i < nLec; i++)
		{
			string username = lec[i].user.username;

			int count = 0;

			for (int j = 0; j < nLec; j++)
			{
				if (lec[j].user.username == username)
					count++;
			}

			if (count > 1)
			{

				for (int j = 0; j < nLec; j++)
				{
					if (lec[j].user.username == username)
					{
						createDupUsername(lec[j].user.username, lec[j].name);
						count--;
					}
					if (count == 1)
						break;
				}
			}
		}
		cout << "\nFix duplicate username successfully.\n";
	}

	ofstream data;

	data.open("Lecturers.txt");

	if (!data.is_open())
	{
		cout << "Read file error.\n";
		return;
	}

	data << nLec << endl << endl;
	for (int i = 0; i < nLec; i++)
	{
		data << lec[i].user.username << endl;
		data << lec[i].user.password << endl;
		data << lec[i].name << endl;
		data << endl;
	}
	data.close();
	delete[] lec;
}

void deleteLecturer()
{
	Lecturer* lec;
	int nLec;
	loadLecturerUser(lec, nLec);

	string username = "";

	cout << "Enter username to delete: ";
	getline(cin, username);

	for (int i = 0; i < nLec; i++)
	{
		if (lec[i].user.username == username)
		{
			string Pass = "";
			int numInput = 0;

			do {
				cout << "> Enter your password to delete: ";
				getline(cin, Pass, '\n');
				numInput++;
				if (numInput == 10)
				{
					cout << "> You have entered the password more than 10 times. Please try again.\n";
					return;
				}
			} while (Pass != lec[i].user.password);

			int nLecNew = nLec - 1;
			Lecturer* newLec = new Lecturer[nLecNew];
			int k = 0;
			for (int j = 0; j < nLec; j++)
			{
				if (lec[j].user.username != username)
				{
					newLec[k] = lec[j];
					k++;
				}
			}

			ofstream data;

			data.open("Lecturers.txt");

			if (!data.is_open())
			{
				cout << "Read file error.\n";
				return;
			}

			data << nLecNew << endl << endl;
			for (int i = 0; i < nLecNew; i++)
			{
				data << newLec[i].user.username << endl;
				data << newLec[i].user.password << endl;
				data << newLec[i].name << endl;
				data << endl;
			}
			data.close();
			delete[] lec;
			delete[] newLec;
			cout << "\nDelete lecturer " << username << " successfully.\n";
			return;
		}
	}
}

void viewAllLecturers()
{
	Lecturer* lec;
	int nLec;
	loadLecturerUser(lec, nLec);

	cout << "List of lecturers:";

	for (int i = 0; i < nLec; i++)
	{
		cout << "\nLecturer #" << i + 1 << ":" << endl;
		cout << "Username: " << lec[i].user.username << endl;
		cout << "Name: " << lec[i].name << endl;
		cout << endl;
	}
	delete[] lec;
}

void editLecturers()
{
	int mode;
	cout << "==========Features==========\n";
	cout << "1. Create new lecturer.\n";
	cout << "2. Update a lecturer.\n";
	cout << "3. Delete a lecturer.\n";
	cout << "4. View all lecturers.\n";
	cout << "Enter mode: ";
	cin >> mode;
	cout << endl;

	switch (mode)
	{
	case 1:
		createNewLecturer();
		break;
	case 2:
		updateLecturer();
		break;
	case 3:
		deleteLecturer();
		break;
	case 4:
		viewAllLecturers();
		break;
	default:
		cout << "Invalid Mode.\n";
	}
}