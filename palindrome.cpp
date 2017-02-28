//palindrome string is a word or a group of words
//that read the same forward and backward.
//For example: "madam" and "wow"

#include <iostream>
#include <string>
using namespace std;

bool palindrome(const string& str){
	int start = 0;
	int end = str.size() - 1;
	while (start < end){
		if (str[start] != str[end])
			return false;
		start++;
		end--;
	}
	return true;
}

int main(int argc, char* argv[]){
	string str(argv[1]);
	cout << str << " is palindrome?  " << palindrome(str) << endl;
}