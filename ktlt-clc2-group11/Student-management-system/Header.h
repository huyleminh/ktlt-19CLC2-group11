#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#define MAX_BUF 1000
using namespace std;

struct Date {
	int day;
	int month;
	int year;
	void inputDay() {
		cout << "Day: ";
		cin >> day;
		cout << "Month: ";
		cin >> month;
		cout << "year: ";
		cin >> year;
	}
	void deleteDay() {
		day = 0; month = 0; year = 0;
	}
	void printDay() {
		cout << day << "/" << month << "/" << year << endl;
	}
};

struct User {
	string username;
	string password;
	string name;
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

struct Score {
	float midterm;
	float final;
	float bonus;
	float total;
};

struct Student {
	string ID;
	string fullName;
	string gender;
	string DoB;
	string classID;
	bool active;
	Score score;
};

struct Time
{
	string dayOfWeek;
	string startHour;
	string startMin;
	string endHour;
	string endMin;
	void inputTime()
	{
		cout << "day of week: ";
		cin >> dayOfWeek;

		cout << "start hour: ";
		cin >> startHour;

		cout << "start min: ";
		cin >> startMin;

		cout << "end hour: ";
		cin >> endHour;

		cout << "end min: ";
		cin >> endMin;
	}
	void deleteTime()
	{
		dayOfWeek = "";
		startHour = "";
		endHour = "";
		startMin = "";
		endMin = "";
	}
	void printTime()
	{
		cout << "Day of week: " << dayOfWeek << endl;
		cout << startHour << ":" << endHour << endl;
		cout << startMin << ":" << endMin << endl;
	}
};

struct Course
{
	string ID;
	string name;
	string classID;
	string lecAccount;
	Date startDate;
	Date endDate;
	Time courseTime;
	string room;
	bool active = 1;
	string sem;
	string acaYear;
};

struct Semester {
	int numberOfCourses;
	Course* coursesArray;
};

struct academicYear {
	int startYear;
	int endYear = startYear + 1;
	Semester semesterArray[3];
};

struct ScoreBoard {
	string studentID;
	string name;
	float _midTerm;
	float _final;
	float _bonus;
	float _total;
};


bool isFileOpen(ifstream& fin, string filename);
void changePassword(User& user);
void viewProfile(const User user);
void copyFile(string source, string destination);

#endif