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
	string line;
	string word = "";
	string dL = "\",\"";

	myFile.open("Library Data.csv");//("Titles.txt");//
	getline(myFile, line); // Skip header line

	if (!myFile.good())
	{
		cout << "Invalid file\n";
	}
	else {
		getline(myFile, line); // Get 1st line of data
		while (myFile.good() && !myFile.eof())
		{
			if (myFile.good()) {
				size_t dLPos = line.find(dL, 0);
				// Parse Title
				for (size_t i = 3; i < dLPos - 2; ++i) {
					word += line[i];
				}
				title = word;
				word = "";
				// Parse Author
				for (size_t i = dLPos + 5; i < line.size() - 3; ++i) {
					word += line[i];
				}
				author = word;
				word = "";
				book.setTitle(title);
				book.setAuthor(author);
				(*tree).insertNode(book);
				getline(myFile, line); // Get next line of data
			}
		}
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
