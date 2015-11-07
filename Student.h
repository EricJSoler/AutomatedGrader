#pragma once
#include <cstdlib>
#include <string>
#include <direct.h>
#include "NameParser.h"
#include "Lister.h"
#include <iostream>
#include <vector>

using namespace std;
class Student {
public:
	Student();
	Student(string sD,string n) : name(n), originDir(sD) {
		wDir = originDir + "\\" + name;
		_mkdir(wDir.c_str());
		studentMode = false;
	}
	~Student();

	bool studentMode;

	string name;//Name of the student
	string myDriver;
	string sDriver; //Student Driver Name
	
	string wDir;//The students working directory where they will javac their stuff
	string compDir;//The Directory where the compiled files will be sent to from javac
	string originDir;//The directory the program is being ran in

	vector<string> relativeFileNames;//Relative names of the files
	//Recieve file as is from sam's class that does stuff
	void addFile(string name)
	{
		if (NameParser::isDriver(name)) {
			string compName = NameParser::compName1(name);
			sDriver = compName;
			string origName = originDir + "\\" + name;
			string destination = wDir + "\\" + compName;
			rename(origName.c_str(), destination.c_str());
		}
		else {
			string compName = NameParser::compName1(name);
			relativeFileNames.push_back(compName);
			string origName = originDir + "\\" + name;
			string destination = wDir + "\\" + compName;
			rename(origName.c_str(), destination.c_str());
		}
	}

	//Pass the absolute path to the driver file
	//This will move the driver file into this directory
	//and return the string of where it has been placed
	string addDriver(string absoluteLocation)
	{	
		string fileName = NameParser::getFileNameFromFilePath(absoluteLocation);
		string newLocation = wDir + "\\" + fileName;
		myDriver = fileName;
		rename(absoluteLocation.c_str(), newLocation.c_str());
		return newLocation;
	}
	
	//Make Sure to move your driver out before moving student driver in
	void moveStudentDriverIn()
	{
		studentMode = true;
	}

	string* filesForCompilation(int& numFiles)
	{
		numFiles = relativeFileNames.size() + 1;
		string* x = new string[numFiles];
		if (studentMode)
			x[0] = sDriver;
		else
			x[0] = myDriver;
		int i = 1;
		for (std::vector<string>::iterator itr = relativeFileNames.begin();
		itr != relativeFileNames.end(); itr++, i++) {
			x[i] = *itr;
		}
		return x;
	}
};

