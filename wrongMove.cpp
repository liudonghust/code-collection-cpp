// how to create move constructor and destructor

#include <iostream>
#include <string>
#include <iterator>
using namespace std;

class Str{
	string *name;
public:
	Str(string s){
		cout << "constructor" << endl;
		name = new string(s);
	}
	Str(const Str& s){
		cout << "copy constructor" << endl;
		name = new string(*(s.name));
	}
	Str(Str&& s){
		cout << "move constructor" << endl;
		name = s.name;
		s.name = nullptr;
	}
	Str& operator=(const Str& s){
		cout << "operator= lvalue" << endl;
		if (this == &s)
			return *this;
		name = new string(*(s.name));
		return *this;
	}
	Str& operator=(Str&& s){
		cout << "operator= rvalue" << endl;
		// before moving, free old memory.
		delete name;
		
		name = s.name;
		s.name = nullptr;
		return *this;
	}
	~Str(){  //bad 
		cout << "~Str()" << endl;
		if(name != nullptr){
			delete name;
			name = nullptr;
		}
	}
};

// make a rvalue string
Str make_Str(){
	Str s("make_str");
	return s;
}

int main(){
	Str str1("sting1");
	// str2 use move, but when temp Str is deconstructed, name is deleted,
	// so str2.name point to a place have been freed/
	Str str2(make_Str());   //bad 
	const Str str3("const string3");
	str2 = str3;
}