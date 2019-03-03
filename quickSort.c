void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

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