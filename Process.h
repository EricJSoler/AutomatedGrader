#ifndef PROCESSRUNNER_H
#define PROCESSRUNNER_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <fstream>
using namespace std;



class ProcessRunner
{
public:
	LPSTR* lpFileName;
	STARTUPINFOA* si;
	PROCESS_INFORMATION* pi;
	HANDLE handOutRead;
	HANDLE handOutWrite;
	SECURITY_ATTRIBUTES secAttr;
	string FileName;
	LPSTR setFile;
	LPSTR path;
	string tempFile;
	
	virtual unsigned short int RunProcess(LPSTR)=0;
	void SetZero();
	void fileOutput(LPSTR*, string);
	void runFileError(LPSTR*, string);
	void prepare();
	~ProcessRunner();
	ProcessRunner();
	ProcessRunner(LPSTR, string);
	ProcessRunner(LPSTR, LPSTR, string);
	void RunProcessT();
};



class CplusplusRunner:public ProcessRunner
{
public:
	CplusplusRunner();
	CplusplusRunner(string, string, string);
	unsigned short int RunProcess(LPSTR);
};

class JavaRunner:public ProcessRunner
{
public:
	JavaRunner();
	/*JavaRunner()*/
	JavaRunner(string, string, string);
	unsigned short int RunProcess(LPSTR);
};

#endif