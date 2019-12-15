/*
	* Authors:		Barragan, Alejandro
	*				Lu, Stephanie
	*				McClain, Micah
	*
	* Date: Dec 15, 2019
	* Description:
	*
	*
	*
	* For: San Bernardino Valley College - CS 265: Data Structures - Fall 2019
*/

#include <iostream>
#include <string>
#include "Library.h"
#include "Extra.h"

/***************************LIBRARYTREE PUBLIC CLASS OPERATIONS*****************************
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
/*********************************PUBLIC OPERATIONS*****************************************
	void insertBook(&tree, title, author)	--> Adds a new book to .csv file
	void removeBook(&tree, title)			--> Removes book from .csv file
	void fillTree(&tree, filename)			--> Fills initial tree with books from file
/*******************************************************************************************/

LibraryTree<Book> treeT; //title sorted tree
LibraryTree<Book> treeA; //author sorted tree

int main()
{
	fillTree(&treeT, "Book1.csv");
	fillTreeA(&treeA, "Book1.csv");

	cout << "PRINT TREE BY TITLE*****************\n";
	treeT.printTree();
	cout << "PRINT TREE BY AUTHOR*****************\n";
	treeA.printTreeA();

	//add new book
	insertBook(&treeT, "Axiom's End", "Ellis, Lindsay");
	//search for book
	treeT.searchSpecific("Axiom's End");
	//search if book checked in
	treeT.changeBookStatus("Axiom's End", 0);
	//remove book
	removeBook(&treeT, "Axiom's End");
	//search for book
	treeT.searchSpecific("Axiom's End");
	//search for instances of all titles starting with "Fun"
	treeT.searchAll("Fun");

	return 0;
}
