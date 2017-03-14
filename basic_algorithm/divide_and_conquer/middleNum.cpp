// computer when merging. a[n] and b[n]
// O(n)
int getMedian(int []a, int []b, int size)
{
	int aindex = bindex = 0;
	int m1, m2;
	for(int count = 0; count <= size; count++){
		// m2 act as temp to store merged value.
		if(a[index] < b[index]){
			m1 = m2;
			m2 = a[aindxe];
			aindex++;
		}
		else{
			m1 = m2;
			m2 = b[bindex];
			bindex++;
		}
		if(aindex == size){
			m1 = a[size - 1];
			m2 = b[0];
		}
		else if(bindex == size){
			m1 = b[size - 1];
			m2 = a[0];
		}
	}
	return (m1 + m2) / 2;
}


// divide and conquer
// O(logN)
inline int median(int* a, int size)
{
	if(size % 2 == 0)
		return (a[size/2 - 1] + a[size/2]) / 2;
	return a[size/2];
}
int getMedian(int *a, int *b, int size)
{
	if(size <= 0)             //false
		return -1;
	if(size == 1)             // base case 1
		return (a[0] + b[0]) / 2;
	if(size == 2)             // base case 2
		return (max(a[0], b[0]) + min(a[1], b[1])) / 2;
	
	int m1 = median(a, size);
	int m2 = median(b, size);

	// if m1 < m2, then median exists in a[m1, ...] or b[..., m2]
	if(m1 < m2){          // divide
		if(size % 2 == 0)              // even number elements
			return getMedian(a + n /2 -1, b, n - n / 2 + 1);      // conquer 1
		return getMedian(a + n/2, b, n/2);                        // conquer 2
	}
	// if m1 >= m2, then median exists in b[m2, ...] or a[..., m1]
	else{
		if(size % 2 == 0)
			return getMedian(a, b + n/2 - 1, n/2 + 1 );           // conquer 3
		return getMedian(a, b + n/2, n/2);                        // conquer 4
	}
	// no combine
}