#ifndef _ALLROLE_H_
#define _ALLROLE_H_

#include "Header.h"

struct User {
	string username;
	string password;
};

struct Staff {
	User user;
	string name;
	//string gender;
};

struct Lecturer {
	User user;
	string name;
};

void menu();
void login(User user, unsigned int& loginMode);
bool isStaffLogin(User loginUser);
bool isLecturerLogin(User loginUser);
bool isStudentLogin(User loginUser);

#endif
