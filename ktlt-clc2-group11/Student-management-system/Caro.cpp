#include "Caro.h"

void importStudentsFromCSV(ifstream& in, Student students[], int& nStudents)
{

	char tempData[100];
	for(int i=0;i<nStudents;i++)
	{
		in.getline(tempData, 100);
		char* temp;
		//access first member
		temp = strtok(tempData, ",");
		students[i].name = temp;

		students[i].name = new char[50];
		students[i].name [strlen(students[i].name)] = '\0';
		strcpy(students[i].name, temp);

		//access another member
		temp = strtok(NULL, ",");
		students[i].ID = temp;

		students[i].ID = new char[9];
		students[i].ID[strlen(students[i].ID)] = '\0';
		strcpy(students[i].ID, temp);

		temp = strtok(NULL, ",");
		strcpy(students[i].DoB,temp);

		//test read
		cout << students[i].name << endl;
		cout << students[i].ID   <<endl;
		cout << students[i].DoB << endl;
	}

}

void createUserPassword(Student a[], int nStudents)
{
	
	for (int i = 0; i < nStudents; i++) {	

		a[i].password = new char[9];
		a[i].password[9] = '\0';

		strcpy_s(a[i].password,9, a[i].DoB);

		//test created password
		cout << "PASSWORD: "<<a[i].password<<endl;
	}
}

void writeToStudentTxt(char* filename, int nStudents, Student a[])
{
	ofstream out(filename);
	if (!out.is_open())
	{
		cout << "Cant create file StudentUsers.txt" << endl;
		return;
	}
	out << nStudents << endl;
	for (int i = 0; i < nStudents; i++)
	{
		out << a[i].ID << endl;
		cout << a[i].ID << endl;
		out << a[i].password << endl;
		cout << a[i].password << endl;
		out << a[i].name << endl;
		cout << a[i].name << endl;
	}
}

void writeToStudentUsersTxt(char* filename, int nStudents, Student a[])
{
	ofstream out(filename);
	if (!out.is_open())
	{
		cout << "Cant create file StudentUsers.txt" << endl;
		return;
	}
	out << nStudents<<endl;
	for (int i = 0; i < nStudents; i++)
	{
		out << a[i].ID << endl;
		out << a[i].password<<endl;
		out << a[i].name<<endl;
	}
}