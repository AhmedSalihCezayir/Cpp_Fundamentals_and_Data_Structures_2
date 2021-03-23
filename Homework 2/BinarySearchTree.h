#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "BinaryNode.h"
/*
* Title: Binary Search Trees
* Author: Ahmed Salih Cezayir
* ID: 21802918
* Section: 2
* Assignment: 2
* Description: BinarySearchTree Class Header File
*/

#include <iostream>
using namespace std;

class BinarySearchTree {
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& tree);
	~BinarySearchTree();
	
	bool isEmpty() const;

	int getHeight();
	int getNumberOfNodes();
	bool add(const int newEntry);
	bool remove(const int anEntry);
	bool contains(const int anEntry);

	void preorderTraverse();
	void inorderTraverse();
	void postorderTraverse();
	void levelorderTraverse();

	int span(const int a, const int b);
	void mirror();

	// Helper functions
	void copyTree(BinaryNode*& newTreePtr, BinaryNode* treePtr);
	void deleteTree(BinaryNode*& root);

	int getHeightOfTree(BinaryNode* treePtr);
	int getNumberOfNodesOfTree(BinaryNode* treePtr);

	bool addItemToTree(BinaryNode*& treePtr, const int& newItem);

	void removeHelper(BinaryNode*& treePtr, const int& anEntry);
	void removeNodeItem(BinaryNode*& treePtr);
	void processLeftMost(BinaryNode*& nodePtr, int& replacement);

	bool findItem(BinaryNode* treePtr, const int& anEntry);

	void preorder(BinaryNode* treePtr) const;
	void inorder(BinaryNode* treePtr) const;
	void postorder(BinaryNode* treePtr) const;
	void levelorder(BinaryNode* treePtr);
	void printCurrentLevel(BinaryNode* treePtr, const int& i);

	void mirrorHelper(BinaryNode* treePtr);
	void swap(BinaryNode*& a, BinaryNode*& b);

	int spanHelper(BinaryNode* treePtr, const int a, const int b);

private:
	BinaryNode* root;
};

#endif // !BINARYSEARCHTREE_H
