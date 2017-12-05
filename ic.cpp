#include<iostream>
#include"ic.h"
using namespace std;

int main(int argc,char* argv[]) {
	cout << "version 1.0.0 created by junghun.lee 171205" << endl;
	if (argc < 3) { cout << "ic [org_folder] [cpy_folder]" << endl; return 1; }
	ic m(argv[1], argv[2]);
	m.run();
	return 0;
}