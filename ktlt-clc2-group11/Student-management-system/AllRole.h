#ifndef _ALLROLE_H_
#define _ALLROLE_H_

#include "Header.h"

void menu();
void login(User user, unsigned int& loginMode);
bool isStaffLogin(User loginUser);
bool isLecturerLogin(User loginUser);
bool isStudentLogin(User loginUser);

#endif
