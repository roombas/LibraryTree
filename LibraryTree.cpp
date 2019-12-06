/*
	* Authors:		Barragan, Alejandro
	*				Lu, Stephanie
	*				McClain, Micah
	*
	* Date: Nov 7, 2019
	* Description:
	*
	*
	*
	* For: San Bernardino Valley College - CS 265: Data Structures - Fall 2019
*/
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Library
{
public:
	Library() : root{ nullptr } {}
	~Library() {
		makeEmpty();
	}

	//figure out a function that compares titles within tree to titles needing to //be inserted
	bool contains(string three_letters)
	{

	}

	/////////////////
	//returns true if tree is empty
	bool isEmpty() const { return root == nullptr; }

	/**
	* Copy assignment
	*/
	Library& operator=(const Library& rhs)
	{
		Library copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	/**
	 * Move assignment
	 */
	Library& operator=(Library&& rhs)
	{
		std::swap(root, rhs.root);
		return *this;
	}

	void insert(string && value) { 
		insert(value, root);
	}

private:
	struct Node
	{
		string title;
		//string author;
		string key;
		int isCheckedIn; // checked in = 1, checked out = 0 (use text or csv)
		Node* left;
		Node* right;
		
		//make title + author into 1 variable, string value. Make 2 different trees
	};

	void insert(string && value, Node* & n) { 
		if (n == nullptr) {

		}
		else if (value < n->title) {
			insert(value, n->left);
		}
		else if (value > n->title) {
			insert(value, n->right);
		}
		else {
			// do nothing.
		}
	}

	void fillTree(Library* lib, LibraryIO* data) {
		for (int i = 0; i < ; ++i) {
			string temp = bookInfo(i);
			lib->insert(temp);
		}
	}

	void remove()
	{
		// removes books
	}

	balance()
	{
		//balance function to keep height within 2
	}

};//end of Library class


/*****************************************/
class admin
{
private:
	string username;
	char password;
public:
	admin(/* args */);
	~admin();
};//end of admin class

admin::admin(/* args */)
{
}

admin::~admin()
{
}

int main() {
	int value;
	cout << "1-Admin\n";
	cout << "2-Search for book\n";	
	cout << "3-Exit\n";	

	cin >> value;
	//we should have a menu... so switch. Unless there is something else we can do...
	switch (value)
	{
	case 1:
		/* we can probably create a username and password for one admin...*/
		break;
	case 2:
		/*...*/
		break;
	case 3:
		exit(EXIT_FAILURE);
		break;
	default:
		break;
	}
}
