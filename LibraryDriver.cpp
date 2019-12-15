#include <iostream>
#include <string>
#include "Library.h"
#include "Extra.h"

LibraryTree<Book> treeT;
LibraryTree<Book> treeA;

int main()
{
	fillTree(&treeT, "Book1.csv");

	insertBook(&treeT, "Axiom's End", "Ellis, Lindsay");
	treeT.searchSpecific("Axiom's End");

	treeT.changeBookStatus("Axiom's End", 0);
	removeBook(&treeT, "Axiom's End");
	treeT.searchSpecific("Axiom's End");

	treeT.printTree();

	return 0;
}
