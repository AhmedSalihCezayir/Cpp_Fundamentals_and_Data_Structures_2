/*
* Title: Binary Search Trees
* Author: Ahmed Salih Cezayir
* ID: 21802918
* Section: 2
* Assignment: 2
* Description: BinaryNode Class (Simple Node with 2 pointer and one data part.)
*/

#include "BinaryNode.h"

BinaryNode::BinaryNode():item(0), leftChildPtr(NULL), rightChildPtr(NULL) {}

BinaryNode::BinaryNode(const NodeItem& nodeItem, 
						BinaryNode* left, 
						BinaryNode* right)
						:item(nodeItem), leftChildPtr(left), rightChildPtr(right) {}