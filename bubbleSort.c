void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

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