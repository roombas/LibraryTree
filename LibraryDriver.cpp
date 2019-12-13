#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "Library.h"

int main()
{
	LibraryTree<Book> tree;
	fillTree(&tree);
	tree.printTreeInOrder();
	cout << "Tree depth of: " << tree.maxDepth() << endl;
	cout << "Tree width of: " << tree.getWidth() << endl;

	return 0;
}
