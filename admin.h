#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include "Library.h"

using namespace std;
LibraryTree<Book> tree;

void addbook(LibraryTree<Book>*);
void deletebook(LibraryTree<Book>*);

class Admin
{
private:
   
public:
 string username = "Darkling-01";
 string passwd = "Welcome2CS";


};

void setAdmin(){
    Admin Admin1;
	fillTree(&tree, "LibraryDataTest.csv");

    string user, paswd;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> paswd;

    if(user == Admin1.username || paswd == Admin1.passwd){
        int value;
        cout << "OPTIONS: \n";
        cout << "1-Add Book\n";
	    cout << "2-Delete Book\n";	
	    //cout << "3-Back\n";	
        cin >> value;

        switch (value)
        {
        case 1:
            addbook(&tree);
            break;
        case 2:
            deletebook(&tree);
            break;
       /* case 3:
            main();
            break; */
        default:

            break;
        }
    }else{
        cout << "Exiting now...";
    }
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
}

void deletebook(LibraryTree<Book>* tree){
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
}
#endif
