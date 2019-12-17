/**********************************************************************************************
	Admin.h

	Authors:	Stephanie Lu
				Micah McClain
				Alejandro Barragan

	Date:		Dec 19, 2019

	Description: https://github.com/roombas/LibraryTree
	For: San Bernardino Valley College - CS 265: Data Structures - Fall 2019
/**********************************************************************************************/

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>

using namespace std;

/******************************ADMIN PUBLIC CLASS OPERATIONS***********************************
	bool checkUser(string)					--> Compares the input to variable 'username'
	bool checkPass(string)					--> Compares the input to variable 'passwd'
/**********************************************************************************************/

class Admin
{
public:
	// Checks the username
	bool checkUser(string value) {
		return value == username;
	}

	// Checks the password
	bool checkPass(string value) {
		return value == passwd;
	}

private:
	string username = "admin";//"Darkling-01";
	string passwd = "password";//"Welcome2CS";
};
#endif