#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Date {
	int day;
	int month;
	int year;
};

struct User {
	string username;
	string password;
};

struct Staff {
	User user;
	string name;
};

struct Lecturer {
	User user;
	string name;
};

struct Student_User {
	User user;
	string name;
};

struct Student{
	string ID;
	string fullName;
	string gender;
	string DoB;
	string classID;
};

inline bool isFileOpen(ifstream &fin, const char* filename) {
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Can not open " << filename << endl;
		return false;
	}
	return true;
}
#endif