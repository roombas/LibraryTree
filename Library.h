#ifndef Library_H
#define Library_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class Book
{
private:
	string title;
	string key;
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
	string getTitleKey()
	{
		return key;
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

template <typename T>
class LibraryTree
{
private:
	static const int ALLOWED_IMBALANCE = 1;
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
};

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
template <typename T>
void LibraryTree<T>::inOrder(Lnode* t) const
{
	if (t != NULL)
	{
		inOrder(t->left);
		cout << "Title: " << t->data.getTitle() << " | Author: " << t->data.getAuthor() << endl;
		inOrder(t->right);
	}
}
template <typename T>
void LibraryTree<T>::printTreeInOrder() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else
		inOrder(root);
}
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
	else if (node->data.getTitle() < nodePtr->data.getTitle())
		insert(nodePtr->left, node);
	else
		insert(nodePtr->right, node);

	balanceCheck(nodePtr);
	balance(nodePtr);
}

#endif