// O(n^2)
int maxSubSequenceSum(const int a[], int n)
{
	int thisSum, maxSum, i, j;
	maxSum = 0;
	for(i = 0; i < n; i++){
		thisSum = 0;
		for(j = i; j < n; j++){
			thisSum += a[j];
			if(thisSum > maxSum)
				maxSum = thisSum;
		}
	}
	return maxSum;
}

// divide and conquer
// O(nLogn)
int maxSubSequenceSum(const int a[], int left, int right)
{
	int maxLeftSum = maxRightSum = 0;
	if(left == right)                    // base case: only one element left
		if(a[left] > 0)
			return a[left];
		else
			return 0;
	middle = (right + left) / 2;                              // divide
	maxLeftSum = maxSubSequenceSum(a, left, middle);         // conquer left
	maxRightSum = maxSubSequenceSum(a, middle+1, right);     // conquer right
	// conquer center
	int maxLeftBorderSum = maxRightBorderSum = 0;
	int leftBorderSum = rightBorderSum = 0;
	for(int i = middle; i >= left; --i){                    // left border
		leftBorderSum += a[i];
		if(leftBorderSum > maxLeftBorderSum)
			maxLeftBorderSum = leftBorderSum;
	}
	for(int i = middle+1; i <= right; ++i){
		rightBorderSum += a[i];
		if(rightBorderSum > maxRightBorderSum)
			maxRightBorderSum = rightBorderSum;
	}

	// combine
	return max3(maxLeftSum, maxRightSum, maxLeftBorderSum+maxRightBorderSum);
}