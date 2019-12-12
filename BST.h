#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

#ifndef BST_H
#define BST_H

class Book
{
private:
	string title;
	string author;

public:
	Book() {}
	Book(string aTitle, string anAuthor)
	{
		title = aTitle;
		author = anAuthor;
	}

	string getTitle()
	{
		return title;
	}
	string getAuthor()
	{
		return author;
	}
	void setTitle(string aTitle)
	{
		title = aTitle;
	}
	void setAuthor(string anAuthor)
 	{
		author = anAuthor;
	}
};

template <class T>
class BST
{
public:
	struct Lnode
	{
		T data;
		Lnode *left;
		Lnode *right;
		int height;

		Lnode() {}
		Lnode(Book b, Lnode* lt, Lnode* rt, int h = 0)
			: data{ b }, left{ lt }, right{ rt }, height{ h } {}

	};
	Lnode *root;
	int leafcount;

	void insert(Lnode *&, Lnode *&);
	int getWidth();
	int getTreeHeight(Lnode*);
	int treeHeight();
	int numAtLevel(Lnode *, int);

	int maxDepth()
	{
		return getDepth(root);
	}
	int getDepth(Lnode* node)
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

	int height(Lnode *t) const
	{
		return t == nullptr ? -1 : t->height;
	}

	static const int ALLOWED_IMBALANCE = 1;
	void balance(Lnode * & t)
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
	void balanceCheck(Lnode *& t)
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
				cout << "The height of left node is: " << height(t->left)  << endl;
				cout << "The height of right node is: " << height(t->right) << endl;
				cout << endl;
			}
			else
			{
				cout << "AVL tree is imbalanced" << endl;
				cout << "The balance factor is: " << height(t->right) - height(t->left) << endl;
				cout << "The height of left node is: " << height(t->left)  << endl;
				cout << "The height of right node is: " << height(t->right)  << endl;
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
					cout << "The height of left node is: " << height(t->left)  << endl;
					cout << "The height of right node is: " << height(t->right)  << endl;
					cout << endl;
				}
				else
				{
					cout << "AVL tree is imbalanced" << endl;
					cout << "The balance factor is: " << height(t->left) - height(t->right) << endl;
					cout << "The height of left node is: " << height(t->left) << endl;
					cout << "The height of right node is: " << height(t->right)  << endl;
					cout << endl;
				}
			}
		}
	}
	void rotateWithLeftChild(Lnode * & k2)
	{
		Lnode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void rotateWithRightChild(Lnode * & k1)
	{
		Lnode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->right), k1->height) + 1;
		k1 = k2;
	}
	void doubleWithLeftChild(Lnode * & k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	void doubleWithRightChild(Lnode * & k1)
	{
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}

public:
	BST() { root = nullptr; }
	bool isEmpty() const 
	{
		return root == nullptr; 
	}
	void insertNode(T);
	void printOut()
	{
		printOut(root);
	}
};

template <class T>
void BST<T>::insert(Lnode *&nodePtr, Lnode *&newNode)
{
	if (nodePtr == nullptr)
		nodePtr = newNode;
	else if (newNode->data.getTitle() < nodePtr->data.getTitle())
		insert(nodePtr->left, newNode);
	else
		insert(nodePtr->right, newNode);
	
	balanceCheck(nodePtr);
	balance(nodePtr);
	
}

template <class T>
void BST<T>::insertNode(T b)
{
	Lnode* newNode;

	newNode = new Lnode;
	newNode->data = b;
	newNode->left = newNode->right = nullptr;
	insert(root, newNode);
}

template <class T>
int BST<T>::getTreeHeight(Lnode* nodePtr)
{
	int leftHeight, rightHeight;
	if (nodePtr)
	{
		leftHeight = getTreeHeight(nodePtr->left);
		rightHeight = getTreeHeight(nodePtr->right);
		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
	else
	{
		return 0;
	}
}
template <class T>
int BST<T>::numAtLevel(Lnode *nodePtr, int level)
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

template <class T>
int BST<T>::treeHeight()
{
	return getTreeHeight(root);
}

template <class T>
int BST<T>::getWidth()
{
	int height = treeHeight();
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


void fillTree(BST<Book>* t)
{
	Book b;
	ifstream myFile;
	string title;
	string author;
	myFile.open("Titles.txt");//("Data.csv");//
	if (!myFile)
	{
		cout << "Invalid file\n";
	}

	while (!myFile.eof())
	{
		myFile >> title >> author;
		cout << title << " " << author << " \n";
		b.setTitle(title);
		b.setAuthor(author);

		(*t).insertNode(b);
	}
	myFile.close();
}
#endif
