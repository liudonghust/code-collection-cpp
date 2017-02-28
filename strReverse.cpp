#include <iostream>
#include <string>
using namespace std;

string reverseStr(string& str){
	string::reverse_iterator ib = str.rbegin();
	string::reverse_iterator ie = str.rend();
	string revStr;
	revStr.resize(str.size());
	for (int i = 0; ib != ie; ib++, i++)
		revStr[i] = *ib;
	return revStr;
}

int main(){
	cout << "input a string:" << endl;
	string str;
	getline(cin, str);
	cout << "after reversing" << endl;
	string revStr = reverseStr(str);
	cout << revStr << endl;
}