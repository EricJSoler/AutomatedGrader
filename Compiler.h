#include <iostream>
#include <string>
#include "Windows.h"
#include <iostream>
using namespace std;
#include <stdlib.h>


//compiler class can be called with just Cplusplusc(string , string* ,int ) or javac(string , string* ,int ) and everything should happen, 
//takes a directory, and array of files to be compiled together, and the size of that array as input. 


class Compiler
{
private:
public:
	int size;
	string *list;
	string winput;
	CHAR* input;
	string directory;
	
	virtual bool extensionsort(string )=0; //virtual to check extension type

	virtual void Compilethis(string , string* ,int )=0;//virtual for actual compiling

	void grouper();//groups multiple files into one string for compileing and checks file type
	
	void reportinput();//out put the string of information to be compiled
	
	virtual void processing()=0;
};



class Cplusplusc:public Compiler
{
private:
public:
	string prefix;
	string ext;

	Cplusplusc();

	Cplusplusc(string , string* ,int ); //constructor  call this and all is well

	virtual void Compilethis(string , string* ,int ); //turns a list of names into a single input command

	bool extensionsort(string ); //only allows .cpp files for be procesed

	void processing(); //actually runs the compiler
	
};


class javac:public Compiler
{
private:
public:
	string prefix;
	string ext;
	
	javac();
	
	javac(string , string* ,int ); //constructor  call this and all is well

	void Compilethis(string , string* ,int ); //turns a list of names into a single input command
	
	bool extensionsort(string );	//only allows .java files for be procesed

	void processing(); //actually runs the compiler

};
