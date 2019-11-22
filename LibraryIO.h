/*	Author: A Micah McClain
	For: CS 265 - Data Structures Fall 2019 - San Bernardino Valley College
	Description:
	File IO for Library Database project. Public functions include:
	- insertEntry(string file_path, string file_name)
	- deleteEntry(int index)
	- printEntry(int index)
	- getIndex(string key)
	- getKeys()
	- getCICO()
	- getAuthors()
	- getTitles()
	- getFilePath()
	- getFileName()
	- getFileEntries()
*/

#pragma once
#ifndef LIBRARYIO_H
#define LIBRARYIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class LibraryIO {
public:
	LibraryIO(std::string fpath, std::string fname) {
		file_path = fpath;
		file_name = fname;
		readFile();
	}
	~LibraryIO() {}

	/* insertEntry
	Adds new key, author, and title data to the end of the file.
	Automatically assumes stock "y".
	*/
	void insertEntry(std::string key, std::string author, std::string title) {
		std::string foldPath = file_path + file_name;
		std::ifstream fold(foldPath); // Get file
		std::string fnewPath = file_path + "data_update.csv";
		std::ofstream fnew(fnewPath); // Update file
		// Copy old file
		std::string line;
		while (fold.good() && !fold.eof()) {
			if (fold.good()) {
				getline(fold, line);
				fnew << line;
			}
			if (fold.good()) {
				fnew << "\n";
			}
		}
		// Write new line
		fnew << "\"\"\"" + key + "\"\"\",\"\"\"y\"\"\",\"\"\"" + author + "\"\"\",\"\"\"" + title + "\"\"\"\n";
		// Close files
		fold.close();
		fnew.close();
		// Remove old file
		std::remove(foldPath.c_str());
		std::rename(fnewPath.c_str(), foldPath.c_str());
		// Increase Library size
		file_entries++;
	}

	/* deleteEntry
	Removes the selected entry from the file.
	Index '1' is the first entry. Index 'FINAL_ENTRY' is the last entry.
	*/
	void deleteEntry(int index) {
		std::string foldPath = file_path + file_name;
		std::ifstream fold(foldPath); // Get file
		std::string fnewPath = file_path + "data_update.csv";
		std::ofstream fnew(fnewPath); // Update file
		if (index > 0 && index <= file_entries) {
			int currentLine = 0;
			// Copy old file
			std::string line;
			while (fold.good() && !fold.eof()) {
				if (fold.good()) {
					getline(fold, line);
				}
				if (fold.good() && currentLine != index) {
					fnew << line;
					fnew << "\n";
				}
				++currentLine;
			}
			// Close files
			fold.close();
			fnew.close();
			// Remove old file
			std::remove(foldPath.c_str());
			std::rename(fnewPath.c_str(), foldPath.c_str());
			// Reduce Library size
			file_entries--;
		}
	}

	/* printEntry
	Prints to console the entry at the index given.
	Index '1' prints the 1st entry. Index 'FINAL_ENTRY' prints the last entry.
	*/
	void printEntry(int index) {
		std::string filePath = file_path + file_name;
		std::ifstream file(filePath); // Get file
		if (index > 0 && index <= file_entries) {
			int currentLine = 0;
			// Copy old file
			std::string line;
			while (file.good() && !file.eof()) {
				if (file.good()) {
					getline(file, line);
				}
				if (file.good() && currentLine == index) {
					std::string dL = "\",\"";
					std::vector<size_t> dLPositions;
					size_t pos = line.find(dL, 0);
					while (pos != std::string::npos) {
						dLPositions.push_back(pos);
						pos = line.find(dL, pos + 1);
					}
					std::string word = "";
					/*
					// Find Key value
					for (size_t i = 3; i < dLPositions.at(0) - 2; ++i) {
						word += line[i];
					}
					word += "\t";
					*/
					// Find InStock value
					for (size_t i = dLPositions.at(0) + 5; i < dLPositions.at(1) - 2; ++i) {
						word += line[i];
					}
					word += "\t\t";
					// Find Author value
					for (size_t i = dLPositions.at(1) + 5; i < dLPositions.at(2) - 2; ++i) {
						word += line[i];
					}
					word += "\t\t";
					// Find Title value
					for (size_t i = dLPositions.at(2) + 5; i < line.size() - 3; ++i) {
						word += line[i];
					}
					word += "\n";
					std::cout << "In Stock: ";
					std::cout << word << std::endl;
				}
				++currentLine;
			}
			// Close files
			file.close();
		}
		else {
			std::cout << "No entry found.\n";
		}
	}

	/* getIndex
		Searches the Key vector for the specified key.
		Returns the data entry with the matching key i.e. 1st entry returns value 1.
	*/
	int getIndex(std::string key) {
		std::vector<std::string>::iterator it = std::find(keys.begin(), keys.end(), key);
		// Search list of keys
		if (it != keys.end()) {
			size_t index = std::distance(keys.begin(), it);
			return static_cast<int>(index) + 1;
		}
		// Inform the user their query was not found
		else {
			return -1;
		}
	}

	std::vector<std::string> getKeys() {
		return keys;
	}

	std::vector<std::string> getCICO() {
		return CICO;
	}

	std::vector<std::string> getAuthors() {
		return authors;
	}

	std::vector<std::string> getTitles() {
		return titles;
	}

	std::string getFilePath() {
		return file_path;
	}

	std::string getFileName() {
		return file_name;
	}

	int getFileEntries() {
		return file_entries;
	}

private:
	std::string file_path;
	std::string file_name;
	std::size_t file_entries;
	std::vector<std::string> authors, titles, keys, CICO;

	/* readFile
	Populates the libData vector. File must be a CSV with columns
	Key, CICO, Author, Title in that order.
	*/
	void readFile() {
		std::ifstream file(file_path + file_name); // Get file
		// Read Data
		std::string line;
		// Skip header line
		std::getline(file, line);
		// Parse the Library Data	
		std::getline(file, line); // Get first line of Data
		while (file.good() && !file.eof()) {
			// Increase Library size
			file_entries++;
			if (file.good()) {
				// Find Delimiters for current line
				std::string dL = "\",\"";
				std::vector<size_t> dLPositions;
				size_t pos = line.find(dL, 0);
				while (pos != std::string::npos) {
					dLPositions.push_back(pos);
					pos = line.find(dL, pos + 1);
				}
				std::string word = "";
				// Find Key value
				for (size_t i = 3; i < dLPositions.at(0) - 2; ++i) {
					word += line[i];
				}
				keys.push_back(word);
				word = "";
				// Find InStock value
				for (size_t i = dLPositions.at(0) + 5; i < dLPositions.at(1) - 2; ++i) {
					word += line[i];
				}
				CICO.push_back(word);
				word = "";
				// Find Author value
				for (size_t i = dLPositions.at(1) + 5; i < dLPositions.at(2) - 2; ++i) {
					word += line[i];
				}
				authors.push_back(word);
				word = "";
				// Find Title value
				for (size_t i = dLPositions.at(2) + 5; i < line.size() - 3; ++i) {
					word += line[i];
				}
				titles.push_back(word);
				// Go to next line of data
				getline(file, line);
			}
		}
		file.close();
	}
};
#endif