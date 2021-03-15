#ifndef _SORTING_H
#define	_SORTING_H

/*
* Title: Sorting and Algorithm Efficiency
* Author: Ahmed Salih Cezayir
* ID: 21802918
* Section: 2
* Assignment: 1
* Description: Header file for various sort functions and some helper functions for them.
*/

void selectionSort(int* arr, const int size, int& compCount, int& moveCount);	
void mergeSort(int* arr, const int size, int& compCount, int& moveCount);
void quickSort(int* arr, const int size, int& compCount, int& moveCount);
void radixSort(int* arr, const int size);

void merge(int* arr1, int* arr2, int*& arr3, const int size, int& compCount, int& moveCount);
void partition(int* arr, int size, int& pivotIndex, int& compCount, int& moveCount);
int findMaxDigit(int* arr, const int size);
void swap(int& a, int& b);

void displayArray(const int* arr, const int size);
void createRandomArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size);
void createAscendingArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size);
void createDescendingArrays(int*& arr1, int*& arr2, int*& arr3, int*& arr4, const int size);

void performanceAnalysis();

#endif
