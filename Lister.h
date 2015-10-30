//class for making arrays of file names, given a directory or a directory and a serch criteria it will make an array of all the file names in that directory.
//also can be used to count the number of files in that directory, for making dynamic arrays of proper size

#include <iostream>
#include <string>
#include "Windows.h"
using namespace std;

#ifndef Grading_Lister_h
#define Grading_Lister_h



class Lister
{
private:
	 WIN32_FIND_DATAA data; //data type repeatedly needed by functions constantly overwritten

public: 
    string directory;
    int filetotal;
    string *thelist;
		
	string* listfiles(string); //returns a pointer to an array of all file names in a directory given a directory as  input,  main purpose of class
	string* listfiles(string,string);// returns a list of files that start in a certain way. 

	int filecounter(); //  counts all the files in a directory and returns the number used in listing files.
    int filecounter(string);// counts all files in a given directory
	int filecounter(string,string); //counts files of a particular name in a given directory

    void searchNlist(); //makes the list of files from a directory input,set the number of files with file counter first, intended to be called from list files functios.

};

#endif
