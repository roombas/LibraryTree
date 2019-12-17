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
#include "Library.h"
#include "Admin.h"
#include <time.h>

LibraryTree<Book> tree; //title sorted tree
LibraryTree<Book> treeA; //author sorted tree
string fileName; // File name for Library Data
clock_t timeStart; // Used for timing functions

void run(string); // Startup code
void init(); // Load/Reload data trees
void uninit(); // Unload data trees
void homePage(); // The home page - user options
void searchPage(); // The search page - user search options
void adminPage(); // The admin page - file manipulation options
void searchBooks(LibraryTree<Book>*, int); // Searches for specified title in the given tree
void adminCheckin(LibraryTree<Book>*); // Check in/out a book
void addBook(LibraryTree<Book>*); // Add a book to Data
void delBook(LibraryTree<Book>*); // Delete a book from Data
void loadBookData(LibraryTree<Book>*, bool); // Fill tree sorted by Title or Author (toggleable)
void updateDataFile(LibraryTree<Book>*); // Updates data csv file
void timerStart(); // Start timer
double timerStop(); // Stop timer

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
	loadBookData(&tree, 0); // Tree sorted by Title (default)
	loadBookData(&treeA, 1); // Tree sorted by Author (search use only)
}

// Unload data trees
void uninit() {
	tree.~LibraryTree();
	treeA.~LibraryTree();
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
			cout << "1 = In Stock\t0 = Out of Stock\n\nSet Book Status: ";
			cin >> num;
			if (num == 0 || num == 1) lib->changeStatus(title, num);
		}
		else {
			cout << "No entry found.\n";
			cout << "**************************************\n";
			cout << "Time taken = " << timerStop() << " ms\n\n";
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
	// Update changes
	updateDataFile(lib);
	uninit();
	init();
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
			cout << "\nNew Book Added.\n";
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
	// Update changes
	updateDataFile(lib);
	uninit();
	init();
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
				lib->removeNode(title);
				cout << "Book Deleted.\n";
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
	// Update changes
	updateDataFile(lib);
	uninit();
	init();
}

// Fill tree sorted by Title or Author (toggleable)
void loadBookData(LibraryTree<Book>* lib, bool toggle)
{
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

			if (!toggle) {
				book.setTitle(title);
				book.setAuthor(author);
			}
			else {
				book.setTitle(author); // Swap author
				book.setAuthor(title); // and title!
			}
			book.setBookStatus(checkedIn);
			(*lib).insertNode(book);
			if (myFile.good()) {
				getline(myFile, line); // Get next line of data
			}
		}
	}
	myFile.close();
}

// Updates the data csv file
void updateDataFile(LibraryTree<Book>* lib) {
	vector<string> title = lib->getTitles();
	vector<string> author = lib->getAuthors();
	vector<int> status = lib->getStatuses();
	int size = title.size();
	ofstream upFile("lib_update.csv"); // New file for update file
	// Print column headers in new file
	upFile << "Title, Author, Checked In\n";
	// Copy contents of lib to new file
	for (int i = 0; i < size; ++i) {
		upFile << "\"\"\"" + title.at(i) + "\"\"\",\"\"\"" + author.at(i) + "\"\"\"," << status.at(i) << "\n";
	}
	// Cleanup
	upFile.close();
	// Remove old file
	remove(fileName.c_str());
	rename("lib_update.csv", fileName.c_str());
}

// Start the Timer
void timerStart() {
	timeStart = clock();
}

// Stop the Timer
double timerStop() {
	return ((int)clock() - (int)timeStart);
}