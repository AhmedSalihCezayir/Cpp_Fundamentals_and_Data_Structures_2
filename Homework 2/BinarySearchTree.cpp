/*
* Title: Binary Search Trees
* Author: Ahmed Salih Cezayir
* ID: 21802918
* Section: 2
* Assignment: 2
* Description: BinarySearchTree Class
*/

#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {
	root = NULL;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& tree) {
	copyTree(root, tree.root);
}

BinarySearchTree::~BinarySearchTree() {
	deleteTree(root);
}


// A method for checking whether the tree is empty or not
bool BinarySearchTree::isEmpty() const {
	return root == NULL;
}

// A method for getting the height of the tree
int BinarySearchTree::getHeight() {
	return getHeightOfTree(root);
}

// A method for getting the amount of nodes
int BinarySearchTree::getNumberOfNodes() {
	return getNumberOfNodesOfTree(root);
}

// A method for adding a new node with the given int value to the tree
// If the item already exists, return false
bool BinarySearchTree::add(const int newEntry) {
	if (contains(newEntry)) {
		return false;
	}
	else {
		addItemToTree(root, newEntry);
	}
}

// A method for deleting an existing item from the tree
// If the item does not exist, return false
bool BinarySearchTree::remove(const int anEntry) {
	if (!contains(anEntry)) {
		return false;
	}
	else {
		removeHelper(root, anEntry);
		return true;
	}
}

// A method for checking wheter the given item is in the tree
bool BinarySearchTree::contains(const int anEntry) {
	return findItem(root, anEntry);
}

// A method for printing the tree in the preorder
void BinarySearchTree::preorderTraverse() {
	preorder(root);
}

// A method for printing the tree in the inorder
void BinarySearchTree::inorderTraverse() {
	inorder(root);
}

// A method for printing the tree in the postorder
void BinarySearchTree::postorderTraverse() {
	postorder(root);
}

// A method for printing the tree level by level.
void BinarySearchTree::levelorderTraverse() {
	levelorder(root);
}

// A method for swapping all the left pointers with the right pointers
void BinarySearchTree::mirror() {
	mirrorHelper(root);
}

// A method for finding the number of nodes that has a value between a and b.
int BinarySearchTree::span(const int a, const int b) {
	return spanHelper(root, a, b);
}

//============================================== HELPER FUNCTIONS ==============================================
void BinarySearchTree::copyTree(BinaryNode*& newTreePtr, BinaryNode* treePtr) {
	if (treePtr != NULL) {
		// Copy the root then repeat this for right and left subtrees
		newTreePtr = new BinaryNode(treePtr->item, NULL, NULL);
		copyTree(newTreePtr->leftChildPtr, treePtr->leftChildPtr);
		copyTree(newTreePtr->rightChildPtr, treePtr->rightChildPtr);
	}
	else {
		newTreePtr = NULL;
	}
}

void BinarySearchTree::deleteTree(BinaryNode*& treePtr) {
	if (treePtr != NULL) {
		// First delete the left and right subtrees. Then delete the root node
		deleteTree(treePtr->leftChildPtr);
		deleteTree(treePtr->rightChildPtr);
		delete treePtr;
		treePtr = NULL;
	}
}

int BinarySearchTree::getHeightOfTree(BinaryNode* treePtr) {
	if (treePtr == NULL) {
		return 0;
	}
	else {
		// Calculate the left and right subtrees height. Then To find the height of the tree, get the max
		// one and add 1 to it(root node)
		return 1 + max(getHeightOfTree(treePtr->leftChildPtr), getHeightOfTree(treePtr->rightChildPtr));
	}
}

int BinarySearchTree::getNumberOfNodesOfTree(BinaryNode* treePtr) {
	if (treePtr == NULL) {
		return 0;
	}
	else {
		// Calculate the number of nodes in the left and right subtrees and add them together.
		// After that, add one to the sum (because of the root node)
		return 1 + getNumberOfNodesOfTree(treePtr->leftChildPtr) + getNumberOfNodesOfTree(treePtr->rightChildPtr);
	}
}

bool BinarySearchTree::addItemToTree(BinaryNode*& treePtr, const int& newItem) {
	if (treePtr == NULL) {
		// If you reach a leaf node, create a new node with the given item and attach it to the leaf node.
		treePtr = new BinaryNode(newItem, NULL, NULL);

		// After adding the node if everything is fine return true, if not return else
		if (treePtr != NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (treePtr->item < newItem) {
		// If the root has smaller value than the newItem, add the new item to the right subtree
		addItemToTree(treePtr->rightChildPtr, newItem);
	}
	else {
		// If the root has bigger value than the newItem, add the new item to the left subtree
		addItemToTree(treePtr->leftChildPtr, newItem);
	}
}

void BinarySearchTree::removeHelper(BinaryNode*& treePtr, const int& anEntry) {
	if (treePtr != NULL) {
		if (anEntry > treePtr->item) {
			// If the root has smaller item, the item is in the right subtree.
			// Run the method for the right subtree
			removeHelper(treePtr->rightChildPtr, anEntry);
		}
		else if (anEntry < treePtr->item) {
			// If the root has bigger item, the item is in the left subtree.
			// Run the method for the left subtree
			removeHelper(treePtr->leftChildPtr, anEntry);
		}
		else {
			// If you find the item, call the removeNodeItem method
			removeNodeItem(treePtr);
		}
	}
}

void BinarySearchTree::removeNodeItem(BinaryNode*& nodePtr) {
	BinaryNode* delPtr;
	int replacement;

	// If you want to delete a leaf node
	if ((nodePtr->leftChildPtr == NULL) && (nodePtr->rightChildPtr == NULL)) {
		delete nodePtr;
		nodePtr = NULL;
	}
	else if (nodePtr->leftChildPtr == NULL) {
		// If you want to delete a node with only rightChild
		delPtr = nodePtr;
		nodePtr = nodePtr->rightChildPtr;
		delPtr->rightChildPtr = NULL;
		delete delPtr;
	}
	else if (nodePtr->rightChildPtr == NULL) {
		// If you want to delete a node with only leftChild
		delPtr = nodePtr;
		nodePtr = nodePtr->leftChildPtr;
		delPtr->leftChildPtr = NULL;
		delete delPtr;
	}
	else {
		// If you want to delete a full node, first find the smallest value bigger than the value we want to delete.
		processLeftMost(nodePtr->rightChildPtr, replacement);
		nodePtr->item = replacement;
	}
}

void BinarySearchTree::processLeftMost(BinaryNode*& nodePtr, int& replacement) {
	if (nodePtr->leftChildPtr != NULL) {
		// Go all the way down to the left child of the right subtree
		processLeftMost(nodePtr->leftChildPtr, replacement);
	}
	else {
		// When you find the node with the wanted item, delete it from the tree.
		replacement = nodePtr->item;
		BinaryNode* delPtr = nodePtr;
		// Parent now points to its child's child.
		nodePtr = nodePtr->rightChildPtr;
		delPtr->rightChildPtr = NULL;
		delete delPtr;
	}
}

bool BinarySearchTree::findItem(BinaryNode* treePtr, const int& anEntry) {
	if (treePtr == NULL) {
		return false;
	}
	else if (treePtr->item == anEntry) {
		return true;
	}
	else if (treePtr->item < anEntry) {
		// If the root is smaller than wanted element, it is in the right subtree.
		// Call the method for right subtree
		return findItem(treePtr->rightChildPtr, anEntry);
	}
	else {
		// If the root is bigger than wanted element, it is in the left subtree.
		// Call the method for left subtree
		return findItem(treePtr->leftChildPtr, anEntry);
	}
}

void BinarySearchTree::preorder(BinaryNode* treePtr) const {
	if (treePtr != NULL) {
		cout << treePtr->item << " ";
		preorder(treePtr->leftChildPtr);
		preorder(treePtr->rightChildPtr);
	}
}

void BinarySearchTree::inorder(BinaryNode* treePtr) const {
	if (treePtr != NULL) {
		inorder(treePtr->leftChildPtr);
		cout << treePtr->item << " ";
		inorder(treePtr->rightChildPtr);
	}
}

void BinarySearchTree::postorder(BinaryNode* treePtr) const {
	if (treePtr != NULL) {
		postorder(treePtr->leftChildPtr);
		postorder(treePtr->rightChildPtr);
		cout << treePtr->item << " ";
	}
}

void BinarySearchTree::levelorder(BinaryNode* treePtr) {
	int height = getHeight();

	// We need to print the items height times.
	for (int i = 1; i <= height; i++) {
		printCurrentLevel(treePtr, i);
	}
}

void BinarySearchTree::printCurrentLevel(BinaryNode* treePtr, const int& i) {
	if (treePtr != NULL) {
		if (i == 1) {
			cout << treePtr->item << " ";
		}
		else if (i > 1) {
			printCurrentLevel(treePtr->leftChildPtr, i - 1);
			printCurrentLevel(treePtr->rightChildPtr, i - 1);
		}
	}
}

void BinarySearchTree::mirrorHelper(BinaryNode* treePtr) {
	if (treePtr != NULL) {
		// First mirror the left subtree, then mirror the right subtree
		mirrorHelper(treePtr->leftChildPtr);
		mirrorHelper(treePtr->rightChildPtr);

		// Then swap the left and right subtrees.
		swap(treePtr->leftChildPtr, treePtr->rightChildPtr);
	}
}

void BinarySearchTree::swap(BinaryNode*& a, BinaryNode*& b) {
	BinaryNode* tmp = a;
	a = b;
	b = tmp;
}

int BinarySearchTree::spanHelper(BinaryNode* treePtr, const int a, const int b) {
	if (treePtr == NULL) {
		return 0;
	}
	else if (treePtr->item <= b && treePtr->item >= a) {
		// If the current root is between a and b, find the right and left subtree's span and add 1.
		return 1 + spanHelper(treePtr->leftChildPtr, a, b) + spanHelper(treePtr->rightChildPtr, a, b);
	}
	else if (treePtr->item <= a) {
		// If the item is smaller than a, call the method for the right subtree
		return spanHelper(treePtr->rightChildPtr, a, b);
	}
	else {
		// If the item is bigger than b, call the method for the left subtree
		return spanHelper(treePtr->leftChildPtr, a, b);
	}
	
}	