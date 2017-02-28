#include <iostream>
#include <string>
using namespace std;

string upperCase(string& s){
	char *buf = new char[s.length()]; //create char[] to meet the arg of toupper()
	s.copy(buf, s.length());
	for (int i = 0; i < s.length(); i++)
		buf[i] = toupper(buf[i]);   //toupper()'s argument must be char
	string r(buf, s.length());
	delete buf;
	return r;
}

string lowerCase(string& s){
	char *buf = new char[s.length()]; 
	s.copy(buf, s.length());
	for (int i = 0; i < s.length(); i++)
		buf[i] = tolower(buf[i]);   
	string r(buf, s.length());
	delete buf;
	return r;
}

int main(){
	string str1("abcDef");
	string str2("AbcdEF");
	if (upperCase(str1) == upperCase(str2))
		cout << "str1 is equal to str2 with case insentive" << endl;
}