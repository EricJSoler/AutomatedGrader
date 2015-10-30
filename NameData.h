// takes the name of a file as a wstring data type and stores information about it and renames the file
// stores all the different components of the string for use in potential logic functions of the program, 
// keeps true/false data on late status if the file compiled and if file cound't be processed into a standard naming convention.

// mostly used as am organization structure. 

#include <iostream>
#include <string>
using namespace std;

#ifndef Grading_NameData_h
#define Grading_NameData_h


class NameData
{
private:
public: 
    string classname;
    string student;
    string problem;
    string newname; //name after canvas garbage is taken out
    string originalname; // original name. 
    bool latestatus; 
	bool badname;
	bool compilestatus;
    string searchtag; //for use in grouping files together, and finding associated compiled .exe or .class
	

	void Namedata()
	{
		latestatus=false;
		badname=false;
		compilestatus=false;
    }

	void Namedata(string a) //intakes the original file name and sets it to a variable
	{
        originalname=a;
		latestatus=false;
		badname=false;
		compilestatus=false;
    }

	void makenamedata();//takes all the data in the name convention and stores it.
    
    void setnewname();// eliminates canvas generated clutter
    
    string getname(); //returns the newname for use in nameing file.
    
	void amIlate(); //determines and updates late status if LATE tag was in filename.
	
	bool Late(); //returns latestatus as a boolin data
   
	void NameData::fetch();
	
	//master function put in bad name return good name and stores data in the structure for any use.
    string canvasnamessuck(string);
		//master function for names that already match naming convention or have been taged as bad names
	
	string allgoodname(string);

	void badnamed();

	


};

#endif
