#include "Namedata.h"
#include "Lister.h"
#include <Windows.h>
#include "Compiler.h"
#include "Process.h"

void renamer(string,NameData);
bool extension(string,string);


int main()
{   

	

	
	// makes sure directory exists before proceding
	LPCSTR wdirectory;
	string directory;
	do
	{
			directory ="c:\\HW\\";
			cout<<"Enter directory of files to grade\n";
			string userinput = "Ch14";
			//cin>> userinput;

			directory.append(userinput);
			wdirectory=directory.c_str(); 
	}
	while (GetFileAttributesA(wdirectory)==INVALID_FILE_ATTRIBUTES);
	

		Lister files;  
		int count=files.filecounter(wdirectory);  //counts the number of files in the start directory
		string *filenames=new string[count];	// makes an pointer to an array for working with names
		filenames=files.listfiles(wdirectory); // lists all the files in that directory
		count=count-2;  //2 files named "." and "..." are always in the directory sets  to ignore those
	

	//creates a data structure to process store and use all the data in the name and use it for compiling. 
		NameData* allfiles=new NameData[count];
	
		
		for (int i=0;i<count;i++)
		{	
			if(!strncmp(filenames[i].c_str(),".", MAX_PATH) && !strncmp(filenames[i].c_str(), "..", MAX_PATH))
				continue;
			//treat files that start with CS and a number as having a good name
			if((filenames[i+2][0]=='C' || filenames[i+2][0]=='c') && (filenames[i+2][1]=='S' || filenames[i+2][1]=='s'))
			{
				allfiles[i].allgoodname(filenames[i+2]);//gets data from the name
			}
			
			// handles names from canvas format
			else
			{	
				allfiles[i].canvasnamessuck(filenames[i+2]); //proceses the name information
				renamer(directory,allfiles[i]);	//rename the files to a good name
			}
		}
	
		//counts how many files have a unique student and project tag. used to make an array of proper size
		int ucount=1;
		for (int i=0; i<count-1; i++) 
		{
			if (allfiles[i].searchtag!=allfiles[i+1].searchtag)//compares strings
			{

				ucount++;
			}
		}
	
		//creates a new array from the list of all files that has unique problems to send to the compiler
		NameData* unique=new NameData[ucount];
		int ucount2=1;
		unique[0]=allfiles[0];
		for(int i=0;i<count-1;i++)	
		{	
			// if the current name and next are not the same adds the name to the list
			if (allfiles[i].searchtag!=allfiles[i+1].searchtag) 
			{
				unique[ucount2]=allfiles[i+1];
				ucount2++;//incrementer for position in array of unique projects	
			}	
		}

		//creates a list of all files associated with a unique student/problem for each entry in the array of unique names then sends them to the compiler
		string **input;
		input=new string*[ucount];
		for(int i=0;i<ucount;i++)
		{
			if(unique[i].badname == false) //skips files that didn't go through naming convention properly.
			{
				int c=files.filecounter(directory,unique[i].searchtag);
				input[i]=files.listfiles(directory,unique[i].searchtag);

				if (extension(input[i][0],"cpp")) //if cpp files sends to the C++ compiler
				{
					//Cplusplusc(directory,input[i],c);
				}
				if (extension(input[i][0],"java")) //if java sends to the java 
				{
					javac(directory,input[i],c);
				}
			}
		}

		//adjusts directory string to be executables directory
		string executablesdir=directory.append("\\");  
		executablesdir.append("CS0_compiled");
		LPCSTR wexecutablesdir=executablesdir.c_str();
	
		//gets all files in the executables directory
		int execount=files.filecounter(wexecutablesdir); //gets  # of files
		string *exenames=new string[execount]; // makes array of proper size
		exenames=files.listfiles(wexecutablesdir); // gets the file names
	


		// checks the list of executables against the list of unique projects and marks the projects as not compiled or compiled
		for (int j=0;j<ucount;j++)
		{	
			if(unique[j].badname == false) // if the name of the file could be processed 
			{
			
				
				string f =unique[j].newname;
				f.erase(f.find_last_of('.')); //gets name of file that should have compiled
				
				
				unique[j].compilestatus=false;//sets as didn't compile for default prior to determining
				for (int i=2;i<execount;i++)
				{
					string c=exenames[i];
					c.erase(c.find_last_of('.')); //gets names of files that did compile
					
					if (f==c) // if the file that should of compiled matches a file that did compile then marks as ture
					{
						unique[j].compilestatus=true;
						i=execount; //endsloop if found
					}	
				}
			}
			else unique[j].compilestatus=false; // if it was a bad name it couldn't of compiled
		}
		

		string output;
		output.append(executablesdir);
		output.append("\\CS0_output.txt");

		//output statements 
		ofstream Output;
		Output.open(output, ios::out | ios::app );
		
		Output<<"\n__________________________________________________________________________________\n";

		for (int i=0;i<ucount;i++)
		{
			if (extension(unique[i].newname,"h")==false) //move to a different spot in logic, files with bad canvas names might be here, 
			{
				if (unique[i].badname==false)
				{
				Output<<unique[i].newname<<endl;
				if(unique[i].latestatus)
					Output<<"turned in late\n";  //late status
				if (unique[i].compilestatus==false)
					Output<< "did not compile\n";  //didn't compile
				if (unique[i].compilestatus==true) //runs program if compiled.
				{
					if (extension(unique[i].newname,"cpp")) //if cpp files sends to the C++ compiler
					{

						Output.close();
						CplusplusRunner(executablesdir,unique[i].searchtag,output);
						Output.open(output, ios::out | ios::app );
					}
					if (extension(unique[i].newname,"java")) //if java sends to the java 
					{
						Output.close();
						JavaRunner(executablesdir,unique[i].searchtag,output);
						Output.open(output, ios::out | ios::app );
					}
				}
				Output<<"\n__________________________________________________________________________________\n"; //break statement
				}
			}
		}
		Output.close();
	
		system("del *.obj"); // deletes object files from program directory if there

	return 0;
}

//function to rename files
void renamer(string dir,NameData aname)
{		
	dir.append("\\");
		string tdir=dir;
		string oname=tdir.append(aname.originalname); // constructs directory and old name string 
		tdir=dir;
		string nname=tdir.append(aname.newname); // construcs directory and new name string 
		rename(oname.c_str(),nname.c_str()); // renames
}


	bool extension(string e,string ext)  //checks a file extension against a given label 
	{
		int index=e.find_last_of('.') + 1;
		if(e.substr(index)==ext)
			return true;
		else return false;
	}