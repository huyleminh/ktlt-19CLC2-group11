#ifndef _CARO_H_
#define _CARO_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#pragma warning(disable : 4996)

using namespace std;

struct Date {
	int day;
	int month;
	int year;
};

struct Student
{
	char* name=new char [50];
	char* ID=new char[9];
	bool gender;
	char DoB[9];
	int* classID;
	char* password=new char[9];
};

struct lecturer {
	char name[50];
	char classID[9];
	char courseID[9];
};


void importStudentsFromCSV(ifstream& in, Student students[], int& nStudents);
void createUserPassword(Student a[], int nStudents);
void writeToStudentTxt(char* filename, int nStudents, Student a[]);
void writeToStudentUsersTxt(char* filename, int nStudents, Student a[]);

#endif



#pragma once
