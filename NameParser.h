#pragma once
#include <cstdlib>
#include <string>

using namespace std;

const string driver = "driv";

class NameParser {

public:
	NameParser();
	~NameParser();
	//Returns a string with the students name expecting
	//input like "au--khoa_3439707_33409987_Bill-1.java" 
	static string studName1(string readFileName)
	{
		int stringSize = readFileName.size();
		string name = "";
		for (int i = 0; i < stringSize; i++) {
			if (readFileName[i] == '_') {
					break;
			}
			else{
				name += readFileName[i];
			}
		}
		return name;
	}

	//Returns true if finds the sequence "driv"
	static bool isDriver(string readFileName)
	{
		int size = readFileName.size();
		for (int i = 0; i < size; i++) {
			readFileName[i] = tolower(readFileName[i]);
		}
		int seqSize = driver.size() - 1;
		size = readFileName.size();
		for (int i = 0, seqLoc = 0; i < size; i++) {
			if (readFileName[i] == driver[seqLoc]) {
				seqLoc++;
				if (seqLoc == seqSize)
					return true;
			}
			else
				seqLoc = 0;
		}
		return false;
	}

	//
	static string compName1(string readFileName)
	{
		string yourMom = "";
		int size = readFileName.size();
		bool hit = false;
		for (int i = readFileName.size() - 1; i >= 0; i--) {
			if (readFileName[i] == '.' && !hit) {
				hit = true;
				if (readFileName[i - 2] == '-')//THis means duplicate was submitted
				{
					i -= 2;
				}
			}
			else if (readFileName[i] == '_') {
				break;
			}
			else if (hit) {
				yourMom += readFileName[i];
			}
		}
		//Reverse the name
		string yourDad = "";
		for (int i = yourMom.size() - 1; i >= 0; i--) {
			yourDad += yourMom[i];
		}
		yourDad += ".java";
		return yourDad;
	}

	static string getFileNameFromFilePath(string path)
	{
		int size = path.size();
		string name = "";
		for (int i = size - 1; i >= 0; i--) {
			if (path[i] != '\\') {
				name += path[i];
			}
			else
				break;
		}
		string ans = "";
		for (int i = name.size() - 1; i >= 0; i--) {
			ans += name[i];
		}
		return ans;
	}

	static string removeFileExtension(string read)
	{
		string ans = "";
		for (int i = 0; i < read.size(); i++) {
			if (read[i] == '.')
				break;
			else
				ans += read[i];
		}
		return ans;
	}

};

