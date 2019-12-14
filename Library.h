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
	//string key;		//first 3 letters for title
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
	//Book(string t, string k, string a, int b)
	//{
	//	title = t;
	//	key = k;
	//	author = a;
	//	bookStatus = b;
	//}
	string getTitle()
	{
		return title;
	}
	//string getTitleKey()
	//{
	//	return key;
	//}
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
	//void setTitleKey(string k)
	//{
	//	key = k;
	//}
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
	int maxDepth()
	{
		return getDepth(root);
	}
	bool isEmpty() const
	{
		return root == nullptr;
	}
	int height(Lnode* t) const
	{
		return t == nullptr ? -1 : t->height;
	}
	int getWidth();
	int numAtLevel(Lnode*, int);
	int getDepth(Lnode*);
	void balance(Lnode*&);
	void balanceCheck(Lnode*&);
	void rotateWithLeftChild(Lnode*&);
	void rotateWithRightChild(Lnode*&);
	void doubleWithLeftChild(Lnode*&);
	void doubleWithRightChild(Lnode*&);
	void inOrder(Lnode*) const;
	void printTreeInOrder() const;
	void insert(Lnode*&, Lnode*&);
	void insertNode(T);

	void makeEmpty(Lnode*&);
	void clearAll();

	bool specificInOrder(Lnode*, string);
	bool searchSpecific(string);
	void allInOrder(Lnode*, string);
	void searchAll(string);

	bool bookStatus(Lnode*, string);
	void changeBookStatus(string, int);
};

template <typename T>
void LibraryTree<T>::clearAll()
{
	makeEmpty(root);
}
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

//search function for specific book
template <typename T>
bool LibraryTree<T>::searchSpecific(string key)
{
	return specificInOrder(root, key);
}

//search function for all matching books
template <typename T>
void LibraryTree<T>::searchAll(string key)
{
	allInOrder(root, key);
}

template <typename T>
void LibraryTree<T>::changeBookStatus(string title, int num)
{
	if (bookStatus(root, title) == true)
	{
		string fileName = "Book1.csv";
		ifstream myFile(fileName); // Data file
		ofstream upFile("Book2.csv"); // Update file
		string line;
		size_t pos;
		stringstream ss;
		ss << num;
		string str = ss.str();

		while (getline(myFile, line))
		{
			if ((pos = line.find(title)) != string::npos)
			{
				string dL1 = "\",";
				size_t dLPos1 = line.rfind(dL1, 0);
				line = line.replace((dLPos1 + 2), 1, str);

				upFile << line;
				myFile.close();
				upFile.close();
				// Remove old file
				remove(fileName.c_str());
				rename("Book2.csv", fileName.c_str());
			}
		}
	}
}
template <typename T>
bool LibraryTree<T>::bookStatus(Lnode* node, string key)
{
	if (node != nullptr)
	{
		if (node->data.getTitle() == key)
		{
			return true;
		}
		else if (node->data.getTitle() < key)
			bookStatus(node->right, key);
		else
			bookStatus(node->left, key);
	}
	else
	{
		cout << "Title not found\n";
		return false;
	}
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

template <class T>
int LibraryTree<T>::getWidth()
{
	int height = maxDepth();
	int nodes, largest = 0;
	// Call numAtLevel for each level in the tree
	// and keep track of the largest number of nodes found.
	for (int x = 1; x <= height; x++)
	{
		nodes = numAtLevel(root, x);
		largest = nodes > largest ? nodes : largest;
	}
	// Return the largest number of nodes found at any level.
	return largest;
}
template <class T>
int LibraryTree<T>::numAtLevel(Lnode* nodePtr, int level)
{
	level--;
	// Have we reached the desired level?
	if (level == 0)
	{
		if (nodePtr)	// Is this a node?
			return 1;
		else
			return 0;
	}
	// Have we run out of nodes before reaching
	// the desired level?
	else if (!nodePtr)
	{
		return 0;
	}

	// If we haven't reached the desired level, and we
	// haven't run out of nodes yet, keep going down in
	// the tree. Keep a sum of the number of nodes found
	// at the desired level in both the left and right branches.
	else
	{
		return numAtLevel(nodePtr->left, level) + numAtLevel(nodePtr->right, level);
	}
}

//////////////////////////////
template <typename T>
int LibraryTree<T>::getDepth(Lnode* node)
{
	if (node == nullptr)
		return 0;
	else
	{
		int lDepth = getDepth(node->left);
		int rDepth = getDepth(node->right);

		/* use the larger one */
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
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

//produces balance factor and height of each subtree
template <typename T>
void LibraryTree<T>::balanceCheck(Lnode*& t)
{
	if (t == nullptr)
	{
		cout << "AVL tree is empty" << endl;
		return;
	}
	if (height(t->left) - height(t->right) < ALLOWED_IMBALANCE && (height(t->left) - height(t->right)) >= 0)
	{
		cout << "AVL tree is balanced" << endl;
		cout << "The balance factor is: " << height(t->left) - height(t->right) << endl;
		cout << "The height of left node is: " << height(t->left) << endl;
		cout << "The height of right node is: " << height(t->right) << endl;
		cout << endl;
		return;
	}
	if (height(t->right) - height(t->left) < ALLOWED_IMBALANCE && (height(t->right) - height(t->left)) >= 0)
	{
		cout << "AVL tree is balanced" << endl;
		cout << "The balance factor is: " << height(t->right) - height(t->left) << endl;
		cout << "The height of left node is: " << height(t->left) << endl;
		cout << "The height of right node is: " << height(t->right) << endl;
		cout << endl;
		return;
	}
	if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
	{
		if (height(t->left->left) >= height(t->left->right))
		{
			cout << "AVL tree is imbalanced" << endl;
			cout << "The balance factor is: " << height(t->left) - height(t->right) << endl;
			cout << "The height of left node is: " << height(t->left) << endl;
			cout << "The height of right node is: " << height(t->right) << endl;
			cout << endl;
		}
		else
		{
			cout << "AVL tree is imbalanced" << endl;
			cout << "The balance factor is: " << height(t->right) - height(t->left) << endl;
			cout << "The height of left node is: " << height(t->left) << endl;
			cout << "The height of right node is: " << height(t->right) << endl;
			cout << endl;
		}
	}
	else
	{
		if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
		{
			if (height(t->right->right) >= height(t->right->left))
			{
				cout << "AVL tree is imbalanced" << endl;
				cout << "The balance factor is: " << height(t->right) - height(t->left) << endl;
				cout << "The height of left node is: " << height(t->left) << endl;
				cout << "The height of right node is: " << height(t->right) << endl;
				cout << endl;
			}
			else
			{
				cout << "AVL tree is imbalanced" << endl;
				cout << "The balance factor is: " << height(t->left) - height(t->right) << endl;
				cout << "The height of left node is: " << height(t->left) << endl;
				cout << "The height of right node is: " << height(t->right) << endl;
				cout << endl;
			}
		}
	}
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
			<< "\nChecked In: " << t->data.getBookStatus() << "\n\n";//"\nKey: " << t->data.getTitleKey() << "\n\n";
		inOrder(t->right);
	}
}

void fillTree(LibraryTree<Book>* tree)
{
	string fileName = "Book1.csv";
	ifstream myFile;
	Book book;
	//string key;
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
				// Parse Title Key (first 3 letters)
				//key = word.substr(0, 6);
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

				//book.setTitleKey(key);
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

//void changeBookStatus(LibraryTree<Book>* tree, string title, int check)
//{
//	ifstream myFile(fileName); // Data file
//	ofstream upFile("updateData.csv"); // Update file
//	string line;
//	size_t pos;
//	string dL1 = "\",";
//	if ((*tree).searchSpecific == true)
//	{
//		while (getline(myFile, line))
//		{
//			size_t dLPos1 = line.find(title, 0);
//			for (size_t i = dLPos1 + 4; i < line.size(); ++i) {
//				word = line[i];
//			}
//			istringstream iss(word);
//			iss >> num;
//			checkedIn = num;
//			word = "";
//			num = -1;
//		}
//
//	}
//}

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
	// Get New Entry Key
	//string key = title.substr(0, 6);
	// Update Tree
	Book book;
	//book.setTitleKey(key);
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
