// A[]: sorted array
// O(logN)
int bin_search(int A[], int left, int right, int k)
{
	if (left == right){
		if (A[left] == k)
			return k;
		else
			return -1;
	}

	int middle = (right + left) / 2;
	if (A[middle] == k) 
		return middle;
	if (A[middle] > k)
		bin_search(A, left, middle - 1, k);
	else
		bin_search(A, middle + 1, right, k);
}