#include "Header.h"

bool isFileOpen(ifstream& fin, string filename) {
	fin.open(filename, ios::in);
	if (!fin.is_open()) {
		cout << "Can not open " << filename << endl;
		return false;
	}
	return true;
}

void changePassword(User& user) {
	string newPass = "";
	string curPass = "";

	do {
		cout << "> Enter your current password : ";
		getline(cin, curPass, '\n');
	} while (curPass != user.password);

	cout << "> Enter your new password : ";
	getline(cin, newPass, '\n');

	user.password = newPass;
}

void viewProfile(const User user) {
	cout << "Name : " << user.name << endl;
	cout << "User name : " << user.username << endl;
}

void copyFile(string source, string destination) {
	ifstream fin;
	ofstream fout;

	fin.open(source, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "Can not open " << source << endl;
		return;
	}

	fout.open(destination, ios::out | ios::binary);
	if (!fout.is_open()) {
		cout << "Can not open " << destination << endl;
		return;
	}

	int x = 0;
	char buff[MAX_BUF];

	do {
		fin.read((char*)buff, MAX_BUF);
		x = fin.gcount();
		fout.write((char*)buff, x);
	} while (x == MAX_BUF);

	fin.close();
	fout.close();
}
