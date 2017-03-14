// inversion: for an array, if a[i] > a[j] and i < j
// get the number of inversions

// linear compare.
// O(n^2)
int getInvCount(int* a, int size)
{
	int count = 0;
	for(int i = 0; i < size; i++)
		for(int j = i+1; j< size; j++)
			if(a[i] > a[j])
				count++;
	return count;
}

// divide and conquer
// O(nlogN) using merge sort
int merge_count(int *a, int* temp, int left, int middle, int right)
{
	int inv_count = 0;
	int i = left;
	int j = middle + 1;
	int k = left;
	while (i <= middle && j <= right){
		if (a[i] > a[j]){
			inv_count += middle - i + 1;
			temp[k++] = a[j++];
		}
		else
			temp[k++] = a[i++];
	}
	while (i <= middle)
		temp[k++] = a[i++];
	while (j <= right)
		temp[k++] = a[j++];
	for (int i = left; i <= right; i++)
		a[i] = temp[i];
	return inv_count;
}

int getInvCount(int* a, int* temp, int left, int right)
{
	int count = 0;
	if (left == right)          // base case
		return 0;

	int middle = (left + right) / 2;                           // divide
	count = getInvCount(a, temp, left, middle);                // conquer left
	count += getInvCount(a, temp, middle + 1, right);          // conquer right
	//combine
	count += merge_count(a, temp, left, middle, right);
	return count;
}

