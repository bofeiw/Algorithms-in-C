void insertionSort(int array[], int n) {
	int sorted, i, curr;
	for (sorted = 1; sorted < n; ++sorted) {
		curr = array[sorted];
		i = sorted;
		while (i > 0 && array[i - 1] > curr) {
			// right shift element
			array[i] = array[i - 1];
			--i;
		}
		array[i] = curr;
	}
}