/*
* Title: Binary Search Trees
* Author: Ahmed Salih Cezayir
* ID: 21802918
* Section: 2
* Assignment: 2
* Description: BinaryNode Class (Simple Node with 2 pointer and one data part.)
*/

#ifndef BINARYNODE_H
#define BINARYNODE_H
#include <iostream>
using namespace std;

typedef int NodeItem;

class BinaryNode {
private:
	BinaryNode();
	BinaryNode(const NodeItem& item, BinaryNode* left = NULL, BinaryNode* right = NULL);

	NodeItem item;
	BinaryNode* leftChildPtr;
	BinaryNode* rightChildPtr;

	friend class BinarySearchTree;
};


#endif 

