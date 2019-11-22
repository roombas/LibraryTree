// An example for the LibraryIO class

#include<iostream>
#include "LibraryIO.h"
#include <vector>
using namespace std;

string file_path = "C:\\file\\path";
string file_name = "data.csv";

int main() {
	// Create library
	LibraryIO lib(file_path, file_name);

	// Print first entry
	lib.printEntry(1);

	// Print last entry
	lib.printEntry(lib.getFileEntries());

	// Get vectors
	vector<string> keys = lib.getKeys();
	vector<string> CICO = lib.getCICO();
	vector<string> authors = lib.getAuthors();
	vector<string> titles = lib.getTitles();

	// Pick a key
	string key = keys.at(99);

	// Print the entry for that key
	int index = lib.getIndex(key);

	// Print the entry for that key
	lib.printEntry(index);

	return 0;
}
