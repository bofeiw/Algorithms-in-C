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
run a test with given sort function, with given array
*/
void testWithArray(void (*sort)(int array[], int n), int arraySize, int array[]);

/*
return is the array sorted
*/
int isSorted(int array[], int n);

/*
assert the array is sorted
*/
void assertSorted(int array[], int n);

/*
test a sort function
*/
void testSort(void (*sort)(int array[], int n), char* name);

/*
generate a random array with size n
*/
int* randomArray(int n);

/*
generate an array with size n, whose elements are all the same
*/
int* sameArray(int n);

/*
generate an array with size n, whose elements are sorted
*/
int* sortedArray(int n);

/*
generate an array with size n, whose elements inverse sorted
*/
int* sortedInverseArray(int n);

int main(void) {
	printf("Start testing...\n");

	testSort(quickSort, "quickSort");
	testSort(insertionSort, "insertionSort");
	testSort(selectionSort, "selectionSort");
	testSort(bubbleSort, "bubbleSort");
	testSort(mergeSort, "mergeSort");
	testSort(heapSort, "heapSort");
	testSort(introSort, "introSort");
	testSort(timSort, "timSort");

	printf("All tests passed!\n");
}

void testSort(void (*sort)(int array[], int n), char* name) {
	printf("testing %s...\n", name);

	// run random tests on sort
	printf("\ttestRandom on %s\n", name);
	testRandom(sort, 1000);

	// run all same tests on sort
	printf("\testAllSame on %s\n", name);
	testAllSame(sort, 1000);

	// run sorted tests on sort
	printf("\testSorted on %s\n", name);
	testSorted(sort, 1000);

	// run inverse sorted tests on sort
	printf("\testSortedInverse on %s\n", name);
	testSortedInverse(sort, 1000);

	printf("\t%s passed!\n", name);
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

// comparison for sorted
int cmp(const void * a, const void * b) {
   return *(int*)a - *(int*)b;
}

int* sortedArray(int n) {
	int* array = randomArray(n);
	qsort(array, n, sizeof(int), cmp);
	return array;
}

// comparison for inverse sorted
int cmpInverse(const void * a, const void * b) {
   return *(int*)b - *(int*)a;
}

int* sortedInverseArray(int n) {
	int* array = randomArray(n);
	qsort(array, n, sizeof(int), cmpInverse);
	return array;
}

void assertSorted(int array[], int n) {
	assert(isSorted(array, n));
}

void testRandom(void (*sort)(int array[], int n), int arraySize) {
	int* array = randomArray(arraySize);
	testWithArray(sort, arraySize, array);
	free(array);
}

void testAllSame(void (*sort)(int array[], int n), int arraySize) {
	int* array = sameArray(arraySize);
	testWithArray(sort, arraySize, array);
	free(array);
}

void testSorted(void (*sort)(int array[], int n), int arraySize) {
	int* array = sortedArray(arraySize);
	testWithArray(sort, arraySize, array);
	free(array);
}

void testSortedInverse(void (*sort)(int array[], int n), int arraySize) {
	int* array = sortedInverseArray(arraySize);
	testWithArray(sort, arraySize, array);
	free(array);
}

void testWithArray(void (*sort)(int array[], int n), int arraySize, int array[]) {
	sort(array, arraySize);
	assertSorted(array, arraySize);
}