#include "sorting.h"
#include <iostream>
using namespace std;

/*
* Title: Sorting and Algorithm Efficiency
* Author: Ahmed Salih Cezayir
* ID: 21802918
* Section: 2
* Assignment: 1
* Description: Main method for testing sorting method implementations and their time analysis (Question 2).
*/

int main() {
	int arr1[16] = { 12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8 };
	int arr2[16] = { 12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8 };
	int arr3[16] = { 12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8 };
	int arr4[16] = { 12, 7, 11, 18, 19, 9, 6, 14, 21, 3, 17, 20, 5, 12, 14, 8 };

	int size = 16;

	int compCount1 = 0;
	int compCount2 = 0;
	int compCount3 = 0;

	int moveCount1 = 0;
	int moveCount2 = 0;
	int moveCount3 = 0;

	cout << "SELECTION SORT:" << endl;
	selectionSort(arr1, size, compCount1, moveCount1);
	cout << "compCount: " << compCount1 << "\nmoveCount: " << moveCount1 << endl;
	displayArray(arr1, size);
	cout << endl;

	cout << "MERGE SORT:" << endl;
	mergeSort(arr2, size, compCount2, moveCount2);
	cout << "compCount: " << compCount2 << "\nmoveCount: " << moveCount2 << endl;
	displayArray(arr2, size);
	cout << endl;

	cout << "QUICK SORT:" << endl;
	quickSort(arr3, size, compCount3, moveCount3);
	cout << "compCount: " << compCount3 << "\nmoveCount: " << moveCount3 << endl;
	displayArray(arr3, size);
	cout << endl;

	cout << "RADIX SORT:" << endl;
	radixSort(arr4, size);
	displayArray(arr4, size);
	cout << endl;

	// Performance Analysis
	performanceAnalysis();

	return 0;
}