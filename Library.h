#ifndef Library_H
#define Library_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

class Book
{
private:
	string title;
	string author;
	int bookStatus;	//= 1 if checked in, = 0 if checked out

public:
	Book() {}
	Book(string t, string a)
	{
		title = t;
		author = a;
	}
	Book(string t, string a, int b)
	{
		title = t;
		author = a;
		bookStatus = b;
	}
	string getTitle()
	{
		return title;
	}
	string getAuthor()
	{
		return author;
	}
	int getBookStatus()
	{
		return bookStatus;
	}
	void setTitle(string t)
	{
		title = t;
	}
	void setAuthor(string a)
	{
		author = a;
	}
	void setBookStatus(int b)
	{
		bookStatus = b;
	}
};

//AVL tree class
template <typename T>
class LibraryTree
{
private:
	static const int ALLOWED_IMBALANCE = 1; //for balancing tree
	struct Lnode
	{
		T data;
		Lnode* left;
		Lnode* right;
		int height;

		Lnode(T b, Lnode* lt, Lnode* rt, int h = 0)
			: data{ b }, left{ lt }, right{ rt }, height{ h } {}
	};
	Lnode* root;

public:
	LibraryTree()
	{
		root = nullptr;
	}
	~LibraryTree()
	{
		clearAll();
	}
	bool isEmpty() const
	{
		return root == nullptr;
	}
	int height(Lnode* t) const
	{
		return t == nullptr ? -1 : t->height;
	}
	void balance(Lnode*&);
	void rotateWithLeftChild(Lnode*&);
	void rotateWithRightChild(Lnode*&);
	void doubleWithLeftChild(Lnode*&);
	void doubleWithRightChild(Lnode*&);

	void insert(Lnode*&, Lnode*&);
	void insertNode(T);

	void makeEmpty(Lnode*&);
	void clearAll();

	bool search(string);
	bool searchTool(Lnode*, string);
	bool searchSpecific(string);
	bool specificInOrder(Lnode*, string);
	void searchAll(string);
	void allInOrder(Lnode*, string);
	void inOrder(Lnode*) const;
	void printTreeInOrder() const;
};

template <typename T>
void LibraryTree<T>::clearAll()
{
	makeEmpty(root);
}
//clears out tree and memory
template <typename T>
void LibraryTree<T>::makeEmpty(Lnode*& node)
{
	if (node != nullptr)
	{
		makeEmpty(node->left);
		makeEmpty(node->right);
		delete node;
	}
	node = nullptr;
}

//function to balance tree
template <typename T>
void LibraryTree<T>::balance(Lnode*& t)
{
	if (t == NULL)
		return;

	if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
		if (height(t->left->left) >= height(t->left->right))
			rotateWithLeftChild(t);
		else
			doubleWithLeftChild(t);
	else
		if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
			if (height(t->right->right) >= height(t->right->left))
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);

	t->height = max(height(t->left), height(t->right)) + 1;
}
template <typename T>
void LibraryTree<T>::rotateWithLeftChild(Lnode*& k2)
{
	Lnode* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}
template <typename T>
void LibraryTree<T>::rotateWithRightChild(Lnode*& k1)
{
	Lnode* k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	k1 = k2;
}
template <typename T>
void LibraryTree<T>::doubleWithLeftChild(Lnode*& k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}
template <typename T>
void LibraryTree<T>::doubleWithRightChild(Lnode*& k1)
{
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}

template <typename T>
bool LibraryTree<T>::search(string key)
{
	return searchTool(root, key);
}
//returns true if found title, rteurns false if no title
template <typename T>
bool LibraryTree<T>::searchTool(Lnode* node, string key)
{
	if (node != nullptr)
	{
		if (node->data.getTitle() == key)
		{
			return true;
		}
		else if (node->data.getTitle() < key)
			searchTool(node->right, key);
		else
			searchTool(node->left, key);
	}
	else
	{
		cout << "Title not found.\n";
		return false;
	}
}
//search function for all matching books
template <typename T>
void LibraryTree<T>::searchAll(string key)
{
	allInOrder(root, key);
}
//traverses full tree in-order to find and print all books with the specified key word
template <typename T>
void LibraryTree<T>::allInOrder(Lnode* node, string key)
{
	if (node != nullptr)
	{
		allInOrder(node->left, key);
		string tmp = node->data.getTitle();
		if (node->data.getTitle() == key || tmp.find(key) != string::npos)
		{
			cout << "Title: " << node->data.getTitle() << "\nAuthor: "
				<< node->data.getAuthor() << "\nChecked In: "
				<< node->data.getBookStatus() << "\n\n";
		}
		allInOrder(node->right, key);
	}
}
//search function for specific book
template <typename T>
bool LibraryTree<T>::searchSpecific(string key)
{
	return specificInOrder(root, key);
}
//traverses tree and prints out the specified result
template <typename T>
bool LibraryTree<T>::specificInOrder(Lnode* node, string key)
{
	if (node != nullptr)
	{
		string tmp = node->data.getTitle();
		//finds first result of condition in tree
		if (node->data.getTitle() == key || tmp.find(key) != string::npos)
		{
			cout << "Title: " << node->data.getTitle() << "\nAuthor: "
				<< node->data.getAuthor() << "\nChecked In: "
				<< node->data.getBookStatus() << "\n\n";
			return true;
		}
		else if (node->data.getTitle() < key)
			specificInOrder(node->right, key);
		else
			specificInOrder(node->left, key);
	}
	else
	{
		cout << "Title not found\n";
		return false;
	}
}

//function that prints tree inorder
template <typename T>
void LibraryTree<T>::printTreeInOrder() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else
		inOrder(root);
}
template <typename T>
void LibraryTree<T>::inOrder(Lnode* t) const
{
	if (t != NULL)
	{
		inOrder(t->left);
		cout << "Title: " << t->data.getTitle() << "\nAuthor: " << t->data.getAuthor()
			<< "\nChecked In: " << t->data.getBookStatus() << "\n\n";
		inOrder(t->right);
	}
}

//insert class object Book
template <typename T>
void LibraryTree<T>::insertNode(T b)
{
	Lnode* node = new Lnode{ b, nullptr, nullptr };
	node->data = b;
	node->left = nullptr;
	node->right = nullptr;
	insert(root, node);
}
template <typename T>
void LibraryTree<T>::insert(Lnode*& nodePtr, Lnode*& node)
{
	if (nodePtr == nullptr)
		nodePtr = node;
	else if (node->data.getTitle() < nodePtr->data.getTitle())
		insert(nodePtr->left, node);
	else
		insert(nodePtr->right, node);

	balance(nodePtr);
}

/***********************************/
void fillTree(LibraryTree<Book>* tree)
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

				book.setTitle(title);
				book.setAuthor(author);
				book.setBookStatus(checkedIn);
				(*tree).insertNode(book);
				getline(myFile, line); // Get next line of data
			}
		}
	}
	myFile.close();
}
void fillTree(LibraryTree<Book>* tree, string file) {
	string fileName = file;
	fillTree(tree);
}
//change book to checked in or out
void changeBookStatus(LibraryTree<Book>* tree, string title, int num)
{
	if ((*tree).search(title))
	{
		string fileName = "Book1.csv";
		ifstream myFile(fileName); // Data file
		ofstream upFile("Book2.csv"); // Update file
		string line;
		size_t pos;

		stringstream ss;
		ss << num;
		string str = ss.str();

		while (myFile.good() && !myFile.eof())
		{
			getline(myFile, line);
			// Write the current line to the new file
			if ((pos = line.find(title)) != string::npos)
			{
				string dL1 = "\",";
				size_t dLPos1 = line.rfind(dL1);
				line = line.replace((dLPos1 + 2), 1, str);
				upFile << line;
			}
			if (myFile.good() && (pos = line.find(title)) == string::npos)
			{
				upFile << line;
			}
			// Add a line break to all but the last line
			if (myFile.good()) {
				upFile << "\n";
			}
		}
		// Close files
		myFile.close();
		upFile.close();
		//Remove old file
		remove(fileName.c_str());
		rename("Book2.csv", fileName.c_str());
		// Refill Tree
		tree->clearAll();
		fillTree(tree);
	}
}

// Add Book entry to the data file
void insertBook(LibraryTree<Book>* tree, string title, string author) {
	string fileName = "Book1.csv";
	ifstream myFile(fileName); // Data file
	ofstream upFile("Book2.csv"); // Update file
	// Copy old file
	string line;
	while (myFile.good() && !myFile.eof()) {
		// Write the current line to the new file
		if (myFile.good()) {
			getline(myFile, line);
			upFile << line;
		}
		// Add a line break to all but the last line
		if (myFile.good()) {
			upFile << "\n";
		}
	}
	// Write new line
	upFile << "\"\"\"" + title + "\"\"\",\"\"\"" + author + "\"\"\"," << 1 << endl;
	// Close files
	myFile.close();
	upFile.close();
	// Remove old file
	remove(fileName.c_str());
	rename("Book2.csv", fileName.c_str());
	// Update Tree
	Book book;
	book.setTitle(title);
	book.setAuthor(author);
	book.setBookStatus(1);
	(*tree).insertNode(book);
}

// Remove Book entry from the data file
void removeBook(LibraryTree<Book>* tree, string title) {
	string fileName = "Book1.csv";
	ifstream myFile(fileName); // Data file
	ofstream upFile("Book2.csv"); // Update file
	// Copy old file
	string line;
	while (myFile.good() && !myFile.eof()) {
		// Get next line
		if (myFile.good()) {
			getline(myFile, line);
		}
		// If title in line, skip line
		if (myFile.good() && line.find(title, 0) > line.length()) {
			upFile << line;
			upFile << "\n";
		}
	}
	// Close files
	myFile.close();
	upFile.close();
	// Remove old file
	remove(fileName.c_str());
	rename("Book2.csv", fileName.c_str());
	// Refill Tree
	tree->clearAll();
	fillTree(tree);
}

#endif
