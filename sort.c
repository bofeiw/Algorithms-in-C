#include "sort.h"

// swap a and b
// essential to most sorting algorithms
// if this is incorrect, most algo will behave very strange
// this swap algorithm is done by xor, for more details, visit:
// https://en.wikipedia.org/wiki/XOR_swap_algorithm
void swap(int* x, int* y) {
	if (x != y) {
		*x ^= *y;
		*y ^= *x;
		*x ^= *y;
	}
}

/****************************** heap sort *****************************/

// Thanks to greeksforgreeks, which helps a lot in heap sort
// https://www.geeksforgeeks.org/heap-sort/

// max heap, number at i must be larger than its children
void heapify(int array[], int n, int i) {
	int maxIndex = i;
	int leftChildIndex = 2 * i + 1;
	int rightChildIndex = leftChildIndex + 1;

	// check if left child is larger
	if (leftChildIndex < n && array[maxIndex] < array[leftChildIndex]) {
		maxIndex = leftChildIndex;
	}

	// check if right child is larger
	if (rightChildIndex < n && array[maxIndex] < array[rightChildIndex]) {
		maxIndex = rightChildIndex;
	}

	// if number at i is not max, swap with max and heapify number at max
	if (maxIndex != i) {
		swap(array + maxIndex, array + i);
		heapify(array, n, maxIndex);
	}
}

// ascending order, build a max heap
void buildHeap(int array[], int n) {
	int i;
	// heapify every elements from the last leaf to 0 inclusive
	// no need to heapify nodes with no children
	for (i = n / 2 - 1; i >= 0; --i) {
		heapify(array, n, i);
	}
}

void heapSort(int array[], int n) {
	buildHeap(array, n);
	while (n > 1) {
		--n;
		swap(array, array + n);
		heapify(array, n, 0);
	}
}

/****************************** merge sort *****************************/

// merges array2 into array1
// n1 n2: lengths or array1 array2
void merge(int array1[], int array2[], int n1, int n2, int auxiliary[]) {
	int i, j, k;

	// copy array1 to auxiliary
	for (i = 0; i < n1; ++i) {
		auxiliary[i] = array1[i];
	}

	i = 0;	// index of auxiliary
	j = 0;	// index of array2
	k = 0;	// index of array1
	// keep coping the smallest element to array1
	// until one of the array is empty
	while (i < n1 && j < n2) {
		if (auxiliary[i] < array2[j]) {
			array1[k] = auxiliary[i];
			++i;
		} else {
			array1[k] = array2[j];
			++j;
		}
		++k;
	}

	// copy the remaining elements of auxiliary to array1
	while (i < n1) {
		array1[k] = auxiliary[i];
		++k;
		++i;
	}

	// copy the remaining elements of array2 to array1
	while (i < n1) {
		array1[k] = array2[j];
		++k;
		++j;
	}
}

// merge sort with auxiliary array allocated
void mergeSortRecursive(int array[], int n, int auxiliary[]) {
	// array with size 1 or less is sorted
	if (n > 1) {
		int mid = n / 2;
		// recursively sort the first half
		mergeSortRecursive(array, mid, auxiliary);

		// recursively sort the second half
		mergeSortRecursive(array + mid, n - mid, auxiliary);

		// merge the sorted two halves
		merge(array, array + mid, mid, n - mid, auxiliary);
	}
}

void mergeSort(int array[], int n) {
	// create an auxiliary array
	int auxiliary[n];

	// call the real merge sort
	mergeSortRecursive(array, n, auxiliary);
}

/****************************** insertion sort *****************************/
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

/****************************** quick sort *****************************/

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

/****************************** selection sort *****************************/

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

/****************************** bubble sort *****************************/

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

/****************************** intro sort *****************************/

// this function uses heap sort and partition from quick sort
// for details of this algorithm, visit:
// https://en.wikipedia.org/wiki/Introsort
void introSortRecursive(int array[], int n, int maxDepth) {
	if (n <= 1) {
		return;
	} else if (maxDepth <= 0) {
		heapSort(array, n);
	} else {
		int firstEqual;
		int firstGreater;
		partition(array, n, &firstEqual, &firstGreater);
		introSortRecursive(array, firstEqual, maxDepth - 1);
		introSortRecursive(array + firstGreater, n - firstGreater, maxDepth - 1);
	}
}

// swithes between quick sort and heap sort
// when the recursion depth < log array length, use quick sort
// otherwise use heap sort
void introSort(int array[], int n) {
	int maxDepth = log(n) * 2;
	introSortRecursive(array, n, maxDepth);
}

/****************************** tim sort *****************************/

#define SIZE_RUN 32

/* 
this algorithms is O(n log n), proof is in the comments below
*/
void timSort(int array[], int n) {
	int auxiliary[n];
	int i, size;

	// first sort all runs using insertion sort
	// this step is O(n)
	// proof:
	//  loop (n/SIZE_RUN) times
	//  each loop is O(SIZE_RUN^2) using insertion sort
	//  overall is O(SIZE_RUN^2 * n/SIZE_RUN) = O(n * SIZE_RUN)
	//  since SIZE_RUN is a constant, it is O(n)
	for (i = 0; i < n; i += SIZE_RUN) {
		if (i + SIZE_RUN <= n) {
			insertionSort(array + i, SIZE_RUN);
		} else {
			// last part might not be exactly of size run
			insertionSort(array + i, n - i);
		}
	}

	// then merge those runs 
	// this step is O(n log n)
	// proof:
	//  outer loop log(n/SIZE_RUN) times
	//  inner loop is O(n) using merge
	//  overall is O(n log(n/SIZE_RUN))
	//  simce SIZE_RUN is a constant, it is O(n log n)
	for (size = SIZE_RUN; size < n; size *= 2) {
		for (i = 0; i < n; i += 2 * size) {
			int rightSize = size;
			if (i + 2 * size > n) {
				// exceeds limit
				rightSize = n - i - size;
			}
			merge(array + i, array + i + size, size, rightSize, auxiliary);
		}
	}

	// combining two parts, it is O(n + n*log n) which is O(n log n)
}

/****************************** shell sort *****************************/

// The complexity of  shell sort heavily depends on the gap sequence
// This gap sequence is O(n*(log n)^2)
// Author: Pratt, 1971, OEIS: A003586
// visit https://en.wikipedia.org/wiki/Shellsort for more information
#define N_GAPS 55
int GAPS[] = {1, 2, 3, 4, 6, 8, 9, 12, 16, 18, 24, 27, 32, 36, 48, 54, 64, 72, 81, 
	96, 108, 128, 144, 162, 192, 216, 243, 256, 288, 324, 384, 432, 486, 512, 576, 
	648, 729, 768, 864, 972, 1024, 1152, 1296, 1458, 1536, 1728, 1944, 2048, 2187, 
	2304, 2592, 2916, 3072, 3456, 3888};

void shellSort(int array[], int n) {
	int sorted, i, curr, gapIndex, gap;

	// do multiple insertion sorts, steps differ, all in GAPS
	for (gapIndex = N_GAPS - 1; gapIndex >= 0; --gapIndex) {
		gap = GAPS[gapIndex];
		// this inner for loop is just an insertion sort with a different step
		// loop through gap..n with step gap
		for (sorted = gap; sorted < n; sorted += gap) {
			// record current element to be shifted
			curr = array[sorted];

			// loop through sorted..0 unless
			// a smaller element than current is found
			i = sorted;
			while (i - gap >= 0 && array[i - gap] > curr) {
				// right shift element gap steps
				array[i] = array[i - gap];
				i -= gap;
			}
			// put the element being shifted at 
			// the correct place
			array[i] = curr;
		}
	}
}


/****************************** Algorithms are fun!    *****************************/
/****************************** Welcome to contribute! *****************************/