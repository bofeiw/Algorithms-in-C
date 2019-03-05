#include "sort.h"

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*********** insertion sort **********/
void insertionSort(int array[], int n) {
	int sorted, i, curr;
	// loop through 1..n, where element at 0 is 
	// already sorted because it is single
	for (sorted = 1; sorted < n; ++sorted) {
		// record current element to be shifted
		curr = array[sorted];

		// loop through sorted..0 unless
		// a smaller element than current is found
		i = sorted;
		while (i > 0 && array[i - 1] > curr) {
			// right shift element
			array[i] = array[i - 1];
			--i;
		}
		// put the element being shifted at 
		// the correct place
		array[i] = curr;
	}
}

/*********** quick sort **********/

// first part is smaller
// second part is equal
// third part is greater
void partition(int array[], int n, int* firstEqual, int* firstGreater) {
	int pivot = array[0];
	int i;

	*firstEqual = 0;
	*firstGreater = 0;

	// loop through 0..n and process each element
	for (i = 0; i < n; ++i) {
		if (array[i] < pivot) {
			// element is smaller

			// swap the element with first equal
			swap(array + *firstEqual, array + i);

			// swap the first equal with first greater
			swap(array + i, array + *firstGreater);

			++*firstGreater;
			++*firstEqual;
		} else if (array[i] == pivot) {
			// swap the equal element with first greater
			swap(array + *firstGreater, array + i);
			
			++*firstGreater;
		}
	}
}

// three part partition quick sort
void quickSort(int array[], int n) {
	// only sort when there are multiple elements
	// an array with a single element is already sorted
	if (n > 1) {
		// 0..firstEqual-1 is smaller part
		// firstEqual..firstGreater-1 is equal part
		// firstGreater..n is greater part
		int firstEqual;
		int firstGreater;

		// partition to three part
		partition(array, n, &firstEqual, &firstGreater);

		// sort the smaller part
		quickSort(array, firstEqual);

		// sort the greater
		quickSort(array + firstGreater, n - firstGreater);

		// the equal part is already sorted
	}
}

/*********** selection sort **********/

void selectionSort(int array[], int n) {
	int sorted, i, minIndex;
	// loop through 0..n-1, where the last n will
	// be already sorted at the end
	for (sorted = 0; sorted < n - 1; ++sorted) {
		// loop through sorted..n to find the next
		// smallest elements in the unsorted array
		minIndex = sorted;
		for (i = sorted; i < n; ++i) {
			if (array[minIndex] > array[i]) {
				minIndex = i;
			}
		}
		// swap the smallest element to the front
		// of the unsorted array hence the element
		// becomes sorted
		swap(array + minIndex, array + sorted);
	}
}

/*********** bubble sort **********/

void bubbleSort(int array[], int n) {
	int i, j;
	// outer loop, 0..n
	for (i = 0; i < n; ++i) {
		// inner loop, j..n-i
		// n-i..n are sorted, which are bubbled to
		// the right end in order
		for (j = 1; j < n - i; ++j) {
			// out of order, swap to fix
			if (array[j - 1] > array[j]) {
				swap(array + j - 1, array + j);
			}
		}
	}
}