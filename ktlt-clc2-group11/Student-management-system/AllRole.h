#ifndef _ALLROLE_H_
#define _ALLROLE_H_

#include "Header.h"

void menu();

void login(User user, unsigned int& loginMode);

bool isStaffLogin(const User loginUser);
bool isLecturerLogin(const User loginUser);
bool isStudentLogin(const User loginUser);

#endif
