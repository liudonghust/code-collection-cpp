// linear compare.
//O(n)
int maxer(int *a, int size)
{
	int max = -1;
	for(int i = 0; i < size; i++)
		if(a[i] > max)
			max = a[i];
	return max;
}


// divide and conquer
// O(logN)
int maxer(int *a, int left, int right){
	if (right == left)          // base case.
		return a[left];
	
	int middle = (right + left) / 2;     // divide
	int maxLeft, maxRight;
	maxLeft = maxer(a, left, middle);    // conquer left
	maxRight = maxer(a, middle + 1, right);   // conquer right

	if (maxLeft > maxRight)        // combine
		return maxLeft;
	else
		return maxRight;
}