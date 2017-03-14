void merge(int []a, int left, int middle, int right, int []temp)
{
	int i = left, j = middle + 1;
	int k = 0;
	while(i <= middle && j <= right )
		if(a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	while(i <= middle)
		temp[k++] = a[i++];
	while(j <= right)
		temp[k++] = a[j++];

	// copy back
	for(i = 0; i < k; i++)
		a[left + i] = temp[i];
}

void merge_sort(int[] val, int left, int right, int[] temp)
{
	if(left == right)         // base case: only one element == sorted
		return;

	int middle = (right + left) / 2;         // divide

	merge_sort(val, left, middle, temp);        // conquer left
	merge_sort(val, middle+1, right, temp);     // conquer right

	merge(val, left, middle, right, temp);      // combine
}
