// dir.cpp
/*
This file is a demo of the following things
	1) How to get current directory
	2) How to refer to a file relative to the path of the executable, ignoring the "current directory"
	3) (Dumb) cross-platform programming with #ifdef (#if defined)
Thanks to:
	http://www.codebind.com/cpp-tutorial/c-get-current-directory-linuxwindows/
	https://sourceforge.net/p/predef/wiki/OperatingSystems/
	https://stackoverflow.com/questions/4025370/can-an-executable-discover-its-own-path-linux
	https://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
Boost may simplify it (tl;dr)
  http://www.boost.org/doc/libs/1_65_1/libs/filesystem/doc/index.htm
*/
// non os-specific headers
#include<cstdio>
#include<iostream>
#include<string>
#include<fstream>
// os-specific things
#if defined( _WIN32 ) || defined ( _WIN64 )
// >>> Windows
#include<windows.h>
#define selfPath(STR){\
	char szPath[MAX_PATH];\
	GetModuleFileName(nullptr,szPath,MAX_PATH);\
	STR=string(szPath);\
  STR=STR.substr(0,STR.find_last_of("\\"));\
	/*GetModuleFileName( "", szPath, MAX_PATH );*/\
}
#define APPEND "\\data.dat"
// <<< Windows
#elif defined( __linux__ ) || defined ( __gnu_linux__ )
// >>> Linux
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<climits>
#include<cstring>
#define selfPath(STR){\
	/*readlink does not '\0' terminate the C-style string*/\
  char dest[PATH_MAX];\
	memset(dest,0,sizeof(dest));\
  readlink("/proc/self/exe",dest,PATH_MAX);\
  STR=string(dest);\
  STR=STR.substr(0,STR.find_last_of("/"));\
}
#define APPEND "/data.dat"
// <<< Linux
#else
	#error "Unsupported OS"
#endif
// here we go
using namespace std;
int main(){
  // cout << getCurrentDir() << endl;
  string path;
  selfPath(path);
  ofstream ofs(path+APPEND);
  // cout<<str.substr(0,str.find_last_of("/"))<<endl;
  // cout<<str<<endl;
  return 0;
}
