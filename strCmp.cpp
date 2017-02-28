#include <iostream>
#include <string>
using namespace std;

int stringCmp(string& str1, string& str2){
	string::const_iterator sb1 = str1.begin();
	string::const_iterator sb2 = str2.begin();
	string::const_iterator se1 = str1.end();
	string::const_iterator se2 = str2.end();
	while (sb1 != se1 && sb2 != se2){
		if (toupper(*sb1) != toupper(*sb2))
			return toupper(*sb1) < toupper(*sb2) ? -1 : 1;
		sb1++;
		sb2++;
	}
	return (str1.size() - str2.size());
}

int main(){
	string str1("abcDef");
	string str2("AbcdEFGH");
	cout << stringCmp(str1, str2) << endl;
}