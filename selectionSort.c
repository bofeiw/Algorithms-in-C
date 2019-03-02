void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

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
