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