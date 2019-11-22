/*
	* Authors:		Barragan, Alejandro
	*				Lu, Stephanie
	*				McClain, Micah
	*
	* Date: Nov 7, 2019
	* Description:
	*
	*
	*
	* For: San Bernardino Valley College - CS 265: Data Structures - Fall 2019
*/
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
	int value;
	cout << "1-Admin\n";
	cout << "2-Search for book\n";	
	cout << "3-Exit\n";	

	cin >> value;
	//we should have a menu... so switch. Unless there is something else we can do...
	switch (value)
	{
	case 1:
		/* we can probably create a username and password for one admin...*/
		break;
	case 2:
		/*...*/
		break;
	case 3:
		exit(EXIT_FAILURE);
		break;
	default:
		break;
	}
}