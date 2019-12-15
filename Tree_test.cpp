#include <iostream>
#include <string>
#include "Library.h"
#include "Extra.h"

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