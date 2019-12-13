#include <cstdlib>
#include <iostream>
#include <string>
#include "Library.h"

void fillTree(LibraryTree<Book>* tree)
{
	ifstream myFile;
	Book book;
	string title;
	string author;

	myFile.open("Data.csv");//("Titles.txt");//
	if (!myFile)
	{
		cout << "Invalid file\n";
	}

	while (!myFile.eof())
	{
		myFile >> title >> author;
		book.setTitle(title);
		book.setAuthor(author);
		(*tree).insertNode(book);
	}
	myFile.close();
}

int main()
{
	LibraryTree<Book> tree;
	fillTree(&tree);
	tree.printTreeInOrder();
	cout << "Tree depth of: " << tree.maxDepth() << endl;
	cout << "Tree width of: " << tree.getWidth() << endl;

	return 0;
}
