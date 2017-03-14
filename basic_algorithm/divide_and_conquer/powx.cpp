// for-loop
// O(N)
int pow(int base, int exponent)
{
	int result = 1;
	for(int i = 0; i < exponent; i++)
		result *= base;
}

// divide and conquer
// O(logN)
int pow(int base, int exponent)
{
	if(exponent == 1)
		return base;
	if(exponent == 0)
		return 1;
	int middle = exponent / 2;     // divide
	int temp = pow(base, middle);  // conquer
	// combine  
	if(exponent % 2 == 0)          // even
		return temp * temp;
	else                           // odd
		return base * temp * temp;
}