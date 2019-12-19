/**********************************************************************************************
	Library.cpp
	
	Authors:	Stephanie Lu
				Micah McClain
				Alejandro Barragan

	Date:		Dec 19, 2019

	Description: https://github.com/roombas/LibraryTree
	For: San Bernardino Valley College - CS 265: Data Structures - Fall 2019
/**********************************************************************************************/

#include <iostream>
#include <string>
#include <time.h>
#include "Library.h"
#include "Admin.h"

string fileName = "LibraryData.csv"; // File name for Library Data
LibraryTree<Book> tree; //title sorted tree
LibraryTree<Book> treeA; //author sorted tree
clock_t timeStart; // Used for timing functions

void run(string); // Startup code
void init(); // Load/Reload data trees
void uninit(); // Unload data trees
void updateData(); // Updates the data in the file, then reloads the trees
void homePage(); // The home page - user options
void searchPage(); // The search page - user search options
void adminPage(); // The admin page - file manipulation options
void searchBooks(LibraryTree<Book>*, int); // Searches for specified title in the given tree
void adminCheckin(LibraryTree<Book>*); // Check in/out a book
void addBook(LibraryTree<Book>*); // Add a book to Data
void delBook(LibraryTree<Book>*); // Delete a book from Data
void timerStart(); // Start timer
int timerStop(); // Stop timer and return the change in time in nanoseconds

/******************************MAIN FUNCTION***********************************/
int main()
{
	run("LibraryData.csv");
	return 0;
}
/******************************************************************************/

 // Startup code
void run(string file) {
	fileName = file;
	init();
	homePage();
	uninit();
}

// Load/Reload data trees
void init() {
	tree.clearAll();
	treeA.clearAll();
	tree.loadFromCSV(fileName, 0); // Sorted by Title
	treeA.loadFromCSV(fileName, 1); // Sorted by Author
}

// Unload data trees
void uninit() {
	tree.~LibraryTree();
	treeA.~LibraryTree();
}

// Updates the data in the file, then reloads the trees
void updateData() {
	if(tree.saveToCSV(fileName)) init();// Save current tree to file and reinitialize
}

//main function that will hold all other user functions
void homePage() {
	int choice = 0;
	bool invalid = false;
	while (choice != 3) {
		system("CLS");
		cout << "Welcome to the library database!\n\n";
		cout << "	**********USER OPTIONS**********\n";
		cout << "	1-Search database\n";
		cout << "	2-Log in as Administrator\n";
		cout << "	3-Exit\n\n";
		if (invalid)	cout << "Please enter valid input.\n";
		invalid = false;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1: // Search database
			searchPage();
			break;
		case 2: // Log in as Administrator
			adminPage();
			break;
		case 3: // Exit
			uninit();
			system("CLS");
			cout << "You have exited the program.\n\nGoodbye.\n\n";
			break;
		default:
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			invalid = true;
			break;
		}
	}
}

// File manipulation ptions available to the admin
void adminPage()
{
	// admin login
	system("CLS");
	cout << "Please sign in to continue.\n\n";
	Admin Admin1;
	string user, paswd;
	cin.ignore();
	cout << "Username: ";
	cin >> user;
	cin.ignore();
	cout << "Password: ";
	cin >> paswd;

	if (Admin1.checkUser(user) && Admin1.checkPass(paswd)) {
		int choice = 0;
		bool invalid = false;
		while (choice != 4) {
			system("CLS");
			cout << "Welcome, " + user + "\n\n";
			cout << "	**********ADMIN OPTIONS********** \n";
			cout << "	1-Add Book\n";
			cout << "	2-Delete Book\n";
			cout << "	3-Check in/Check out\n";
			cout << "	4-Log out\n\n";
			if (invalid)	cout << "Please enter valid input.\n";
			invalid = false;
			cout << "Your choice: ";
			cin >> choice;
			switch (choice)
			{
			case 1: // Add a Book
				addBook(&tree);
				break;
			case 2: // Remove a Book
				delBook(&tree);
				break;
			case 3: // Check in/Check out by Title
				adminCheckin(&tree);
				break;
			case 4: // Log out (exit)
				break;
			default:
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				invalid = true;
				break;
			}
		}
	}
}

// Search the database
void searchPage()
{
	int choice = 0;
	bool invalid = false;
	while (choice != 3) {
		system("CLS");
		cout << "Welcome, Guest.\n\n";
		cout << "	**********SEARCH OPTIONS**********\n";
		cout << "	1-Search by title\n";
		cout << "	2-Search by author\n";
		cout << "	3-Exit\n\n";
		if (invalid)	cout << "Please enter valid input.\n";
		invalid = false;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1: // Search by title
			searchBooks(&tree, 0);
			break;
		case 2: // Search by Author
			searchBooks(&treeA, 1);
			break;
		case 3: // Exit
			break;
		default:
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			invalid = true;
			break;
		}
	}
}

// Function to find books in the database
void searchBooks(LibraryTree<Book>* lib, int A) {
	char cont;
	bool running = true;
	system("CLS");
	while (running) {
		string key;
		(A) ? cout << "Searching by Author.\n\nEnter Author: " :
			cout << "Searching by Title.\n\nEnter Title: ";
		cin.clear();
		cin.ignore();
		getline(cin, key);
		timerStart();
		cout << "\n**************************************\n";
		lib->searchAll(key, A);
		// If it finds nothing, print this
		if (!lib->sAFlag) cout << "No entry found.\n";
		else lib->sAFlag = false; // Reset flag for next search
		cout << "**************************************\n";
		cout << "Time taken = " << timerStop() << " ms\n\n";

		cout << "New Search? [y/n]\n";
		while (!(cin >> cont))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			cout << "New Search? [y/n]\n";
		}
		system("CLS");
		if (cont == 'y' || cont == 'Y')
			running = true;
		else if (cont == 'n' || cont == 'N')
			running = false;
	}
}

// Change the value of Book's Status (0 or 1)
void adminCheckin(LibraryTree<Book>* lib) {
	char cont;
	int num;
	bool running = true;
	system("CLS");
	while (running) {
		string title;
		cout << "Change the status of a book.\n\nEnter Title: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, title);
		timerStart();
		cout << "\n**************************************\n";
		// Try to find the book
		if (lib->contains(title))
		{
			// Change the status if the book was found
			lib->printBook(title);
			cout << "**************************************\n";
			cout << "Time taken = " << timerStop() << " ms\n\n";
			cout << "1 = In Stock\t0 = Out of Stock\nSet Book Status: ";
			cin >> num;
			timerStart();
			if (num == 0 || num == 1) {
				lib->changeStatus(title, num);
				// Update file to reflect changes in tree
				updateData();
				cout << "\nBook is now: ";
				(num) ? cout << "In Stock." : cout << "Out of Stock.";
			}
			else {
				cout << "Invalid status selected.";
			}
			cout << " Time taken = " << timerStop() << " ms\n";
		}
		else {
			cout << "No entry found.\n";
			cout << "**************************************\n";
			cout << "Time taken = " << timerStop() << " ms\n";
		}
		cout << "\nNew Search? [y/n]\n";
		while (!(cin >> cont))
		{
			system("CLS");
			cout << "New Search? [y/n]\n";
		}
		system("CLS");
		if (cont == 'y' || cont == 'Y')
			running = true;
		else if (cont == 'n' || cont == 'N')
			running = false;
	}
}

// Adds book to database
void addBook(LibraryTree<Book>* lib) {
	bool loop = true;
	while (loop) {
		//add title
		string title;
		system("CLS");
		cout << "Adding New Book Entry.\n\n";
		cout << "Insert Title:\t";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, title);
		//author
		string author;
		cout << "Insert Author:\t";
		getline(cin, author);
		// verify
		cout << "\nAdd this entry? [y/n]: ";
		string ans;
		getline(cin, ans);
		if (!ans.compare("y") || !ans.compare("Y")) {
			timerStart();
			Book book;
			book.setTitle(title);
			book.setAuthor(author);
			book.setBookStatus(1);
			(*lib).insertNode(book);
			// Update file to reflect changes in tree
			updateData();
			cout << "\nNew Book Added. ";
			cout << "Time taken = " << timerStop() << " ms\n\n";
		}
		else if (ans.compare("n") || ans.compare("N")) {
			cout << "\nNew Entry Cancelled.\n\n";
		}
		char cont;
		cout << "Add another book? [y/n]\n";
		while (!(cin >> cont))
		{
			system("CLS");
			cout << "Add another book? [y/n]\n";
		}
		system("CLS");
		if (cont == 'y' || cont == 'Y')
			loop = true;
		else if (cont == 'n' || cont == 'N')
			loop = false;
	}
}

// Deletes book from database
void delBook(LibraryTree<Book>* lib) {
	bool loop = true;
	while (loop) {
		//add title
		string title;
		system("CLS");
		cout << "Deleting Book Entry.\n\n";
		cout << "Insert Title:\t";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, title);
		timerStart();
		// verify
		cout << "\n**************************************\n";
		if (lib->contains(title)) {
			lib->printBook(title);
			cout << "**************************************\n";
			cout << "Time taken = " << timerStop() << " ms\n";
			cout << "\nDelete this entry? [y/n]: ";
			string ans;
			getline(cin, ans);
			if (!ans.compare("y") || !ans.compare("Y")) {
				timerStart();
				lib->removeNode(title);
				// Update file to reflect changes in tree
				updateData();
				cout << "Book Deleted. ";
				cout << "Time taken = " << timerStop() << " ms\n";
				loop = false;
			}
			else if (ans.compare("n") || ans.compare("N")) {
				cout << "Deletion Cancelled.\n";
				loop = false;
			}
		}
		else {
			cout << "No entry found.\n";
			cout << "**************************************\n";
			cout << "Time taken = " << timerStop() << " ms\n";
		}
		char cont;
		cout << "\nDelete another book? [y/n]\n";
		while (!(cin >> cont))
		{
			system("CLS");
			cout << "Delete another book? [y/n]\n";
		}
		system("CLS");
		if (cont == 'y' || cont == 'Y')
			loop = true;
		else if (cont == 'n' || cont == 'N')
			loop = false;
	}
}

// Start the Timer
void timerStart() {
	timeStart = clock();
}

// Stop the Timer and return the difference
int timerStop() {
	return ((int)clock() - (int)timeStart);
}
