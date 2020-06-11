#include "Staff.h"
#include "AllRole.h"

/*Main staff menu*/  

void showStaffMenu(User& user) {
	cout << "**********STAFF MENU**********" << endl;
	cout << "> 1. Class and student.\n";
	cout << "> 2. Course.\n";
	cout << "> 3. Scoreboard.\n";
	cout << "> 4. Attendance list.\n";
	cout << "> 5. Change your password.\n";
	cout << "> 6. View your profile information.\n";
	cout << "> 7. Logout.\n";
	cout << "> 8. Exit app.\n";

OPTION: 
	cout << "> Which mode do you want to access ?\n";
	
	int option = 0;
	cin >> option;
	if (option < 1 || option > 8)
		goto OPTION;

	switch (option)
	{
		case 1: 
			classAndStudentMode();
			break;
		case 2:
			courseMode();
			break;
		case 3:
			scoreBoardMode();
			break;
		case 4: 
			attendanceListMode();
			break;
		case 5:
			changeStaffPassword(user);
			cout << "Change password successfully.\n";
			cout << "===================================\n";
			break;
		case 6:
			viewProfile(user);
			cout << "===================================\n";
			break;
		case 7: 
			return;
		case 8: 
			exit(0);
	}
	showStaffMenu(user);
}

//**1. Class and student.
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
	
	int nClass = 0;
	string* Class;
	string classID = ""; //case 5

	switch (option)
	{
	case 1:
		filterStudentToClass("Students.txt");
		cout << "Import successfully.\n";
		cout << "===================================\n";
		break;
	case 2:
		addStudentToClass();
		cout << "Add successfully.\n";
		cout << "===================================\n";
		break;
	case 3:
		Edit(); 
		break;
	case 4:
		getListClass(nClass, Class);
		cout << "===================================\n";
		delete[] Class;
		break;
	case 5: 
		cin.ignore(1);
		cout << "\nEnter class ID you want to view its students: ";
		getline(cin, classID, '\n');
		viewListStudents(classID);
		break;
	case 6:
		return;
	}
	classAndStudentMode();
}

//1. Import students from csv file.
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
	fin.ignore();
	while (!fin.eof()) {
		//Read each line in csv 
		
		getline(fin, ignore, ',');
		getline(fin, students[i].ID, ',');
		getline(fin, students[i].fullName, ',');
		getline(fin, students[i].gender, ',');
		getline(fin, students[i].DoB, ',');
		getline(fin, students[i].classID, ',');
		fin >> students[i].active;
		getline(fin, ignore, '\n');
		
		//getline(fin, ignore, '\n');
		fout << endl << students[i].ID << endl << students[i].fullName << endl << students[i].gender << endl << students[i].DoB << endl << students[i].classID<<endl<<students[i].active << endl;
		i++;
	}
	fin.close();
	fout.close();

	createUserPassword(students, nStudent);
}

void filterStudentToClass(string filename)
{
	Student* a;
	int nStudents;
	importStudentsFromCSV(a, nStudents);
	ifstream in(filename);
	
	if (!in.is_open())
	{
		cout << "Cant open " << filename << endl;
		return;
	}

	for (int i = 0; i < nStudents; i++)
	{
		string classFile = a[i].classID + "-Students.txt";
		ofstream fout(classFile, ofstream::app);
		if (!fout.is_open())
		{
			cout << "Cant create file" << endl;
			return;
		}
		fout << a[i].ID << endl << a[i].fullName << endl << a[i].DoB << endl << a[i].gender << endl << a[i].active << endl << endl;
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
		string password = formatPassword(students[i].DoB);
		fout << password << endl;
		fout << students[i].fullName << endl;
	}

	fout.close();
}

string formatPassword(string password) {
	string format = "";
	for (int i = 0; i < password.length(); i++) 
		if (password[i] != '-')
			format += password[i];
	return format;
}

//2. Add a student to a class.  //Check valid student before add
void addStudentToClass() {
	Student newStudent;

	cin.ignore(1);
	cout << "> Enter student infomation: \n";
	cout << " Full name: "; getline(cin, newStudent.fullName, '\n');
	cout << " ID: "; getline(cin, newStudent.ID, '\n');
	cout << " Gender: "; getline(cin, newStudent.gender, '\n');
	cout << " Date of birth: "; getline(cin, newStudent.DoB, '\n');
	cout << " Class ID: "; getline(cin, newStudent.classID, '\n');
	newStudent.active = 1;

	Student* students, * students1;
	int n = 0;

	ifstream fin;	
	ofstream fout;

	loadStudent(fin, "Students.txt", students, n);
	students1 = new Student[n + 1];
	for (int i = 0; i < n; i++) {
		students1[i] = students[i];
	}
	students1[n] = newStudent;

	writeStudent(fout, "Students.txt", students1, n + 1);

	createUserPassword(students1, n + 1);

	delete[] students;
	n = 0;

	string path = newStudent.classID;
	convertToUpper(path);
	path += "-Students.txt";
	
	fout.open(path, ios::app);

	fout << newStudent.ID << endl;
	fout << newStudent.fullName << endl;
	fout << newStudent.DoB << endl;
	fout << newStudent.gender << endl;
	fout << ((newStudent.active == true) ? 1 : 0) << endl << endl;

	fout.close();
}

void loadStudent(ifstream& fin, string filename, Student*& students, int& n) {
	if(isFileOpen(fin, filename) == false) 
		return;

	fin >> n;
	students = new Student[n];
	string ignore = "";
	getline(fin, ignore, '\n');

	for (int i = 0; i < n; i++) {
		getline(fin, ignore, '\n');
		getline(fin, students[i].ID,'\n');
		getline(fin, students[i].fullName,'\n');
		getline(fin, students[i].gender,'\n');
		getline(fin, students[i].DoB,'\n');
		getline(fin, students[i].classID,'\n');
		getline(fin, ignore, '\n');
		students[i].active = stoi(ignore);
	}

	fin.close();
}

void writeStudent(ofstream& fout, string filename, const Student* students, const int n) {
	fout.open(filename);
	if(!fout.is_open()) {
		cout << "Can not open " << filename << " .\n";
		return;
	}

	fout << n << endl;

	for (int i = 0; i < n; i++) {
		fout << endl;
		fout << students[i].ID << endl;
		fout << students[i].fullName << endl;
		fout << students[i].gender << endl;
		fout << students[i].DoB << endl;
		fout << students[i].classID << endl;
		fout << ((students[i].active == true) ? 1 : 0) << endl;
	}

	fout.close();
}
//3. Edit existing student.
///remember delete dynamic array when call these function
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
	cout << "===================================\n";
	cout << "List of Classes:\n";
	// int i = -1;
	// while (!data.eof())
	// {
	// 	++i;
	// 	getline(data, Class[i], '\n');
	// 	cout << i + 1 << ". " << Class[i] << endl;
	// }
	for (int i = 0; i < n; i++) {
		getline(data, Class[i], '\n');
		cout << i + 1 << ". " << Class[i] << endl;
	}
	data.close();
}

void getListStudents(string classID, Student*&Students, int &nStudents)
{
	ifstream data;
	string inputPath = "";
	string extension = "-Students.txt";
	convertToUpper(classID);
	inputPath = classID + extension;
	
	data.open(inputPath);

	if (!data.is_open()) {
		cout << "Can not open " << inputPath << endl;
		return;
	}

	string buff;
	nStudents = 0;
	while (!data.eof()) {
		getline(data, buff, '\n');
		if(buff == "")
			nStudents++;
	}
	data.close();

	data.open(inputPath);

	if (!data.is_open()) {
		cout << "Can not open " << inputPath << endl;
		return;
	}

	nStudents -= 1;
	Students = new Student[nStudents];

	cout << "List of students in class " << classID << " :\n";

	for (int i = 0; i < nStudents; i++) {
		getline(data, buff, '\n');
		Students[i].ID = buff;
		
		getline(data, buff, '\n');
		Students[i].fullName = buff;
		
		getline(data, buff, '\n');
		Students[i].DoB = buff;
		
		getline(data, buff, '\n');
		Students[i].gender = buff;
		
		getline(data, buff, '\n');
		Students[i].active = ((buff == "1") ? 1 : 0);

		getline(data, buff, '\n');

		if (Students[i].active == 1) {
			cout << "\nID: " << Students[i].ID << endl;
			cout << "Full name: " << Students[i].fullName << endl;
			cout << "Date of birth: " << Students[i].DoB << endl;
			cout << "Gender: " << Students[i].gender << endl;
		}
	}
	cout << "===================================\n";
	data.close();
}

void saveStudent(Student* Students, int nStudent, string fclass) {
	ofstream data;
	data.open(fclass);
	if (!data.is_open()) {
		cout << "Can't open file " << fclass;
	}
	else {
		for (int i = 0; i < nStudent; i++) {
			data << Students[i].ID << endl; 
			data << Students[i].fullName << endl;
			data << Students[i].DoB << endl;
			data << Students[i].gender << endl;
			data << Students[i].active << endl << endl;
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
		if (Students[i].ID == ID && Students[i].active == 1) {
			Students[i].active = false;
			flag = false;
			break;
		}
	}

	if (flag == true) {
		cout << "Don't have ID <" << ID << "> in this class.\n";
		cout << "===================================\n";
	}
	else {
		string inputPath = "";
		string extension = "-Students.txt";
		inputPath = Aclass + extension;
		saveStudent(Students, nStudents, inputPath);
		cout << "Delete successfully.\n";
		cout << "===================================\n";
	}
}

void Changeclass(string origin, string des) {
	Student* Students, * Students2;
	int nStudents, nStudents2;
	
	getListStudents(origin, Students, nStudents);
	
	string ID;
	cout << "Input ID of student you want to change class :"; cin >> ID;
	bool flag = true;
	for (int i = 0; i < nStudents; i++) {
		if (Students[i].ID == ID && Students[i].active == 1) {
			Students[i].active = false;
			flag = false;

			string Path = "";
			string extension = "-Students.txt";
			Path = des + extension;
			ofstream out;
			out.open(Path, ios::app);
			if (!out.is_open()) {
				cout << "Cant open file:" << Path << endl;
				return;
			}
			out << Students[i].ID << endl;
			out << Students[i].fullName << endl;
			out << Students[i].DoB << endl;
			out << Students[i].gender << endl;
			out << 1 << endl << endl;
			out.close();
			break;
		}
	}

	if (flag == true) {
		cout << "Don't have ID <" << ID << "> in this class.\n";
	}
	else
	{
		cout << "Change class successfully.\n";
		cout << "===================================\n";
		string inputPath = "";
		string extension = "-Students.txt";
		inputPath = origin + extension;
		saveStudent(Students, nStudents, inputPath);
		ifstream fin;
		Student* S;
		int n;
		loadStudent(fin, "Students.txt", S, n);
		for (int i = 0; i < n; i++) {
			if (S[i].ID == ID) {
				S[i].classID = des;
				//break;
			}
		}
		ofstream data;
		data.open("Students.txt");
		if (!data.is_open()) {
			cout << "Can't open file " << "Students.txt";
		}
		else {
			data << n << endl << endl;
			for (int i = 0; i < n; i++) {
				data << S[i].ID << endl;
				data << S[i].fullName << endl;
				data << S[i].DoB << endl;
				data << S[i].classID << endl;
				data << S[i].gender << endl;
				data << S[i].active << endl << endl;
			}
		}
		delete[] S;
		data.close();
	}
}

void Edit() {
	string* Class;
	int n;
	getListClass(n, Class);
	int buffer,buffer2,buffer3;
CLASS1:
	cout << "Choose your class you want to edit: ";
	cin >> buffer;
	buffer -= 1;
	if (buffer < 0 || buffer > n-1)
		goto CLASS1;
	cout << "===================================\n";
	cout << "1. Delete a student.\n";
	cout << "2. Change class a student.\n";
	cout << "3. Back to menu.\n";
OPTION:
	cout << "Choose mode: ";
	cin >> buffer2;
	cin.ignore(1);
	cout << "===================================\n";
	if (buffer2 > 3)
		goto OPTION;
	
	switch (buffer2) {
		case 1: 
			deleteStudent(Class[buffer]);
			break;
		case 2:
			for (int i=0;i<n;i++)
			 cout << i + 1 << ". " << Class[i] << endl;
		CLASS:
			cout << "Choose class destination: "; cin >> buffer3;
			buffer3 -= 1;
			if (buffer == buffer3 || buffer3<0 || buffer3 >n - 1)
				goto CLASS;
			cout << "===================================\n";
			Changeclass(Class[buffer],Class[buffer3]);
			break;
		case 3:
			break;
	}
	delete[] Class;
}

//4. View list of classes.
//5. View list of student in class.
void viewListStudents(string classID)
{
	ifstream data;
	string inputPath = "";
	string extension = "-Students.txt";
	
	convertToUpper(classID);
	inputPath = classID + extension;

	data.open(inputPath);

	if (!data.is_open()) {
		cout << "Can not open " << inputPath << endl;
		return;
	}

	string buff, buff1;
	Student student;
	int nStudent = 0;
	cout << "**List of students in class " << classID << ":\n";

	while (!data.eof()) {
		getline(data, buff, '\n');
		if(buff == "" && buff1 == "")
			break;
		student.ID = buff;
		
		getline(data, buff, '\n');
		student.fullName = buff;
		
		getline(data, buff, '\n');
		student.DoB = buff;
		
		getline(data, buff, '\n');
		student.gender = buff;
		
		getline(data, buff, '\n');
		student.active = ((buff == "1") ? 1 : 0);
		getline(data, buff1, '\n');
		
		if (student.active == 1) {
			cout << "\nID: " << student.ID << endl;
			cout << "Full name: " << student.fullName << endl;
			cout << "Day of birth: " << student.DoB << endl;
			cout << "Gender: " << student.gender << endl;
			nStudent++;
		}
	}
	data.close();

	cout << "\nTotal students: " << nStudent << endl;
	cout << "===================================\n";
}

void convertToUpper(string& s)
{
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		s[i] = (char)toupper(s[i]);
	}
}

//6. Back to staff menu.
//Call classAndStudentMode();

//**2. Courses.
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
		importCoursesFromCsvFile(courses, nCourse);
		cout << "Import successfully.\n";
		cout << "===================================\n";
		break;
	case 3:
		addNewCourse();
		cout << "===================================\n";
		break;
	case 4:
		editCourse();
		cout << "===================================\n";
		break;
	case 5: 
		removeCourse();
		cout << "===================================\n";
		break;
	case 6:
		removeSpecificStudent();
		cout << "===================================\n";
		break;
	case 7:	
		addStudentToCourse();
		cout << "===================================\n";
		break;
	case 8: 
		//View list of courses in the current semester.
		break;
	case 9:
		viewListStudentsOfCourse();
		cout << "===================================\n";
		break;
	case 10:
		viewAttendanceList();
		cout << "===================================\n";
		break;
	case 11:
		editLecturers();
		cout << "===================================\n";
		break;
	case 12:
		return;
	}
	courseMode();
}

//1. Edit academic years and semesters.
void createCourse(Course& course,string classID) {
	cout << "Input course ID: ";
	cin >> course.ID;

	// cout << "Input course name: ";
	// cin >> course.name;

	// course.classID=classID;

	// cout << "Input lecturer's account: ";
	// cin >> course.lecAccount;

	// cout << "Input course's start day: ";
	// course.startDate.inputDay();

	// cout << "Input course's end day: ";
	// course.endDate.inputDay();

	// cout << "Input course's time: ";
	// course.courseTime.inputTime();

	// cout << "Input course room: ";
	// cin >> course.room;
}

void createSemester(Semester& temp,string classID,string startYear, string endYear,string HK)
{
	cout << "Input the number of courses: ";
	cin >> temp.numberOfCourses;
	temp.coursesArray = new Course[temp.numberOfCourses];
	for (int i = 0; i < temp.numberOfCourses; i++)
	{
		createCourse(temp.coursesArray[i],classID);
	}
	string filename=classID+"-"+startYear+"-"+endYear+"-"+HK+".txt";
	ofstream fout(filename);
	if(!fout.is_open())
	{
		cout<<"Cant create "<<filename<<endl;
		return;
	}

	//fout<<temp.numberOfCourses<<endl<<endl;

	for(int j=0;j<temp.numberOfCourses;j++)
	{
		fout<<temp.coursesArray[j].ID<<endl;
		fout<<temp.coursesArray[j].name<<endl;
		fout<<temp.coursesArray[j].classID<<endl;
		fout<<temp.coursesArray[j].lecAccount<<endl;
		fout<<temp.coursesArray[j].startDate.year<<"-"<< temp.coursesArray[j].startDate.month<<"-"<< temp.coursesArray[j].startDate.day<<endl;
		fout<<temp.coursesArray[j].endDate.year<<"-"<< temp.coursesArray[j].endDate.month<<"-"<< temp.coursesArray[j].endDate.day<<endl;
		fout<<temp.coursesArray[j].courseTime.dayOfWeek<<"\n"<< temp.coursesArray[j].courseTime.startHour<<":"<< temp.coursesArray[j].courseTime.startMin<<endl<< temp.coursesArray[j].courseTime.endMin<<":"<< temp.coursesArray[j].courseTime.endHour<<endl;
		fout<<temp.coursesArray[j].room<<endl;
		fout<<endl;
	}
	fout.close();
}

void createSimpleSemester(Semester& temp,string classID,string startYear, string endYear,string HK)
{
	cout << "Input the number of courses: ";
	cin >> temp.numberOfCourses;
	temp.coursesArray = new Course[temp.numberOfCourses];
	for (int i = 0; i < temp.numberOfCourses; i++)
	{
		createCourse(temp.coursesArray[i],classID);
	}
	string filename=classID+"-"+startYear+"-"+endYear+"-"+HK+".txt";
	ofstream fout(filename);
	if(!fout.is_open())
	{
		cout<<"Cant create "<<filename<<endl;
		return;
	}

	//fout<<temp.numberOfCourses<<endl<<endl;

	for(int j=0;j<temp.numberOfCourses;j++)
	{
		fout<<temp.coursesArray[j].ID<<endl;
	}
	fout.close();
}

//void createSemesterAlone()
//{
//	Semester temp;
//	string classID,hk;
//	string number;
//
//	cout<<"Input class ID: ";
//	cin>>classID;
//
//	int intStartYear,intEndYear;
//	cout<<"Input start year: ";
//	cin>>intStartYear;
//	string startYear,endYear;
//	stringstream sstr;
//	sstr << intStartYear;
//	startYear = sstr.str();
//	sstr.str("");
//	sstr << intStartYear+1;
//	endYear = sstr.str();
//
//	cout<<"Input semester(1 to 3): ";
//	cin>>number;
//	hk = "HK" + number;
//	string filename=classID+"-"+startYear+"-"+endYear+"-"+hk+".txt";
//
//	ofstream fout(filename);
//	if(!fout.is_open())
//	{
//		cout<<"Cant create "<<filename<<endl;
//		return;
//	}
//
//	fout<<temp.numberOfCourses<<endl<<endl;
//
//	for(int j=0;j<temp.numberOfCourses;j++)
//	{
//		fout<<temp.coursesArray[j].ID<<endl;
//		fout<<temp.coursesArray[j].name<<endl;
//		fout<<temp.coursesArray[j].classID<<endl;
//		fout<<temp.coursesArray[j].lecAccount<<endl;
//		fout<<temp.coursesArray[j].startDate.year<<"-"<< temp.coursesArray[j].startDate.month<<"-"<< temp.coursesArray[j].startDate.day<<endl;
//		fout<<temp.coursesArray[j].endDate.year<<"-"<< temp.coursesArray[j].endDate.month<<"-"<< temp.coursesArray[j].endDate.day<<endl;
//		fout<<temp.coursesArray[j].courseTime.dayOfWeek<<"\n"<< temp.coursesArray[j].courseTime.startHour<<":"<< temp.coursesArray[j].courseTime.startMin<<endl<< temp.coursesArray[j].courseTime.endMin<<":"<< temp.coursesArray[j].courseTime.endHour<<endl;
//		fout<<temp.coursesArray[j].room<<endl;
//		fout<<endl;
//	}
//	fout.close();
//}

void addCourseToSemester()
{
	{
	string classID,hk;
	string temp;

	cout<<"Input class ID: ";
	cin>>classID;

	int intStartYear,intEndYear;
	cout<<"Input start year: ";
	cin>>intStartYear;
	string startYear,endYear;
	stringstream sstr;
	sstr << intStartYear;
	startYear = sstr.str();
	sstr.str("");
	sstr << intStartYear+1;
	endYear = sstr.str();

	cout<<"Input semester(1 to 3): ";
	cin>>temp;
	hk = "HK" + temp;
	string filename=classID+"-"+startYear+"-"+endYear+"-"+hk+".txt";

	ofstream out(filename,ios::app);
	if (!out.is_open())
	{
		cout<<"Cant open "<<filename<<endl;
		return;
	}

	string courseID;
	cout<<"Input course ID: ";
	cin>>courseID;
	out<<courseID;

	return;
	}
}

void viewCourseSemester() {
	{
		string classID, hk;
		string temp;

		cout << "Input class ID: ";
		cin >> classID;

		int intStartYear, intEndYear;
		cout << "Input start year: ";
		cin >> intStartYear;
		string startYear, endYear;
		stringstream sstr;
		sstr << intStartYear;
		startYear = sstr.str();
		sstr.str("");
		sstr << intStartYear + 1;
		endYear = sstr.str();

		cout << "Input semester(1 to 3): ";
		cin >> temp;
		hk = "HK" + temp;
		string filename = classID + "-" + startYear + "-" + endYear + "-" + hk + ".txt";

		ifstream in(filename);
		if (!in.is_open())
		{
			cout << "Cant open " << filename << endl;
			return;
		}
		string buf;
		while (!in.eof())
		{
			getline(in, buf, '\n');
			cout << buf << endl;
		}

		return;
	}
}
void createAcademicYear()
{
	academicYear year;
	string classID;
	cout<<"Input class ID: ";
	cin>>classID;
	cout << "Input starting year: ";
	cin >> year.startYear;

	string startYear,endYear;
	stringstream sstr;
	sstr << year.startYear;
	startYear = sstr.str();
	sstr.str("");
	
	sstr << year.startYear+1;
	endYear = sstr.str();

	string filename=classID+"-"+startYear+"-"+endYear+".txt";
	ofstream fout(filename);

	string hk;
	for (int i = 0; i < 3; i++)
	{
		cout <<endl<< "INPUT SEMESTER " << i+1 << " " << endl;
		hk = "HK"+to_string(i+1);
		createSimpleSemester(year.semesterArray[i],classID,startYear,endYear,hk);
		hk="";
	}

	for (int i = 0; i < 3; i++)
	{
		hk = "HK"+to_string(i+1);
		fout<<classID+"-"+startYear+"-"+endYear+"-"+hk+".txt"<<endl;
	}
}

void deleteCourses()
{
	string classID,hk;
	string temp;

	cout<<"Input class ID: ";
	cin>>classID;

	int intStartYear,intEndYear;
	cout<<"Input start year: ";
	cin>>intStartYear;
	string startYear,endYear;
	stringstream sstr;
	sstr << intStartYear;
	startYear = sstr.str();
	sstr.str("");
	sstr << intStartYear+1;
	endYear = sstr.str();

	cout<<"Input semester(1 to 3): ";
	cin>>temp;
	hk = "HK" + temp;
	string filename=classID+"-"+startYear+"-"+endYear+"-"+hk+".txt";

	ofstream out(filename);
	if (!out.is_open())
	{
		cout<<"Cant open "<<filename<<endl;
		return;
	}

	string courseID;
	cout<<"Input course ID: ";
	cin>>courseID;

	return;
}

void deleteSemester()
{
	string classID, hk;
	string temp;

	cout << "Input class ID: ";
	cin >> classID;

	int intStartYear, intEndYear;
	cout << "Input start year: ";
	cin >> intStartYear;
	string startYear, endYear;
	stringstream sstr;
	sstr << intStartYear;
	startYear = sstr.str();
	sstr.str("");
	sstr << intStartYear + 1;
	endYear = sstr.str();

	cout << "Input semester(1 to 3): ";
	cin >> temp;
	hk = "HK" + temp;
	string filename = classID + "-" + startYear + "-" + endYear + "-" + hk + ".txt";

	if (remove(filename.c_str()) == 0)
		cout << "Deteled " << filename;
	else
		cout << "Cant delete " << filename;

	return;
}

void viewYear() {
	academicYear year;
	string classID;
	cout << "Input classID: ";
	cin >> classID;
	cout << "Input starting year: ";
	cin >> year.startYear;

	string startYear, endYear;
	stringstream sstr;
	sstr << year.startYear;
	startYear = sstr.str();
	sstr.str("");

	sstr << year.startYear + 1;
	endYear = sstr.str();
	string filename = classID + "-" + startYear + "-" + endYear + ".txt";

	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Cant open " << filename << endl;
		return;
	}

	string temp = "";

	while (!fin.eof())
	{
		temp = "";
		getline(fin, temp, '\n');
		cout <<temp<<endl;
	}
	return;
}

void deleteYear()
{
	academicYear year;
	string classID;
	cout<<"Input classID: ";
	cin>>classID;
	cout << "Input starting year: ";
	cin >> year.startYear;

	string startYear,endYear;
	stringstream sstr;
	sstr << year.startYear;
	startYear = sstr.str();
	sstr.str("");
	
	sstr << year.startYear+1;
	endYear = sstr.str();
	string filename=classID+"-"+startYear+"-"+endYear+".txt";

	if(remove(filename.c_str())==0)
		cout<<"Deleted "<<filename<<endl;
	else
		cout<<"Cant delete "<<filename<<endl;

	string hk="";
	for (int i = 0; i < 3; i++)
	{
		hk = "HK"+to_string(i+1);
		filename=startYear+"-"+endYear+"-"+hk+".txt";
		if(remove(filename.c_str())==0)
			cout<<"Deleted "<<filename<<endl;
		else
			cout<<"Cant delete "<<filename<<endl;
	}

	return;
}

void updateAcademicYear()
{
	academicYear year;
	cout << "Input starting year: ";
	cin >> year.startYear;

	string startYear, endYear;
	stringstream sstr;
	sstr << year.startYear;
	startYear = sstr.str();
	sstr.str("");

	sstr << year.startYear + 1;
	endYear = sstr.str();
	string filename = startYear + "-" + endYear + ".txt";
}

void menuAcademicYear()
{
	int option,option2;
	cout << "1. Academic year." << endl;
	cout << "2. Semester." << endl;

	cout<<"SELECT YOUR OPTION: "<<endl;
	cin>>option;
	if(option==1)
	{
		cout<<"ACADEMIC MENU: "<<endl;
		cout<<"1. Add an academic year."<<endl;
		cout<<"2. Edit an academic year."<<endl;
		cout<<"3. View an academic year."<<endl;
		cout<<"4. Delete an academic year."<<endl;
		cout << "0. Back." << endl;

		cin>>option;
		if(option==1)	createAcademicYear();
		else if(option==2)
		{
			cout<<"Coming soon."<<endl;
			return;
		}
		else if(option==3)
		{
			viewYear();
			return;
		}
		else if(option==4)	deleteYear();
		else if (option == 0) {
			menuAcademicYear();
		}
		else{
			cout<<"There is no option matched your option."<<endl;
			return;
		}
		return;
	}
	else if(option==2)
	{
		cout<<"SEMESTER MENU: "<<endl;
		cout<<"1. Add a course."<<endl;
		cout<<"2. Edit a course."<<endl;
		cout<<"3. View semester."<<endl;
		cout<<"4. Delete semester."<<endl;
		cout<<"0. Back." << endl;
	
		cin>>option;
		if (option == 1)	
		{
			addCourseToSemester();
		}
		else if(option==2){
			cout<<"Coming soon."<<endl;
			return;
		}
		else if(option==3){
			viewCourseSemester();
			return;
		}
		else if(option==4)	deleteSemester();
		else if (option ==0 ) {
			menuAcademicYear();
		}
		else{
			cout<<"There is no option matched your option."<<endl;
			return;
		}
		return;
	}

}
//2. Import courses from csv file to txt file.(14)
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
	nCourse -= 1;
	fin.close();

	if (isFileOpen(fin, "Courses.csv") == false)
		return;
	
	courses = new Course[nCourse];
	fout << nCourse << endl;

	ignore = "";

	int i = 0;
	for (int i = 0; i < nCourse; i++)
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
		//fout << courses[i].active << endl;
	}

	fin.close();
	fout.close();

	createClassCourse(courses, nCourse);
	addStudentIntoCourse(nCourse);
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
void splitClassID(string& str) {
	string classId = "";
	for(int i = 0; str[i] != '-'; i++) {
		classId += str[i];
	}
	str = classId;
}

void addStudentIntoCourse(const int n) {
	string fileCourse = "";
	string source = "";

	ifstream finCourse;
	if(isFileOpen(finCourse, "ListCourses.txt") == false) 
		return;

	for (int i = 0; i < n; i++) {
		getline(finCourse, fileCourse, '\n');
		source = fileCourse;
		splitClassID(source);
		source += "-Students.txt";

		copyFile(source, fileCourse);
	}
	finCourse.close();
}

//3. Manually add a new course.(15)
void addNewCourse()
{
	Course c;
	cout << "Enter course ID: ";
	cin.ignore(1);
	getline(cin, c.ID);
	convertToUpper(c.ID);
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
	convertToUpper(c.courseTime.dayOfWeek);
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

	Course* courses;
	int nCourses;

	loadCoursesFromTXT("Courses.txt", courses, nCourses);

	int temp = nCourses + 1;

	ofstream fout;

	fout.open("Courses.txt");

	if (!fout.is_open())
	{
		cout << "Cannot open file Courses.txt\n";
		return;
	}

	fout << temp << endl;

	for (int i = 0; i < temp; i++) {
		if (i != temp - 1)
		{
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
		}
		else
		{
			fout << endl << c.ID << endl;
			fout << c.name << endl;
			fout << c.classID << endl;
			fout << c.lecAccount << endl;
			fout << c.startDate.year << '-' << c.startDate.month << '-' << c.startDate.day << endl;
			fout << c.endDate.year << '-' << c.endDate.month << '-' << c.endDate.day << endl;
			fout << c.courseTime.dayOfWeek << endl;
			fout << c.courseTime.startHour << ':' << c.courseTime.startMin << endl;
			fout << c.courseTime.endHour << ':' << c.courseTime.endMin << endl;
			fout << c.room << endl;
		}
	}
	delete[] courses;
	fout.close();

	fstream f;
	f.open("ListCourses.txt", ios::out | ios::app);

	string filecourses = c.classID + "-" + c.ID + ".txt";

	f << filecourses << endl;
	f.close();
	string source = c.classID + "-Students.txt";

	fstream f1;
	f1.open(source, ios::in);

	if (!f1.is_open())
	{
		f1.close();
		f1.open(source, ios::out);
		f1.close();
	}
	else
		f1.close();

	copyFile(source, filecourses);
	cout << "\nAdd new courses successfully.\n";
}

//4. Edit an existing course.
void editCourse()
{
	cin.ignore(1);
	string buffer = "";
	string courseID = "";
	string classID = "";
	cout << "Enter course ID: ";
	getline(cin, courseID);
	convertToUpper(courseID);

	cout << "Enter class ID: ";
	getline(cin, classID);
	convertToUpper(classID);

	Course* courses;
	int nCourses;

	loadCoursesFromTXT("Courses.txt", courses, nCourses);

	int index = -1;
	for (int i = 0; i < nCourses; i++)
	{
		if ((courses[i].ID == courseID) && (courses[i].classID == classID))
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		cout << "Cannot find course with ID [" << courseID << "][" << classID << "].\n";
		return;
	}

	cout << "\n==========Information==========\n";
	cout << "Course ID         : " << courses[index].ID << endl;
	cout << "Course Name       : " << courses[index].name << endl;
	cout << "Class ID          : " << courses[index].classID << endl;
	cout << "Lecturer Username : " << courses[index].lecAccount << endl;
	cout << "Start Date        : " << courses[index].startDate.year << "-" << courses[index].startDate.month << "-" << courses[index].startDate.day << endl;
	cout << "End Date          : " << courses[index].endDate.year << "-" << courses[index].endDate.month << "-" << courses[index].endDate.day << endl;
	cout << "Day Of Week       : " << courses[index].courseTime.dayOfWeek << endl;
	cout << "Start Hour        : " << courses[index].courseTime.startHour << ":" << courses[index].courseTime.startMin << endl;
	cout << "End Hour          : " << courses[index].courseTime.endHour << ":" << courses[index].courseTime.endMin << endl;
	cout << "Room              : " << courses[index].room << endl;

	int mode = -1;
	bool flag = false;

	while (mode != 10)
	{
		if (flag == true)
		{
			cout << "\n==========Information==========\n";
			cout << "Course ID         : " << courses[index].ID << endl;
			cout << "Course Name       : " << courses[index].name << endl;
			cout << "Class ID          : " << courses[index].classID << endl;
			cout << "Lecturer Username : " << courses[index].lecAccount << endl;
			cout << "Start Date        : " << courses[index].startDate.year << "-" << courses[index].startDate.month << "-" << courses[index].startDate.day << endl;
			cout << "End Date          : " << courses[index].endDate.year << "-" << courses[index].endDate.month << "-" << courses[index].endDate.day << endl;
			cout << "Day Of Week       : " << courses[index].courseTime.dayOfWeek << endl;
			cout << "Start Hour        : " << courses[index].courseTime.startHour << ":" << courses[index].courseTime.startMin << endl;
			cout << "End Hour          : " << courses[index].courseTime.endHour << ":" << courses[index].courseTime.endMin << endl;
			cout << "Room              : " << courses[index].room << endl;
		}
		flag = true;
		cout << "\n==========Features==========\n";
		cout << "1. Change course ID.\n";
		cout << "2. Change course name.\n";
		cout << "3. Change lecturer (username).\n";
		cout << "4. Change start date.\n";
		cout << "5. Change end date.\n";
		cout << "6. Change day of week.\n";
		cout << "7. Change start time.\n";
		cout << "8. Change end time.\n";
		cout << "9. Change room.\n";
		cout << "10. Exit and save.\n";
		cout << "Enter mode: ";
		cin >> mode;
		cout << endl;

		cin.ignore(1);

		if (mode == 1)
		{
			cout << "Enter new course ID: ";
			getline(cin, buffer);
			convertToUpper(buffer);
			courses[index].ID = buffer;
		}
		if (mode == 2)
		{
			cout << "Enter new course name: ";
			getline(cin, buffer);
			courses[index].name = buffer;
		}
		if (mode == 3)
		{
			cout << "Enter new lecturer (username): ";
			getline(cin, buffer);
			courses[index].lecAccount = buffer;
		}
		if (mode == 4)
		{
			cout << "Enter new start date: \n";
			cout << "Day: ";
			cin >> buffer;
			courses[index].startDate.day = stoi(buffer);
			cout << "Month: ";
			cin >> buffer;
			courses[index].startDate.month = stoi(buffer);
			cout << "Year: ";
			cin >> buffer;
			courses[index].startDate.year = stoi(buffer);
		}
		if (mode == 5)
		{
			cout << "Enter new end date: \n";
			cout << "Day: ";
			cin >> buffer;
			courses[index].endDate.day = stoi(buffer);
			cout << "Month: ";
			cin >> buffer;
			courses[index].endDate.month = stoi(buffer);
			cout << "Year: ";
			cin >> buffer;
			courses[index].endDate.year = stoi(buffer);
		}
		if (mode == 6)
		{
			cout << "Enter new day of week: ";
			getline(cin, buffer);
			convertToUpper(buffer);
			courses[index].courseTime.dayOfWeek = buffer;
		}
		if (mode == 7)
		{
			cout << "Enter new start time: \n";
			cout << "Start hour: ";
			getline(cin, buffer);
			courses[index].courseTime.startHour = buffer;
			cout << "Start min: ";
			getline(cin, buffer);
			courses[index].courseTime.startMin = buffer;
		}
		if (mode == 8)
		{
			cout << "Enter new end time: \n";
			cout << "End hour: ";
			getline(cin, buffer);
			courses[index].courseTime.endHour = buffer;
			cout << "End min: ";
			getline(cin, buffer);
			courses[index].courseTime.endMin = buffer;
		}
		if (mode == 9)
		{
			cout << "Enter new room: ";
			getline(cin, buffer);
			convertToUpper(buffer);
			courses[index].room = buffer;
		}
		if ((mode < 1) || (mode > 10))
			cout << "Invalid Mode.\n";
		else
			if (mode != 10)
				cout << "Done.\n";
	}

	ofstream fout;

	fout.open("Courses.txt");

	if (!fout.is_open())
	{
		cout << "Cannot open file Courses.txt\n";
		return;
	}

	fout << nCourses << endl;

	for (int i = 0; i < nCourses; i++) {
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
	}

	fout.close();
	delete[] courses;

	cout << "\nSaved successfully.\n";
}
//5. Remove a course.
void loadCoursesFromTXT(string filename, Course*& courses, int& n) {
	fstream f;

	f.open(filename, ios::in);

	if (!f.is_open())
		return;

	f >> n;

	courses = new Course[n];

	string ignore = "";

	f.ignore(1);
	getline(f, ignore, '\n');

	for (int i = 0; i < n; i++)
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
	}

	f.close();
}

void removeCourse() {
	Course course;

	cout << "> Enter course ID: "; 
	cin >> course.ID;
	convertToUpper(course.ID);
	cout << "> Enter course class ID: ";
	cin >> course.classID;
	convertToUpper(course.classID);

	Course* courses;
	int n = 0;

	loadCoursesFromTXT("Courses.txt", courses, n);

	for(int i = 0; i < n; i++) {
	 	if(courses[i].ID == course.ID && courses[i].classID == course.classID) {
			courses[i].active == 0;
	 		break;
	 	}
	}

	ofstream fout;
	fout.open("Courses.txt", ios::out);
	if(!fout.is_open()) {
		cout << "Can not open Courses.txt.\n";
		return;
	}

	int temp = n - 1;

	fout << temp << endl;

	for(int i = 0; i < n; i++) {
		if (courses[i].ID == course.ID && courses[i].classID == course.classID)
			continue;
		else {
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
		}
	}
	cout << "Remove " << course.ID << " in " << course.classID << " successfully.\n";
	fout.close();
}

//6. Remove Specific Student From A Course.
void removeSpecificStudent()
{
	bool flag = false;
	string filename = "";
	string classID = "";
	string course = "";
	string ID = "";

	cin.ignore(1);
	cout << "Enter class: ";
	getline(cin, classID);

	cout << "Enter course: ";
	getline(cin, course);

	convertToUpper(classID);
	convertToUpper(course);

	cout << "Enter student ID to remove from course " << course << ": ";
	getline(cin, ID);

	filename = classID + "-" + course + ".txt";

	fstream fin;

	fin.open(filename, ios::in);

	if (!fin.is_open())
	{
		cout << "Can't find course. Please check your input information.\n";
		return;
	}

	string ignore = "";
	int nStudents = 0;

	while (!fin.eof())
	{
		getline(fin, ignore, '\n');
		getline(fin, ignore, '\n');
		getline(fin, ignore, '\n');
		getline(fin, ignore, '\n');
		getline(fin, ignore, '\n');
		getline(fin, ignore, '\n');
		nStudents++;
	}

	fin.close();

	fin.open(filename, ios::in);

	if (!fin.is_open())
	{
		cout << "Can't open file.\n";
		return;
	}

	Student* s = new Student[nStudents];

	for (int i = 0; i < nStudents; i++)
	{
		getline(fin, s[i].ID, '\n');
		getline(fin, s[i].fullName, '\n');
		getline(fin, s[i].DoB, '\n');
		getline(fin, s[i].gender, '\n');
		string active = "";
		getline(fin, active, '\n');
		if (active == "0")
			s[i].active = 0;
		else 
			s[i].active = 1;
		s[i].classID = classID;
		getline(fin, ignore, '\n');
	}

	fin.close();

	for (int i = 0; i < nStudents; i++)
	{
		if (s[i].ID == ID)
		{
			s[i].active = 0;
			flag = true;
		}
	}

	fin.open(filename, ios::out);

	if (!fin.is_open())
	{
		cout << "Can't open file.\n";
		return;
	}

	for (int i = 0; i < nStudents; i++)
	{
		fin << s[i].ID << endl;
		fin << s[i].fullName << endl;
		fin << s[i].DoB << endl;
		fin << s[i].gender << endl;
		if (s[i].active == 1)
			fin << "1";
		else 
			fin << "0";
		if (i != nStudents - 1)
			fin << endl << endl;
	}

	fin.close();

	delete[] s;

	if (flag == true)
		cout << "Remove student with ID [" << ID << "][" << classID << "] successfully.\n";
	else 
		cout << "Cannot find student with [" << ID << "][" << classID << "] in course.\n";

	return;
}

//7. Add a specific student to a course.
void writeFileStudentTXT(Student& newStudent) 
{

	// cin.ignore(1);
	// cout << "> Enter student infomation: \n";
	// cout << " Full name: "; getline(cin, newStudent.fullName, '\n');
	// cout << " ID: "; getline(cin, newStudent.ID, '\n');
	// cout << " Gender: "; getline(cin, newStudent.gender, '\n');
	// cout << " Date of birth: "; getline(cin, newStudent.DoB, '\n');
	// cout << " Class ID: "; getline(cin, newStudent.classID, '\n');
	// newStudent.active = 1;

	Student* students, * students1;
	int n = 0;

	ifstream fin;	
	ofstream fout;

	loadStudent(fin, "Students.txt", students, n);
	for(int i=0;i<n;i++)
	{
		if(students[i].ID.compare(newStudent.ID)==0)
		{
			return;
		}
	}
	students1 = new Student[n + 1];
	for (int i = 0; i < n; i++) {
		students1[i] = students[i];
	}
	students1[n] = newStudent;

	writeStudent(fout, "Students.txt", students1, n + 1);
}
void writeStudentCaro(string filename,Student* newStudent )
{
	ifstream fin(filename);
	if(!fin.is_open())
	{
		cout<<"Cant open "<<filename<<endl;
		return;
	}

	string ignore="";
	int nStudents=0;
	while(!fin.eof())
	{
		getline(fin,ignore,'\n');
		getline(fin,ignore,'\n');
		getline(fin,ignore,'\n');
		getline(fin,ignore,'\n');
		getline(fin,ignore,'\n');
		nStudents++;
		getline(fin,ignore,'\n');
	}
	nStudents++;
	Student* aStudents=new Student[nStudents];
	aStudents[nStudents - 1] = *newStudent;
	fin.close();
	fin.open(filename);
	int a;
	for(int i=0;i<nStudents;i++)
	{
		getline(fin, aStudents[i].ID,'\n');
		getline(fin, aStudents[i].fullName,'\n');
		getline(fin, aStudents[i].DoB, '\n');
		getline(fin, aStudents[i].gender,'\n');
		fin >> a;
		aStudents[i].active = (bool)a;
		fin.ignore();
		fin.ignore();
	}
	fin.close();
	ofstream fout(filename);
	for (int i = 0; i < nStudents; i++)
	{
		fout << aStudents[i].ID<<'\n';
		fout << aStudents[i].fullName << '\n';
		fout << aStudents[i].DoB << '\n';
		fout << aStudents[i].gender << '\n';
		fout << aStudents[i].active << '\n';
		fout << endl;
	}
	fout.close();
}

bool checkAppeared(string filename,Student* newStudent )
{
	ifstream fin(filename);
	if(!fin.is_open())
	{
		cout<<"Cant open "<<filename<<endl;
		return 0;
	}

	string ignore="";
	int nStudents=0;
	while(!fin.eof())  //count
	{
		getline(fin,ignore,'\n');
		getline(fin,ignore,'\n');
		getline(fin,ignore,'\n');
		getline(fin,ignore,'\n');
		getline(fin,ignore,'\n');
		nStudents++;
		getline(fin,ignore,'\n');
	}
	nStudents++;
	Student* aStudents=new Student[nStudents];
	aStudents[nStudents - 1] = *newStudent;
	fin.close();
	fin.open(filename);
	int a;
	for(int i=0;i<nStudents;i++)
	{
		getline(fin, aStudents[i].ID,'\n');
		getline(fin, aStudents[i].fullName,'\n');
		getline(fin, aStudents[i].DoB, '\n');
		getline(fin, aStudents[i].gender,'\n');
		fin >> a;
		aStudents[i].active = (bool)a;
		fin.ignore();
		fin.ignore();
	}
	fin.close();

	for (int i = 0; i < nStudents; i++)
	{
		if (aStudents[i].ID.compare(newStudent->fullName) == 0)
		{
			return 1;
		}
	}
	return 0;
}

void addStudentToCourse()
{
	string courseID;
	string classID;

	cout << "Input Class ID: ";
	cin >> classID;
	convertToUpper(classID);
	cout << "Input Course ID: ";
	cin >> courseID;
	convertToUpper(courseID);

	Course* aCourses;
	int nCourses;

	loadCoursesFromTXT("Courses.txt", aCourses, nCourses);

	Course course;  //course to find
	course.ID = "";
	for (int i = 0; i < nCourses; i++)
	{
		if (aCourses[i].ID.compare(courseID) == 0 || aCourses[i].classID.compare(classID) == 0)
		{
			course = aCourses[i];
			break;
		}
	}
	if (course.ID.compare("") == 0)
	{
		cout << "Cant find the inputted course" << endl;
		return;
	}

	Student newStudent;

	cout << "> Enter student information: \n";
	cout << " Full name: "; getline(cin, newStudent.fullName);
	getline(cin, newStudent.fullName);
	cout << " ID: "; getline(cin, newStudent.ID);
	cout << " Gender: "; getline(cin, newStudent.gender);
	cout << " Date of birth: "; getline(cin, newStudent.DoB);
	cout << " Class ID: "; getline(cin, newStudent.classID);
	cout << " Active status(0:No, 1:Yes) : "; cin >> newStudent.active;
 
	string filename = "";
	//Students.txt
	if (checkAppeared("Students.txt", &newStudent) == 0)
	{
		writeFileStudentTXT(newStudent);
	}
	//Class-Students.txt
	if(newStudent.classID.compare(classID)!=0)
	{
		cout<<"YOU DONT HAVE PERMISSION TO JOIN ANOTHER CLASS."<<endl;
	}
	else
	{
		filename = newStudent.classID + "-Students.txt";
		if (checkAppeared(filename, &newStudent) == 0)
		{
			writeStudentCaro(filename, &newStudent);
		}
	}


	//Class-Course.txt
	filename = classID + "-" + courseID + ".txt";
	if (checkAppeared(filename, &newStudent) == 0)
	{
		writeStudentCaro(filename, &newStudent);
	}

	filename = classID + "-" + courseID + "-AttendanceList.txt";
	if (checkAppeared(filename, &newStudent) == 0)
	{
		writeStudentCaro(filename, &newStudent);
	}
	/*{


	Student* aStudents, * temp;
	int nStudents;

	loadDataCourse(filename, temp, nStudents);

	aStudents = new Student[nStudents + 1];
	for (int i = 0; i < nStudents; i++)
	{
		aStudents[i] = temp[i];
	}
	aStudents[nStudents - 1] = newStudent;

	ofstream out(filename);
	if (!out.is_open())
	{
		cout << "Cant open course file";
		return;
	}

	for (int i = 0; i < nStudents; i++)
	{
		out << aStudents[i].ID << endl;
		out << aStudents[i].fullName << endl;
		out << aStudents[i].DoB << endl;
		out << aStudents[i].gender << endl;
		out << aStudents[i].active << endl;
		out << endl;
	}
	}*/
}

//9. View list of students of a course.
void viewListStudentsOfCourse()
{
	ifstream data;
	string classID, course;
	cout << "Input course:"; cin >> classID;
	cout << "Input class:"; cin >> course;
	string inputPath = "";

	convertToUpper(classID);
	convertToUpper(course);
	inputPath = course + "-" + classID + ".txt";

	data.open(inputPath);

	if (!data.is_open()) {
		cout << "Can not open " << inputPath << endl;
		return;
	}

	string buff;
	int nStudents = 0;
	while (!data.eof()) {
		getline(data, buff, '\n');
		if (buff == "")
			nStudents++;
	}
	data.close();

	data.open(inputPath);
	if (!data.is_open()) {
		cout << "Can not open " << inputPath << endl;
		return;
	}

	nStudents -= 1;
	Student* students = new Student[nStudents];

	cout << "List of students in course " << classID << ":\n\n";

	for (int i = 0; i < nStudents; i++) {
		getline(data, buff, '\n');
		students[i].ID = buff;

		getline(data, buff, '\n');
		students[i].fullName = buff;

		getline(data, buff, '\n');
		students[i].DoB = buff;

		getline(data, buff, '\n');
		students[i].gender = buff;

		getline(data, buff, '\n');
		students[i].active = ((buff == "1") ? 1 : 0);

		getline(data, buff, '\n');

		if (students[i].active == 1) {
			cout << "\nID: " << students[i].ID << endl;
			cout << "Full name: " << students[i].fullName << endl;
			cout << "Day of birth: " << students[i].DoB << endl;
			cout << "Gender: " << students[i].gender << endl;
		}
	}
	data.close();
}

//10. View attendance list of a course.
void loadDataCourse(string filename, Student*& aStudents, int& n)
{
	ifstream in;
	if (isFileOpen(in, filename) == false)
		return;

	n = 0;
	string ignore;
	while (!in.eof()) {
		getline(in, ignore, '\n');
		if(ignore == "")
			n++;
	}
	n -= 1;
	in.close();

	if (isFileOpen(in, filename) == false)
		return;

	aStudents = new Student[n];

	for (int i = 0; i < n; i++) {
		getline(in, aStudents[i].ID, '\n');
		getline(in, aStudents[i].fullName, '\n');
		getline(in, aStudents[i].DoB, '\n');
		getline(in, aStudents[i].gender, '\n');
		getline(in, ignore, '\n');
		aStudents[i].active = ((ignore == "1") ? 1 : 0);
		getline(in, ignore, '\n');
	}
}

void viewAttendanceList()
{
	string courseID;
	string classID;

	cout << "Input Class ID: ";
	cin >> classID;
	convertToUpper(classID);
	cout << "Input Course ID: ";
	cin >> courseID;
	convertToUpper(courseID);

	Course* aCourses;
	int nCourses;

	loadCoursesFromTXT("Courses.txt", aCourses, nCourses);

	Course course;
	course.ID = "";

	for (int i = 0; i < nCourses; i++)
	{
		if (aCourses[i].ID.compare(courseID) == 0 || aCourses[i].classID.compare(classID) == 0)
		{
			course = aCourses[i];
			break;
		}
	}

	if (course.ID.compare("") == 0)
	{
		cout << "Cant find the inputted course" << endl;
		return;
	}

	string filename = "";
	filename = classID + "-" + courseID + ".txt";
	
	string filenameTXT = classID + "-" + courseID + "-AttendanceList.txt";
	ofstream fout(filenameTXT);
	if(!fout.is_open())
	{
		cout << "Cant open " << filenameTXT << endl;
		return;
	}

	Student* aStudents;
	int nStudents;

	loadDataCourse(filename, aStudents, nStudents);

	cout << "THE ATTENDANCE LIST: " << endl;
	for (int i = 0; i < nStudents; i++)
	{
		if (aStudents[i].active == 1) {
			cout << i + 1 << ") " << aStudents[i].ID << " - " << aStudents[i].fullName << endl;
			fout << aStudents[i].ID << endl;
			fout << aStudents[i].fullName << endl;
			fout << aStudents[i].DoB << endl;
			fout << aStudents[i].gender << endl;
			fout << aStudents[i].active << endl;
			fout << endl;
		}
	}
	fout.close();

	return;
}

//11. Create / update / delete / view all lecturers.

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
	cin.ignore(1);
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
	cout << "\nCreate account for lecturer [" << name << "] successfully.\n";
}

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
		cin.ignore(1);
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

	cin.ignore(1);
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
	system("pause");
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

//**3. Scoreboard.
void scoreBoardMode() {
	cout << "> 1. Search and view the scoreboard of a course.\n";
	cout << "> 2. Export a scoreboard to a csv file.\n";
	cout << "> 3. Export all scoreboard to csv files.\n";
	cout << "> 4. Back to staff menu.\n";

OPTION:
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 4)
		goto OPTION;
	if (option == 4)
		return;
	
	string classID = "", courseID = "", sourceTXT = "", destinationCSV = "";
	cin.ignore(1);
	
	createListOfScoreBoard();

	cout << "> Enter class ID: ";
	getline(cin, classID, '\n');
	convertToUpper(classID);

	cout << "> Enter course ID: ";
	getline(cin, courseID, '\n');
	convertToUpper(courseID);
	sourceTXT = classID + '-' + courseID + "-Scoreboard.txt";

	getDestinationTXT(sourceTXT, destinationCSV);
	
	switch(option) {
		case 1: 
			viewScoreBoard(sourceTXT);
			cout << "===================================\n";
			break;
		case 2:
			export_A_ScoreboardToCsv(sourceTXT, destinationCSV);
			cout << "===================================\n";
			break;
		case 3: 
			exportScoreBoardToCSV();
			cout << "===================================\n";
			break;
	}
	scoreBoardMode();
}

//Search and view the scoreboard of a course.
void viewScoreBoard(string sourceTXT) {
	ifstream fin;
	if(isFileOpen(fin, "ListScoreBoard.txt") == false)
		return;

	string cmpStr = "";

	while (!fin.eof()) {
		getline(fin, cmpStr, '\n');
		if(cmpStr == "")
			break;
		
		if(cmpStr == sourceTXT) {
			loadScoreBoard(sourceTXT);
			cout << "-----------------------------------\n";
			fin.close();
			return;
		} 
	}
	cout << "Can not found " << sourceTXT << ", the file has not been created yet.\n";

	fin.close();
}

void loadScoreBoard(string filename) {
	ifstream fin;
	if (isFileOpen(fin, filename) == false) 
		return;

	string line, ignore;
	getline(fin, line, '\n');
	cout << "Number of student: " << line << ".\n";
	getline(fin, ignore, '\n');

	while (!fin.eof()) {
		getline(fin, line, '\n');
		if (line == "")
			break;
		cout << "\nStudent ID: " << line << endl;

		getline(fin, line, '\n');
		cout << "Name: " << line << endl;

		getline(fin, line, '\n');
		cout << "Midterm: " << line << endl;

		getline(fin, line, '\n');
		cout << "Final: " << line << endl;

		getline(fin, line, '\n');
		cout << "Bonus: " << line << endl;

		getline(fin, line, '\n');
		cout << "Total: " << line << endl;
		getline(fin, ignore, '\n');
	}
	fin.close();
}

void createListOfScoreBoard()
{
	ifstream in;
	in.open("ListCourses.txt");

	ofstream out;
	out.open("ListScoreBoard.txt");

	if (!in.is_open())
		cout << "can't open file ListCourses.txt" << endl;
	else
		if (!out.is_open())
			cout << "can't open file ListScoreBoard.txt" << endl;
		else {
			string buffer, buffer1;
			while (!in.eof()) {
				getline(in,buffer);
				if (buffer == "")
					break;

				buffer1 = "";
				for (int i = 0; buffer[i] != '.'; i++)
					buffer1 += buffer[i];
				
				buffer1 += "-Scoreboard.txt";
				out << buffer1 << endl;
			}
			in.close();
			out.close();
		}
}

//2. Export a scoreboard to a csv file.
void getDestinationTXT(const string sourceTXT, string& destinationCSV) {
	destinationCSV = "";

	for (int i = 0; sourceTXT[i] != '.'; i++)
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
	string ignore = "";

	//read score from .txt
	fin >> nScor;
	scores = new ScoreBoard[nScor];
	
	for(int i = 0; i < nScor; i++) {
		fin.ignore(1);
		getline(fin, ignore, '\n');
		getline(fin, scores[i].studentID, '\n');
		getline(fin, scores[i].name, '\n');
		fin >> scores[i]._midTerm;
		fin >> scores[i]._final;
		fin >> scores[i]._bonus;
		fin >> scores[i]._total;
	}
	fin.close();

	for (int i = 0; i < nScor; i++) {
		fout << i + 1 << ',';
		fout << scores[i].studentID << ',';
		fout << fixed << setprecision(2) << scores[i].name << ',';
		fout << fixed << setprecision(2) << scores[i]._midTerm << ',';
		fout << fixed << setprecision(2) << scores[i]._final << ',';
		fout << fixed << setprecision(2) << scores[i]._bonus << ',';
		fout << fixed << setprecision(2) << scores[i]._total << endl;
	}
	fout.close();

	delete[] scores;

	cout << "Export " << sourceTXT << " to " << destinationCSV << " successfully.\n";
}

//3. Export all scoreboard to csv files.
void exportScoreBoardToCSV() {
	ifstream fin;
	if (isFileOpen(fin, "ListScoreBoard.txt") == false) {
		cout << "Can not open ListScoreBoard.txt.\n";
		return;
	}

	string filename = "";

	while (!fin.eof()) {
		getline(fin, filename, '\n');
		if (filename == "")
			break;
		string temp = "";
		getDestinationTXT(filename, temp);

		export_A_ScoreboardToCsv(filename, temp);
	}
	fin.close();
}

//**4. Attendance list.
void attendanceListMode() {
	cout << "> 1. Search and view attendance list of a course.\n";
	cout << "> 2. Export a attendance list to a csv file.\n";
	cout << "> 3. Back to staff menu.\n";

OPTION:
	cout << "> Which mode do you want to access ? \n";
	int option;
	cin >> option;
	if (option < 1 || option > 3)
		goto OPTION;

	switch(option) {
		case 1: 
			viewAttendanceList();
			cout << "===================================\n";
			break;
		case 2:
			exportAttendanceListToCSV();
			cout << "===================================\n";
			break;
		case 3:
			return;
	}
	attendanceListMode();
}

//**5. Change staff password.
void changeStaffPassword(User& user) {
	Staff* staffs;
	int n = 0;

	cin.ignore(1);
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
		fout << endl << staffs[i].user.username << endl << staffs[i].user.password << endl << staffs[i].name << endl;
	}

	fout.close();
	delete[]staffs;
}


//27 export attendance list to csv
void exportAttendanceListToCSV()
{
	string courseID;
	string classID;

	cout << "Input Class ID: ";
	cin >> classID;
	convertToUpper(classID);
	cout << "Input Course ID: ";
	cin >> courseID;
	convertToUpper(courseID);

	Course* aCourses;
	int nCourses;

	loadCoursesFromTXT("Courses.txt", aCourses, nCourses);

	Course course;
	course.ID = "";

	for (int i = 0; i < nCourses; i++)
	{
		if (aCourses[i].ID.compare(courseID) == 0 && aCourses[i].classID.compare(classID) == 0)
		{
			course = aCourses[i];
			break;
		}
	}
	if (course.ID.compare("") == 0)
	{
		cout << "Cant find the inputted course" << endl;
		return;
	}

	string filenameTXT = "";
	filenameTXT = classID + "-" + course.ID + ".txt";
	string filenameCSV = classID + "-" + course.ID + "-AttendanceList.csv";

	ifstream fin(filenameTXT);
	ofstream fout(filenameCSV);

	if (!fin.is_open())
	{
		cout << "Cant find " << filenameTXT;
		return;
	}

	if (!fout.is_open())
	{
		cout << "Cant create " << filenameCSV;
		return;
	}

	Student * aStudents;
	int nStudents;

	loadDataCourse(filenameTXT, aStudents, nStudents);

	for (int i = 0; i < nStudents; i++)
	{
		if (aStudents[i].active == 1) {
			fout << aStudents[i].ID << "," << aStudents[i].fullName<<","<< aStudents[i].DoB << "," << aStudents[i].gender << "," << endl;
		}
	}

	cout << "Export " << filenameTXT << " to " << filenameCSV << " successfully.\n";

	fin.close();
	fout.close();
	return;
}

//**6. View profile information.
//This function is located in Header.h

//**7. Log out