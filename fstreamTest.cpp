#include <cstdlib>
#include <iostream>
#include <string>
#include "Library.h"

LibraryTree<Book> tree;

int main()
{
	fillTree(&tree, "LibraryDataTest.csv");
	// Print books in the data file
	cout << "PRINT BOOKS IN FILE:\n";
	tree.printTreeInOrder();
	cout << "Tree depth of: " << tree.maxDepth() << endl;
	cout << "Tree width of: " << tree.getWidth() << endl;

	// Insert a new book and print
	cout << "\nINSERT NEW BOOK TO TREE AND FILE:\n";
	insert(&tree, "Axiom's End", "Ellis, Lindsay");
	tree.printTreeInOrder();
	
	// Remove the new book and print
	cout << "\nREMOVE BOOK FROM TREE AND FILE:\n";
	remove(&tree, "Axiom's End");
	tree.printTreeInOrder();
	return 0;
}