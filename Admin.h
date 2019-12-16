#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include "Library.h"
//#include "SignUp.h"

using namespace std;

LibraryTree<Book> tree; //title sorted tree
LibraryTree<Book> treeA; //author sorted tree
void initializeTree();
void adminOptions();
void viewBooks();
void searchBook();
void checkBook();
void adminCheckin();
void addbook(LibraryTree<Book>*);
void deletebook(LibraryTree<Book>*);

class Admin
{
private:

public:
	string username = "admin";//"Darkling-01";
	string passwd = "password";//"Welcome2CS";
};


void initializeTree()
{
	fillTree(&tree, "Book1.csv");
	fillTreeA(&treeA, "Book1.csv");
}

int options()
{
	int choice;
	cout << "Welcome to the library database!\n\n";
	cout << "	**********USER OPTIONS:**********\n";
	cout << "	1-View all titles\n";
	cout << "	2-Search database\n";
	cout << "	3-See if title is available\n";
	cout << "	4-Log in as administrator\n";
	cout << "	5-Exit\n\n";

	while (!(cin >> choice) || choice > 5 || choice < 1)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("CLS");
		cout << "Welcome to the library database!\n\n";
		cout << "	**********USER OPTIONS**********\n";
		cout << "	1-View all books\n";
		cout << "	2-Search database\n";
		cout << "	3-See if title is available\n";
		cout << "	4-Log in as administrator\n";
		cout << "	5-Exit\n\n";
		cout << "	Please enter valid input.\n";
	}
	return choice;
}

//main function that will hold all other user functions
void setUser() {
	int choice = options();

	//view all titles
	if (choice == 1)
	{
		system("CLS");
		viewBooks();
	}
	//search database
	else if (choice == 2)
	{
		system("CLS");
		searchBook();
	}
	//see if title is available
	else if (choice == 3)
	{
		system("CLS");
		checkBook();
	}
	//log in as admin
	else if (choice == 4)
	{
		system("CLS");

		Admin Admin1;
		string user, paswd;
		cout << "Username: ";
		cin >> user;
		cout << "Password: ";
		cin >> paswd;

		if (user == Admin1.username || paswd == Admin1.passwd) {
			system("CLS");
			adminOptions();
		}
		else {
			cout << "Exiting now...";
			setUser();
		}
	}
	//exit program
	else if (choice == 5)
	{
		return;
	}
}

void adminOptions()
{
	system("CLS");
	int value;
	cout << "	**********ADMIN OPTIONS********** \n";
	cout << "	1-Add Book\n";
	cout << "	2-Remove Book\n";
	cout << "	3-Check in/Check out\n";
	cout << "	4-Log out\n";
	cin >> value;

	switch (value)
	{
	case 1:
		system("CLS");
		addbook(&tree);
	case 2:
		system("CLS");
		deletebook(&tree);
	case 3:
		system("CLS");
		adminCheckin();
	case 4:
		system("CLS");
		setUser();
		break;
	default:
		break;
	}
}

void viewBooks()
{
	char cont;
	bool running = true;
	int choice;
	system("CLS");
	
	cout << "	**********VIEW LIBRARY DATABASE**********\n";
	cout << "	1-Sort by title\n";
	cout << "	2-Sort by author\n";
	cout << "	3-Exit\n";
	cin >> choice;

	if (choice == 1)
	{
		system("CLS");
		while (running) {
			tree.printTree();
			cout << "BACK [y/n]\n";
			while (!(cin >> cont))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("CLS");
				cout << "BACK [y/n]\n";
			}
			system("CLS");
			if (cont == 'y' || cont == 'Y')
				running = false;
			else if (cont == 'n' || cont == 'N')
				running = true;
		}
		viewBooks();
	}
	else if (choice == 2)
	{
		system("CLS");
		while (running) {
			treeA.printTreeA();
			cout << "BACK [y/n]\n";
			while (!(cin >> cont))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("CLS");
				cout << "BACK [y/n]\n";
			}
			system("CLS");
			if (cont == 'y' || cont == 'Y')
				running = false;
			else if (cont == 'n' || cont == 'N')
				running = true;
		}
		viewBooks();
	}
	else if (choice == 3)
	{
		system("CLS");
		setUser();
	}
	else
	{
		cout << "INVALID INPUT.\n";
		system("CLS");
		viewBooks();
	}
}

void searchBook()
{
	int choice;
	char cont;
	bool running = true;

	cout << "	**********SEARCH OPTIONS**********\n";
	cout << "	1-Search for specific book\n";
	cout << "	2-Search for all books containing key word\n";
	cout << "	3-Exit\n";
	cin >> choice;
	if (choice == 1)
	{
		system("CLS");
		while (running) {
			string title;
			cout << "Please enter full title. Search is case sensitive.\n\n";
			cout << "SEARCH: ";
			cin.clear();
			cin.ignore();
			getline(cin, title);
			cout << "\n**************************************\n\n";
			tree.searchSpecific(title);
			cout << "\n**************************************\n";
			cout << "NEW SEARCH [y/n]\n";
			while (!(cin >> cont))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("CLS");
				cout << "NEW SEARCH [y/n]\n";
			}
			system("CLS");
			if (cont == 'y' || cont == 'Y')
				running = true;
			else if (cont == 'n' || cont == 'N')
				running = false;
		}
		searchBook();
	}
	else if (choice == 2)
	{
		system("CLS");
		while (running) {
			string title;
			cout << "Enter partial or full title. Must hold beginning of title (ex: Harry Potter. NOT Potter). Search is case sensitive\n\n";
			cout << "SEARCH: ";
			cin.clear();
			cin.ignore();
			getline(cin, title);
			cout << "\n**************************************\n\n";
			tree.searchAll(title);
			cout << "\n**************************************\n";

			cout << "NEW SEARCH [y/n]\n";
			while (!(cin >> cont))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("CLS");
				cout << "NEW SEARCH [y/n]\n";
			}
			system("CLS");
			if (cont == 'y' || cont == 'Y')
				running = true;
			else if (cont == 'n' || cont == 'N')
				running = false;
		}
		searchBook();
	}
	else if (choice == 3)
	{
		system("CLS");
		setUser();
	}
	else
	{
		cout << "INVALID INPUT.\n";
		system("CLS");
		searchBook();
	}
}

void checkBook()
{
	string title;
	char cont;
	bool running = true;

	while (running) {
		cout << "Please enter partial or full title. Search is case sensitive. Must contain beginning of title.\n\n";
		cout << "SEARCH: ";
		cin.clear();
		cin.ignore();
		getline(cin, title);
		tree.checkStatus(title);

		cout << "NEW SEARCH [y/n]\n";
		while (!(cin >> cont))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			cout << "NEW SEARCH [y/n]\n";
		}
		system("CLS");
		if (cont == 'y' || cont == 'Y')
			running = true;
		else if (cont == 'n' || cont == 'N')
			running = false;
	}
	setUser();
}

void adminCheckin()
{
	string title;
	int num;

	cout << "Title: ";
	cin.clear();
	cin.ignore();
	getline(cin, title);
	cout << "\n************************\n";
	if (!(tree.searchSpecific(title)))
	{
		adminCheckin();
	}
	cout << "\n************************\n";
	cout << "Book Status: ";
	cin >> num;
	tree.changeBookStatus(title, num);

	adminOptions();
}

void addbook(LibraryTree<Book>* tree) {
	cout << "Adding New Book Entry.";
	cin.ignore();
	bool loop = true;
	while (loop) {
		//add title
		string title;
		cout << "\nInsert Title:\t";
		getline(cin, title);
		//author
		string author;
		cout << "Insert Author:\t";
		getline(cin, author);
		// verify
		// TODO: check if title is already in data
		cout << "\nIs this correct? [y/n]: ";
		string ans;
		getline(cin, ans);
		if (!ans.compare("y") || !ans.compare("Y")) {
			insertBook(tree, title, author);
			cout << "New Book Added.\n";
			loop = false;
		}
		else if (ans.compare("n") || ans.compare("N")) {
			cout << "New Entry Cancelled.\n";
			loop = false;
		}
	}
	adminOptions();
}

void deletebook(LibraryTree<Book>* tree) {
	cout << "Deleting Book Entry.";
	cin.ignore();
	bool loop = true;
	while (loop) {
		//add title
		string title;
		cout << "\nInsert Title:\t";
		getline(cin, title);
		// verify
		// TODO: check if title exists in data
		cout << "\nIs this correct? [y/n]: ";
		string ans;
		getline(cin, ans);
		if (!ans.compare("y") || !ans.compare("Y")) {
			removeBook(tree, title);
			cout << "Book Deleted.\n";
			loop = false;
		}
		else if (ans.compare("n") || ans.compare("N")) {
			cout << "Deletion Cancelled.\n";
			loop = false;
		}
	}
	adminOptions();
}

#endif