#include "sorting.h"
#include <time.h>
#include <cmath>
#include <iostream>
using namespace std;

/*
* Title: Sorting and Algorithm Efficiency
* Author: Ahmed Salih Cezayir
* ID: 21802918
* Section: 2
* Assignment: 1
* Description: Implementation of Selection, Merge, Quick and Radix Sort and some helper functions to create various arrays.
*			   There is also a method for analysing performance of these sort algorithms.
*/

void selectionSort(int* arr, const int size, int& compCount, int& moveCount) {
	int border = 0;
	compCount = 0;
	moveCount = 0;

	while (border < size - 1) {
		int minV = arr[border];
		int minI = border;

		for (int i = border + 1; i < size; i++) {
			if (minV > arr[i]) {
				minV = arr[i];
				minI = i;
			}
			compCount++;
		}
		swap(arr[border], arr[minI]);
		moveCount += 3;

		border++;
	}
}

void mergeSort(int* arr, const int size, int& compCount, int& moveCount) {
	if (size > 1) {
		int* left = arr;
		int* right = arr + size/2;

		mergeSort(left, size / 2, compCount, moveCount);
		mergeSort(right, size - (size / 2), compCount, moveCount);

		merge(left, right, arr, size, compCount, moveCount);
	}
}

void merge(int* arr1, int* arr2, int*& arr3 ,const int size, int& compCount, int& moveCount) {
	int* temp = new int[size];
	int i = 0;
	int j = 0;
	int k = 0;

	// Compare the elements of the two parts
	while (i < (size / 2) && j < size - (size / 2)) {
		if (arr1[i] < arr2[j]) {
			temp[k] = arr1[i];
			i++;
		}
		else {
			temp[k] = arr2[j];
			j++;
		}
		k++;
		compCount++;
		moveCount++;
	}

	// If after the comparisons if still there are some elements in the first part, directly add them to the array
	while (i < (size / 2)) {
		temp[k] = arr1[i];
		i++;
		k++;
		moveCount++;
	}

	// If after the comparisons if still there are some elements in the second part, directly add them to the array
	while (j < size - (size / 2)) {
		temp[k] = arr2[j];
		j++;
		k++;
		moveCount++;
	}

	// Copy back the elements from the temp to the original array
	for (int a = 0; a < size; a++) {
		arr3[a] = temp[a];
		moveCount++;
	}

	temp = nullptr;
	delete[] temp;
}

void quickSort(int* arr, const int size, int& compCount, int& moveCount) {
	int pivotIndex;

	if (size > 1) {
		// After this method, the pivot will be at its final sorted position
		partition(arr, size, pivotIndex, compCount, moveCount);

		// Repeat this process for the right and left parts
		quickSort(arr, pivotIndex, compCount, moveCount);
		quickSort(arr + pivotIndex + 1, size - pivotIndex - 1, compCount, moveCount);
	}
}

void partition(int* arr, int size, int& pivotIndex, int& compCount, int& moveCount) {
	int pivot = arr[0];
	int bigArrFirst = 1;

	for (int i = 1; i < size; i++) {
		// Compare the current element with the pivot
		// If it is smaller than pivot swap it with the first element of the bigger-than-pivot array
		if (arr[i] < pivot) {
			swap(arr[i], arr[bigArrFirst]);
			bigArrFirst++;
			moveCount += 3;
		}
		compCount++;
	}
	// Put the pivot to its final position by swapping the pivot with the last element of less-than-pivot array
	swap(arr[0], arr[bigArrFirst - 1]);
	pivotIndex = bigArrFirst - 1;
	moveCount += 3;
}

void radixSort(int* arr, const int size) {
	int index = 0;
	int neg = 0;
	int pos = 0;

	// Create a 2d array for each figure
	int** tempArr = new int* [10];
	for (int i = 0; i < 10; i++) {
		tempArr[i] = new int[size];
	}

	// Create an array for storing the counts of each figure
	int* count = new int[10];
	// Find the maximum digit number. We will loop this amount of time through the array
	int maxDigit = findMaxDigit(arr, size);
	
	// Start looping through the array. Each time we will compare the digit
	for (int i = 0; i < maxDigit; i++) {
		// Clear the count array
		for (int k = 0; k < 10; k++) {
			count[k] = 0;
		}

		for (int k = 0; k < size; k++) {
			// Get the digit of the number
			int digit = (abs(arr[k]) % int(pow(10, i+1)) - abs(arr[k]) % int(pow(10, i))) / pow(10, i);

			// Save it to the tempArr
			tempArr[digit][count[digit]] = arr[k];
			count[digit] += 1;
		}

		// Copy back to the original array after sorting the numbers according to one of their digits 
		for (int k = 0; k < 10; k++) {
			for (int a = 0; a < count[k]; a++) {
				arr[index] = tempArr[k][a];
				index++;
			}
		}

		index = 0;
	}

	// To solve the problem of negative numbers divide the numbers into 2 groups as negatives and positives
	for (int i = 0; i < size; i++) {
		if (arr[i] < 0) {
			tempArr[0][neg] = arr[i];
			neg++;
		}
		else {
			tempArr[1][pos] = arr[i];
			pos++;
		}
	}

	// Copy back the numbers to the original array starting from negative numbers.
	// For negative numbers start from the end of the array. (Because numbers are sorted in terms of their magnitutes)
	// For positive numbers start from the start of the array.
	for (int i = neg - 1, j = 0, k = 0; k < size; k++) {
		if (i >= 0) {
			arr[k] = tempArr[0][i];
			i--;
		}
		else {
			arr[k] = tempArr[1][j];
			j++;
		}
	}

	// Delete the dynamic arrays
	for (int i = 0; i < 10; i++) {
		tempArr[i] = nullptr;
		delete[] tempArr[i];
	}
	tempArr = nullptr;
	delete[] tempArr;

	count = nullptr;
	delete[] count;
}

int findMaxDigit(int* arr, const int size) {
	int maxDigit = 0;

	for (int i = 0; i < size; i++) {
		int current = abs(arr[i]);
		int currentDigit = floor(log10(current) + 1);

		if (currentDigit > maxDigit) {
			maxDigit = currentDigit;
		}
	}
	return maxDigit;
}

void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void displayArray(const int* arr, const int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// Create four identical arrays with random elements
void createRandomArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size) {
	srand(time(0));

	for (int i = 0; i < size; i++) {
		int random = rand();
		arr1[i] = random;
		arr2[i] = random;
		arr3[i] = random;
		arr4[i] = random;
	}
}

// Create four identical arrays with ascending elements
void createAscendingArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size) {
	for (int i = 0; i < size; i++) {
		arr1[i] = i+1;
		arr2[i] = i+1;
		arr3[i] = i+1;
		arr4[i] = i+1;
	}
}

// Create four identical arrays with descending elements
void createDescendingArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size) {
	for (int i = 0; i < size; i++) {
		arr1[i] = size - i;
		arr2[i] = size - i;
		arr3[i] = size - i;
		arr4[i] = size - i;
	}
}

// A method for printing elapsed run time of the four sorting algorithms for three different situations.
// SelectionSort, MergeSort, QuickSort, RadixSort
// Arrays with Descending, Ascending, Random elements
void performanceAnalysis() {
	int sizes[7] = { 6000, 10000, 14000, 18000, 22000, 26000, 30000 };

	cout << "-----------------------------------------------------" << endl;
	cout << "Analysis of Selection Sort" << endl;
	cout << "Array Size\t\tElapsed time\t\tcompCount\t\tmoveCount" << endl;

	cout << "Random Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];
		int compCount = 0;
		int moveCount = 0;

		createRandomArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		selectionSort(arr1, sizes[i], compCount, moveCount);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << "\t\t\t" << compCount << "\t\t" << moveCount << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "\nAscending Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];
		int compCount = 0;
		int moveCount = 0;

		createAscendingArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		selectionSort(arr1, sizes[i], compCount, moveCount);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << "\t\t\t" << compCount << "\t\t" << moveCount << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "\nDexcending Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];
		int compCount = 0;
		int moveCount = 0;

		createDescendingArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		selectionSort(arr1, sizes[i], compCount, moveCount);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << "\t\t\t" << compCount << "\t\t" << moveCount << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "-----------------------------------------------------" << endl;
	cout << "Analysis of Merge Sort" << endl;
	cout << "Array Size\t\tElapsed time\t\tcompCount\t\tmoveCount" << endl;

	cout << "Random Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];
		int compCount = 0;
		int moveCount = 0;

		createRandomArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		mergeSort(arr1, sizes[i], compCount, moveCount);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << "\t\t\t" << compCount << "\t\t\t" << moveCount << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "\nAscending Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];
		int compCount = 0;
		int moveCount = 0;

		createAscendingArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		mergeSort(arr1, sizes[i], compCount, moveCount);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << "\t\t\t" << compCount << "\t\t\t" << moveCount << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "\nDescending Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];
		int compCount = 0;
		int moveCount = 0;

		createDescendingArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		mergeSort(arr1, sizes[i], compCount, moveCount);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << "\t\t\t" << compCount << "\t\t\t" << moveCount << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "-----------------------------------------------------" << endl;
	cout << "Analysis of Quick Sort" << endl;
	cout << "Array Size\t\tElapsed time\t\tcompCount\t\tmoveCount" << endl;

	cout << "Random Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];
		int compCount = 0;
		int moveCount = 0;

		createRandomArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		quickSort(arr1, sizes[i], compCount, moveCount);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << "\t\t\t" << compCount << "\t\t\t" << moveCount << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "\nAscending Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];
		int compCount = 0;
		int moveCount = 0;

		createAscendingArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		quickSort(arr1, sizes[i], compCount, moveCount);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << "\t\t\t" << compCount << "\t\t" << moveCount << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "\nDescending Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];
		int compCount = 0;
		int moveCount = 0;

		createDescendingArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		quickSort(arr1, sizes[i], compCount, moveCount);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << "\t\t\t" << compCount << "\t\t" << moveCount << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "-----------------------------------------------------" << endl;
	cout << "Analysis of Radix Sort" << endl;
	cout << "Array Size\t\tElapsed time"<< endl;

	cout << "Random Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];

		createRandomArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		radixSort(arr1, sizes[i]);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "\nAscending Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];

		createAscendingArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		radixSort(arr1, sizes[i]);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}

	cout << "\nDescending Arrays" << endl;
	for (int i = 0; i < 7; i++) {
		int* arr1 = new int[sizes[i]];
		int* arr2 = new int[sizes[i]];
		int* arr3 = new int[sizes[i]];
		int* arr4 = new int[sizes[i]];

		createDescendingArrays(arr1, arr2, arr3, arr4, sizes[i]);

		clock_t start = clock();
		radixSort(arr1, sizes[i]);
		double duration = 1000 * double(clock() - start) / CLOCKS_PER_SEC;

		cout << sizes[i] << "\t\t\t" << duration << "ms" << endl;

		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] arr4;
	}
}