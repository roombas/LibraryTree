#include <iostream>
#include <string>
#include "BST.h"

int main()
{
	BST<Book> tree;
	fillTree(&tree);
	cout << "Tree depth of: " << tree.maxDepth() << endl;
	cout << "Tree width of: " << tree.getWidth() << endl;

	return 0;
}
