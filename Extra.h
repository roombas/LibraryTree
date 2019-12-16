#ifndef Extra_H
#define Extra_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Library.h"
using namespace std;

//function that prints tree inorder by author
template <typename T>
void LibraryTree<T>::printTreeA() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else
		printHelperA(root);
}
template <typename T>
void LibraryTree<T>::printHelperA(Lnode* t) const
{
	if (t != NULL)
	{
		printHelperA(t->left);
		cout << "Author: " << t->data.getTitle() << "\nTitle: " << t->data.getAuthor()
			<< "\nChecked In: " << t->data.getBookStatus() << "\n\n";
		printHelperA(t->right);
	}
}

//fill tree via author
void fillTreeA(LibraryTree<Book>* tree)
{
	string fileName = "Book1.csv";
	ifstream myFile;
	Book book;
	string title;
	string author;
	int checkedIn;
	string line;
	string word = "";
	int num = -1;
	string dL = "\",\"";
	string dL1 = "\",";

	myFile.open(fileName);
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
				for (size_t i = dLPos + 5; i < line.size() - 5; ++i) {
					word += line[i];
				}
				author = word;
				word = "";

				size_t dLPos1 = line.rfind(dL1, 0);
				// Parse Checked in or out
				for (size_t i = dLPos1 + 4; i < line.size(); ++i) {
					word = line[i];
				}
				istringstream iss(word);
				iss >> num;
				checkedIn = num;
				word = "";
				num = -1;

				book.setTitle(author);
				book.setAuthor(title);
				book.setBookStatus(checkedIn);
				(*tree).insertNode(book);
				getline(myFile, line); // Get next line of data
			}
		}
	}
	myFile.close();
}
void fillTreeA(LibraryTree<Book>* tree, string file) {
	string fileName = file;
	fillTreeA(tree);
}

#endif