#include "Caro.h"

int main()
{
	ifstream in("student.csv");

	if (!in.is_open())
	{
		cout << "Cant open file" << endl;
		return 1;
	}
	int nStudents = 2;
	Student* aStudent = new Student[2];
	importStudentsFromCSV(in, aStudent, nStudents);
	createUserPassword(aStudent,nStudents);
	writeToStudentTxt((char*)"Student.txt",nStudents,aStudent);
	writeToStudentUsersTxt((char*)"StudentUsers.txt", nStudents, aStudent);

	return 0;
}