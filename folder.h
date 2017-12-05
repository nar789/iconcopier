#pragma once
#include<string>
using namespace std;
class Folder {
private:
	static Folder* root;
	Folder() {};

public:
	string s, d;
	virtual ~Folder() {  };
	static Folder* get() {
		if (!root)root = new Folder();
		return root;
	};
};