#ifndef Library_H
#define Library_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

class Book
{
private:
	string title;
	string key;		//first 3 letters for title
	string author;
	int bookStatus;	//= 1 if checked in, = 0 if checked out

public:
	Book() {}
	Book(string t, string a)
	{
		title = t;
		author = a;
	}
	Book(string t, string a, int b)
	{
		title = t;
		author = a;
		bookStatus = b;
	}
	Book(string t, string k, string a, int b)
	{
		title = t;
		key = k;
		author = a;
		bookStatus = b;
	}
	string getTitle()
	{
		return title;
	}
	string getTitleKey()
	{
		return key;
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
	void setTitleKey(string k)
	{
		key = k;
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

//AVL tree class
template <typename T>
class LibraryTree
{
private:
	static const int ALLOWED_IMBALANCE = 1; //for balancing tree
	struct Lnode
	{
		T data;
		Lnode* left;
		Lnode* right;
		int height;

		Lnode(T b, Lnode* lt, Lnode* rt, int h = 0)
			: data{ b }, left{ lt }, right{ rt }, height{ h } {}
	};
	Lnode *root;

public:
	LibraryTree()
	{
		root = nullptr;
	}
	~LibraryTree()
	{
		clearAll();
	}
	int maxDepth()
	{
		return getDepth(root);
	}
	bool isEmpty() const 
	{
		return root == nullptr; 
	}	
	int height(Lnode *t) const
	{
		return t == nullptr ? -1 : t->height;
	}
	int getWidth();
	int numAtLevel(Lnode*, int);
	int getDepth(Lnode*);
	void balance(Lnode*&);
	void balanceCheck(Lnode*&);
	void rotateWithLeftChild(Lnode*&);
	void rotateWithRightChild(Lnode*&);
	void doubleWithLeftChild(Lnode*&);
	void doubleWithRightChild(Lnode*&);
	void inOrder(Lnode*) const;
	void printTreeInOrder() const;
	void insert(Lnode*&, Lnode*&);
	void insertNode(T);

	void remove(Lnode*);
	void removeNode(T);

	void makeEmpty(Lnode*&);
	void clearAll();

	void specificInOrder(Lnode*, string);
	void searchSpecific(string);
	void allInOrder(Lnode*, string);
	void searchAll(string);
};

template <typename T>
void LibraryTree<T>::clearAll()
{
	makeEmpty(root);
}
template <typename T>
void LibraryTree<T>::makeEmpty(Lnode *& node)
{
	if (node != nullptr)
	{
		makeEmpty(node->left);
		makeEmpty(node->right);
		delete node;
	}
	node = nullptr;
}

//insert class object Book
template <typename T>
void LibraryTree<T>::insertNode(T b)
{
	Lnode* node = new Lnode{ b, nullptr, nullptr };
	node->data = b;
	node->left = nullptr;
	node->right = nullptr;
	insert(root, node);
}
template <typename T>
void LibraryTree<T>::insert(Lnode *& nodePtr, Lnode *& node)
{
	if (nodePtr == nullptr)
		nodePtr = node;
	else if (node->data.getTitleKey() < nodePtr->data.getTitleKey())
		insert(nodePtr->left, node);
	else
		insert(nodePtr->right, node);

	//balanceCheck(nodePtr);
	balance(nodePtr);
}

//template <typename T>
//void LibraryTree<T>::removeNode(T x)
//{
//	remove(x, root);
//}
//template <typename T>
//void LibraryTree<T>::remove(Lnode *node)
//{
//	Lnode *tmp;
//
//	if (node == nullptr)
//		return;
//
//	if (x < t->element)
//		remove(x, t->left);
//	else if (t->element < x)
//		remove(x, t->right);
//	else if (t->left != nullptr && t->right != nullptr) // Two children
//	{
//		t->element = findMin(t->right)->element;
//		remove(t->element, t->right);
//	}
//	else
//	{
//		AvlNode *oldNode = t;
//		t = (t->left != nullptr) ? t->left : t->right;
//		delete oldNode;
//	}
//
//	balance(t);
//}

//search function for specific book
template <typename T>
void LibraryTree<T>::searchSpecific(string key)
{
	specificInOrder(root, key);
}

//search function for all matching books
template <typename T>
void LibraryTree<T>::searchAll(string key)
{
	allInOrder(root, key);
}

//traverses tree and prints out the specified result
template <typename T>
void LibraryTree<T>::specificInOrder(Lnode* node, string key)
{
	if (node != nullptr)
	{
		string tmp = node->data.getTitle();
		//finds first result of condition in tree
		if (node->data.getTitle() == key || tmp.find(key) != string::npos)
		{
			cout << "Title: " << node->data.getTitle() << "\nAuthor: "
				<< node->data.getAuthor() << "\nChecked In: "
				<< node->data.getBookStatus() << "\n\n";
			return;
		}
		else if (node->data.getTitle() < key)
			specificInOrder(node->right, key);
		else
			specificInOrder(node->left, key);
	}
	else
		cout << "Title not found\n";
}

//traverses full tree in-order to find and print all books with the specified key word
template <typename T>
void LibraryTree<T>::allInOrder(Lnode* node, string key)
{
	if (node != nullptr)
	{
		allInOrder(node->left, key);
		string tmp = node->data.getTitle();
		if (node->data.getTitle() == key || tmp.find(key) != string::npos)
		{
			cout << "Title: " << node->data.getTitle() << "\nAuthor: "
				<< node->data.getAuthor() << "\nChecked In: "
				<< node->data.getBookStatus() << "\n\n";
		}
		allInOrder(node->right, key);
	}
}

template <class T>
int LibraryTree<T>::getWidth()
{
	int height = maxDepth();
	int nodes, largest = 0;
	// Call numAtLevel for each level in the tree
	// and keep track of the largest number of nodes found.
	for (int x = 1; x <= height; x++)
	{
		nodes = numAtLevel(root, x);
		largest = nodes > largest ? nodes : largest;
	}
	// Return the largest number of nodes found at any level.
	return largest;
}
template <class T>
int LibraryTree<T>::numAtLevel(Lnode *nodePtr, int level)
{
	level--;
	// Have we reached the desired level?
	if (level == 0)
	{
		if (nodePtr)	// Is this a node?
			return 1;
		else
			return 0;
	}
	// Have we run out of nodes before reaching
	// the desired level?
	else if (!nodePtr)
	{
		return 0;
	}

	// If we haven't reached the desired level, and we
	// haven't run out of nodes yet, keep going down in
	// the tree. Keep a sum of the number of nodes found
	// at the desired level in both the left and right branches.
	else
	{
		return numAtLevel(nodePtr->left, level) + numAtLevel(nodePtr->right, level);
	}
}

//////////////////////////////
template <typename T>
int LibraryTree<T>::getDepth(Lnode* node)
{
	if (node == nullptr)
		return 0;
	else
	{
		int lDepth = getDepth(node->left);
		int rDepth = getDepth(node->right);

		/* use the larger one */
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

//function to balance tree
template <typename T>
void LibraryTree<T>::balance(Lnode *& t)
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

//produces balance factor and height of each subtree
template <typename T>
void LibraryTree<T>::balanceCheck(Lnode *& t)
{
	if (t == nullptr)
	{
		cout << "AVL tree is empty" << endl;
		return;
	}
	if (height(t->left) - height(t->right) < ALLOWED_IMBALANCE && (height(t->left) - height(t->right)) >= 0)
	{
		cout << "AVL tree is balanced" << endl;
		cout << "The balance factor is: " << height(t->left) - height(t->right) << endl;
		cout << "The height of left node is: " << height(t->left) << endl;
		cout << "The height of right node is: " << height(t->right) << endl;
		cout << endl;
		return;
	}
	if (height(t->right) - height(t->left) < ALLOWED_IMBALANCE && (height(t->right) - height(t->left)) >= 0)
	{
		cout << "AVL tree is balanced" << endl;
		cout << "The balance factor is: " << height(t->right) - height(t->left) << endl;
		cout << "The height of left node is: " << height(t->left) << endl;
		cout << "The height of right node is: " << height(t->right) << endl;
		cout << endl;
		return;
	}
	if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
	{
		if (height(t->left->left) >= height(t->left->right))
		{
			cout << "AVL tree is imbalanced" << endl;
			cout << "The balance factor is: " << height(t->left) - height(t->right) << endl;
			cout << "The height of left node is: " << height(t->left) << endl;
			cout << "The height of right node is: " << height(t->right) << endl;
			cout << endl;
		}
		else
		{
			cout << "AVL tree is imbalanced" << endl;
			cout << "The balance factor is: " << height(t->right) - height(t->left) << endl;
			cout << "The height of left node is: " << height(t->left) << endl;
			cout << "The height of right node is: " << height(t->right) << endl;
			cout << endl;
		}
	}
	else
	{
		if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
		{
			if (height(t->right->right) >= height(t->right->left))
			{
				cout << "AVL tree is imbalanced" << endl;
				cout << "The balance factor is: " << height(t->right) - height(t->left) << endl;
				cout << "The height of left node is: " << height(t->left) << endl;
				cout << "The height of right node is: " << height(t->right) << endl;
				cout << endl;
			}
			else
			{
				cout << "AVL tree is imbalanced" << endl;
				cout << "The balance factor is: " << height(t->left) - height(t->right) << endl;
				cout << "The height of left node is: " << height(t->left) << endl;
				cout << "The height of right node is: " << height(t->right) << endl;
				cout << endl;
			}
		}
	}
}
template <typename T>
void LibraryTree<T>::rotateWithLeftChild(Lnode *& k2)
{
	Lnode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}
template <typename T>
void LibraryTree<T>::rotateWithRightChild(Lnode *& k1)
{
	Lnode *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	k1 = k2;
}
template <typename T>
void LibraryTree<T>::doubleWithLeftChild(Lnode *& k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}
template <typename T>
void LibraryTree<T>::doubleWithRightChild(Lnode *& k1)
{
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}
//function that prints tree inorder
template <typename T>
void LibraryTree<T>::printTreeInOrder() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else
		inOrder(root);
}
template <typename T>
void LibraryTree<T>::inOrder(Lnode* t) const
{
	if (t != NULL)
	{
		inOrder(t->left);
		cout << "Title: " << t->data.getTitle() << "\nAuthor: " << t->data.getAuthor() 
			<< "\nChecked In: " << t->data.getBookStatus() << "\nKey: " << t->data.getTitleKey() << "\n\n";
		inOrder(t->right);
	}
}

void fillTree(LibraryTree<Book>* tree)
{
	ifstream myFile;
	Book book;
	string key;
	string title;
	string author;
	int checkedIn;
	string line;
	string word = "";
	int num = -1;
	string dL = "\",\"";
	string dL1 = "\",";

	myFile.open("LibraryData2.csv");//("Titles.txt");//
	getline(myFile, line); // Skip header line

	if (!myFile.good())
	{
		cout << "Invalid file\n";
	}
	else {
		getline(myFile, line); // Get 1st line of data
		while (myFile.good() && !myFile.eof())
		{
			if (myFile.good()) {
				size_t dLPos = line.find(dL, 0);
				// Parse Title
				for (size_t i = 3; i < dLPos - 2; ++i) {
					word += line[i];
				}
				// Parse Title Key (first 3 letters)
				key = word.substr(0,3);
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

				book.setTitleKey(key);
				book.setTitle(title);
				book.setAuthor(author);
				book.setBookStatus(checkedIn);
				(*tree).insertNode(book);
				getline(myFile, line); // Get next line of data
			}
		}
	}
	myFile.close();
}

#endif