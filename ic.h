#pragma once
#include<iostream>
#include<conio.h>
#include<io.h>
#include<string>
#include<vector>
#include<map>
#include "folder.h"
using namespace std;
Folder* Folder::root = NULL;
class ic {
private:
	map<string, string> strmap;
public:
	virtual ~ic() { delete Folder::get(); };
	ic(string a, string b) {
		Folder::get()->s = a;
		Folder::get()->d = b;
		init();
	};
	void getfolder(vector<string>* list, string dir) {
		_finddata_t fd;
		long handle;
		int result = 1;
		char d[255]; strcpy(d, dir.c_str());
		strcat(d, "\\*.*");
		handle = _findfirst(d, &fd);  //현재 폴더 내 모든 파일을 찾는다.
		if (handle == -1)
		{
			printf("There were no files.\n");
			return;
		}

		while (result != -1)
		{
			//printf("File: %s\n", fd.name);
			list->push_back(fd.name);
			result = _findnext(handle, &fd);
		}
		_findclose(handle);
	};
	void init() {
		strmap.insert(pair<string, string>("32", "drawable-ldpi"));
		strmap.insert(pair<string, string>("36", "drawable-ldpi"));
		strmap.insert(pair<string, string>("48", "drawable-mdpi"));
		strmap.insert(pair<string, string>("72", "drawable-hdpi"));
		strmap.insert(pair<string, string>("96", "drawable-xhdpi"));
	};
	void run() {
		vector<string> slist;
		getfolder(&slist, Folder::get()->s);
		for (string i : slist) {
			for (auto j : strmap) {
				size_t pos = i.find(j.first.c_str());
				if (pos != string::npos) {
					char start[255], dest[255];
					makestartdir(start, i);
					makedestdir(dest, j.second);
					filecopy(i, start, dest);
				}
			}
		}
	};

	void makedestdir(char* dest, string foldername) {
		string d = Folder::get()->d + "\\" + foldername + "\\icon.png";
		strcpy(dest, d.c_str());
	};
	void makestartdir(char* start, string filename) {
		string s = Folder::get()->s + "\\" + filename;
		strcpy(start, s.c_str());
	};

	void filecopy(string filename, string org, string dst) {
		FILE *in = fopen(org.c_str(), "rb");
		FILE *out = fopen(dst.c_str(), "wb");
		char buf[BUFSIZ];
		size_t size;

		if (in == NULL || out == NULL) {
			cout << "file open fail." << endl;
			return;
		}
		while (size = fread(buf, 1, BUFSIZ, in)) {
			fwrite(buf, 1, size, out);
		}
		if (feof(in) != 0)cout << filename + " is copied completely." << endl;
		else cout << "copy fail." << endl;
		fclose(in);
		fclose(out);
	};
};
