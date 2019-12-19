/**********************************************************************************************
	Library.h

	Authors:	Stephanie Lu
				Micah McClain
				Alejandro Barragan

	Date:		Dec 19, 2019

	Description: https://github.com/roombas/LibraryTree
	For: San Bernardino Valley College - CS 265: Data Structures - Fall 2019
/**********************************************************************************************/

#pragma once
#ifndef Library_H
#define Library_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

/***************************LIBRARYTREE PUBLIC CLASS OPERATIONS********************************
	bool isEmpty()							-->	Returns True if the tree is empty.
	void changeStatus(string, int)			--> Changes book status of file and tree (0 or 1)
	void printTree(bool)					--> Prints tree inorder. Can toggle between Title
												and Author sort.
	void printBook(string)					--> Prints the contents of a Book based on Title.
	bool contains(string)					--> Returns True if Title is in the tree.
	void searchAll(string, bool)			--> Searches for all instances of a substring.
												Can toggle between Title and Author search.
	void clearAll()							--> Clears tree.
	bool saveToCSV()						--> Saves tree data to a specified CSV file and
												returns True if successful.
	void loadFromCSV()						--> Loads tree data from a specified CSV file.
/**********************************************************************************************/

class Book
{
private:
	string title;
	string author;
	int bookStatus;	//= 1 if checked in, = 0 if checked out

public:
	Book() {}
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

template <typename T>
class LibraryTree {
public:
	// Constructor
	LibraryTree() {
		root = nullptr;
	}

	// Deconstructor
	~LibraryTree() {
		clearAll();
	}

	//class functions
	bool isEmpty() const {
		return root == nullptr;
	}

	// Change checked in/out. 1 = checked in, 0 = checked out
	void changeStatus(string key, int num)
	{
		Lnode* node = searchNode(root, key);
		if (node != nullptr)
		{
			node->data.setBookStatus(num);
		}
		else
			cout << "Title not found.\n";
	}

	// Print the contents of the tree
	void printTree(bool toggle) const {
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printTree(root, toggle);
	}

	// Print contents of a book
	void printBook(string key) const {
		if (!contains(key)) {
			cout << "Title not found.\n";
		}
		else {
			printBook(root, key);
		}
	}

	// Search for exact Title
	bool contains(string key) const {
		return contains(root, key);
	}

	// Search for substrings in Title/Author
	void searchAll(string key, bool toggle) {
		searchAll(root, key, toggle);
	}

	// Inserts a new node of type Book
	template <typename T>
	void insertNode(T b) {
		Lnode* node = new Lnode{ b, nullptr, nullptr };
		node->data = b;
		node->left = nullptr;
		node->right = nullptr;
		insertNode(root, node);
	}

	// Deletes a node based on Title
	void removeNode(string key) {
		removeNode(root, key);
	}

	//clears out tree and memory
	void clearAll() {
		clearAll(root); // Empty all nodes
	}

	// Updates the data csv file
	bool saveToCSV(string fileName) {
		// Temporary file for update
		ofstream upFile("lib_update.csv");
		// Print column headers in new file
		upFile << "Title, Author, Checked In\n";
		// Fill current data
		fillUpdateFile(root, upFile);
		// Cleanup
		upFile.close();
		// Remove old file
		remove(fileName.c_str());
		return rename("lib_update.csv", fileName.c_str());
	}

	// Fill tree sorted by Title or Author (toggleable)
	void loadFromCSV(string loadFile, bool toggle)
	{
		ifstream myFile;
		Book book;
		string line;
		string word = "";
		int num = -1;
		// Delimiters
		string dL = "\",\"";
		string dL1 = "\",";
		// Open file
		myFile.open(loadFile);
		getline(myFile, line); // Skip header line

		if (!myFile.good())
		{
			cout << "Invalid file\n";
		}
		else {
			getline(myFile, line); // Get 1st line of data
			while (myFile.good() && !myFile.eof())
			{
				size_t dLPos = line.find(dL, 0);
				// Parse Title if toggle = 1, Author if toggle = 0
				for (size_t i = 3; i < dLPos - 2; ++i) {
					word += line[i];
				}
				(toggle) ? book.setAuthor(word) : book.setTitle(word);
				word = "";
				// Parse Author if toggle = 1, Author if toggle = 0
				for (size_t i = dLPos + 5; i < line.size() - 5; ++i) {
					word += line[i];
				}
				(toggle) ? book.setTitle(word) : book.setAuthor(word);
				word = "";
				size_t dLPos1 = line.rfind(dL1, 0);
				// Parse Checked in or out (integer)
				for (size_t i = dLPos1 + 4; i < line.size(); ++i) {
					word = line[i];
				}
				istringstream iss(word);
				iss >> num;
				book.setBookStatus(num);
				word = "";
				num = -1;
				// Insert new book into tree
				insertNode(book);
				if (myFile.good()) {
					getline(myFile, line); // Get next line of data if next line exists
				}
			}
		}
		myFile.close();
	}

	bool sAFlag = false; // Prevents searchAll from returning repeatedly

private:
	static const int ALLOWED_IMBALANCE = 1; //for balancing tree
	// Node definition
	struct Lnode
	{
		T data;
		Lnode* left;
		Lnode* right;
		int height;

		Lnode(T b, Lnode* lt, Lnode* rt, int h = 0)
			: data{ b }, left{ lt }, right{ rt }, height{ h } {}
	};
	// Class variables
	Lnode* root;
	string fileName = "";

	// Finds height of the tree
	int height(Lnode* t) const
	{
		if (t == nullptr)
			return -1;
		else
			return t->height;
	}

	// Find the leftmost node
	Lnode* findMin(Lnode* t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}

	// Print contents of tree
	void printTree(Lnode* node, bool toggle) const {
		if (node != NULL)
		{
			printTree(node->left, toggle);
			printNode(node, toggle);
			printTree(node->right, toggle);
		}
	}

	// Print contents of a book
	void printBook(Lnode* node, string key) const {
		if (node != nullptr) {
			string title = node->data.getTitle();
			if (key == title) {
				printNode(node, 0);
			}
			else if (key < title) {
				printBook(node->left, key);
			}
			else if (key > title) {
				printBook(node->right, key);
			}
		}
	}

	// Print contents of a single node
	void printNode(Lnode* node, bool toggle) const {
		string t = node->data.getTitle();
		string a = node->data.getAuthor();
		int bs = node->data.getBookStatus();
		// If sorted by Author
		if (toggle) {
			cout << "Title:\t" << a << "\nAuthor:\t" << t << "\n";
		}
		// If sorted by Title
		else {
			cout << "Title:\t" << t << "\nAuthor:\t" << a << "\n";
		}
		(bs == 1) ? cout << "In Stock\n" : cout << "Out of Stock\n";
		cout << "\n";
	}

	// Search for exact Title in tree
	bool contains(Lnode* node, string key) const {
		if (node == nullptr) return false;
		else {
			string title = node->data.getTitle();
			if (key == title) {
				return true;
			}
			else if (key < title) {
				return contains(node->left, key);
			}
			else if (key > title) {
				return contains(node->right, key);
			}
		}
	}

	// Search for substrings in Title / Author
	void searchAll(Lnode*& node, string key, bool toggle)
	{
		// toggle = 0 -> sort by Title
		// toggle = 1 -> sort by Author
		// Key -> tolower
		string keyT;
		keyT.resize(key.size());
		transform(key.begin(), key.end(), keyT.begin(), ::tolower);
		if (node != nullptr)
		{
			searchAll(node->left, key, toggle);
			// Data -> tolower
			string tmp = node->data.getTitle();
			string tmpT;
			tmpT.resize(tmp.size());
			transform(tmp.begin(), tmp.end(), tmpT.begin(), ::tolower);
			// Find Key in Data
			if (tmpT == keyT || tmpT.find(keyT) != string::npos)
			{
				printNode(node, toggle);
				sAFlag = true;
			}
			searchAll(node->right, key, toggle);
		}
	}

	// Search for a node containing substring
	Lnode* searchNode(Lnode*& node, string key)
	{
		if (node != nullptr)
		{
			if (node->data.getTitle() == key || (node->data.getTitle()).find(key) != string::npos)
			{
				return node;
			}
			else if (node->data.getTitle() < key)
				return searchNode(node->right, key);
			else
				return searchNode(node->left, key);
		}
		else
		{
			return nullptr;
		}
	}

	// Inserts a new node of type Book
	void insertNode(Lnode*& nodePtr, Lnode*& node)
	{
		if (nodePtr == nullptr)
			nodePtr = node;
		else if (node->data.getTitle() < nodePtr->data.getTitle())
			insertNode(nodePtr->left, node);
		else
			insertNode(nodePtr->right, node);

		balance(nodePtr);
	}

	// Deletes a node based on Title
	void removeNode(Lnode*& node, string key) {
		if (node == nullptr)
			return;   // Item not found; do nothing
		if (key < node->data.getTitle())
			removeNode(node->left, key);
		else if (node->data.getTitle() < key)
			removeNode(node->right, key);
		else if (node->left != nullptr && node->right != nullptr) // Two children
		{
			node->data.getTitle() = findMin(node->right)->data.getTitle();
			removeNode(node->right, node->data.getTitle());
		}
		else {
			Lnode* oldNode = node;
			node = (node->left != nullptr) ? node->left : node->right;
			delete oldNode;
		}
		balance(node);
	}

	//clears out tree and memory
	void clearAll(Lnode*& node)
	{
		if (node != nullptr)
		{
			clearAll(node->left);
			clearAll(node->right);
			delete node;
		}
		node = nullptr;
	}

	// Node Manipulation Operations
	void balance(Lnode*& t)
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
	void rotateWithLeftChild(Lnode*& k2)
	{
		Lnode* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void rotateWithRightChild(Lnode*& k1)
	{
		Lnode* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->right), k1->height) + 1;
		k1 = k2;
	}
	void doubleWithLeftChild(Lnode*& k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	void doubleWithRightChild(Lnode*& k1)
	{
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}

	// Fills the update file with data
	void fillUpdateFile(Lnode* node, ofstream& upFile) {
		if (node != NULL)
		{
			fillUpdateFile(node->left, upFile);
			upFile << "\"\"\"" + node->data.getTitle()
				+ "\"\"\",\"\"\"" + node->data.getAuthor()
				+ "\"\"\"," << node->data.getBookStatus() << "\n";
			fillUpdateFile(node->right, upFile);
		}
	}
};

#endif
