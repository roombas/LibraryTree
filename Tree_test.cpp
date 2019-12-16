/*
	* Authors:		Barragan, Alejandro
	*				Lu, Stephanie
	*				McClain, Micah
	*
	* Date: Dec 15, 2019
	* Description:
	*
	* For: San Bernardino Valley College - CS 265: Data Structures - Fall 2019
*/

#include <iostream>
#include <string>
#include "Library.h"
#include "Extra.h"
#include "Admin.h"

/***************************LIBRARYTREE PUBLIC CLASS OPERATIONS********************************
	bool searchSpecific(title)				--> Searches for title using partial or full title.
												Must begin with start of title
												(Ex: Harry Potter, NOT arry Potter)
	void searchAll(title)					--> Searches for all instances of a key word.
												Must begin with start of title
	void checkStatus(title)					--> Check status of book in database
	void clearAll();						--> Clears tree
	void printTree() const;					--> Prints tree inorder (by title)
	void printTreeA() const;				--> Prints tree inorder (by author)
	void changeBookStatus(title, int)		--> Changes book status of file and tree (0 or 1)
/*********************************PUBLIC OPERATIONS********************************************
	void insertBook(&tree, title, author)	--> Adds a new book to .csv file
	void removeBook(&tree, title)			--> Removes book from .csv file
	void fillTree(&tree, filename)			--> Fills initial tree with books from file
/**********************************************************************************************/

int main()
{
	initializeTree();
	setUser();

	return 0;
}