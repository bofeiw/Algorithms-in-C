#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "sort.h"

/*
run a random test with given sort function, generate a random
array with arraySize elements assert all fails
*/
void testRandom(void (*sort)(int array[], int n), int arraySize);

/*
run a random test with given sort function, generate a sorted
array with arraySize elements assert all fails
*/
void testSorted(void (*sort)(int array[], int n), int arraySize);

/*
run a random test with given sort function, generate a inverse sorted
array with arraySize elements assert all fails
*/
void testSortedInverse(void (*sort)(int array[], int n), int arraySize);

/*
run a random test with given sort function, generate an array whose
elements are all the same, with arraySize elements assert all fails
*/
void testAllSame(void (*sort)(int array[], int n), int arraySize);

/*
return is the array sorted
*/
int isSorted(int array[], int n);

/*
assert the array is sorted
*/
void assertSorted(int array[], int n);

/*
generate a random array with size n
*/
int* randomArray(int n);

/*
generate an array with size n, whose elements are all the same
*/
int* sameArray(int n);

int main(void) {
	testRandom(quickSort, 100);
	testAllSame(quickSort, 100);
	testRandom(insertionSort, 100);
	testAllSame(insertionSort, 100);
	testRandom(selectionSort, 100);
	testAllSame(selectionSort, 100);
	testRandom(bubbleSort, 100);
	testAllSame(bubbleSort, 100);

	printf("All tests passed!\n");
}

int* randomArray(int n) {
	srand((unsigned) time(NULL));

	int* array = malloc(sizeof(int) * n);

	for (int i = 0; i < n; ++i) {
		array[i] = rand();
	}

	return array;
}

int* sameArray(int n) {
	int* array = calloc(sizeof(int) * n, 1);
	return array;
}

int isSorted(int array[], int n) {
	for (int i = 1; i < n; ++i) {
		if (array[i - 1] > array[i]) {
			return 0;
		}
	}
	return 1;
}

void assertSorted(int array[], int n) {
	assert(isSorted(array, n));
}

void testRandom(void (*sort)(int array[], int n), int arraySize) {
	int* array = randomArray(arraySize);
	sort(array, arraySize);
	assertSorted(array, arraySize);
	free(array);
}

void testAllSame(void (*sort)(int array[], int n), int arraySize) {
	int* array = sameArray(arraySize);
	sort(array, arraySize);
	assertSorted(array, arraySize);
	free(array);
}