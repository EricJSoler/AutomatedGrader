#include "Compiler.h"

	
	//groups a list of files into one input string
	void Compiler::grouper()
	{
		for(int i=0;i<size;i++)
		{
			if(extensionsort(list[i]))
			{
				winput.append(directory);
				winput.append("\\");
				winput.append(list[i]);
				if(i!=size-1)
				{
					winput.append(" ");
				}
			}
		}
	}
	
	//ouputs input string //mostly for testing
	void Compiler::reportinput()
	{
		cout<<input<<endl<<endl;
	}

	//default sets extension and starter for filetypes
	Cplusplusc::Cplusplusc()
	{
		prefix = "EHsc /Fe";

		ext="cpp";
		
	}
	//constructs the data string for input to be compiled calls compiler at end
	Cplusplusc::Cplusplusc(string dir, string* l,int s)
	{
		prefix = "EHsc /Fe";
		ext="cpp";
		Compilethis(dir,l,s);
	}
	//compiles the files
	void Cplusplusc::Compilethis(string d, string* l,int s)
	{	
		directory=d;
		size=s;
		list=l;
		winput="";
		winput.append(prefix);
		d.append("\\");
		d.append("CS0_compiled");
		if (GetFileAttributesA(d.c_str())==INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectoryA(d.c_str(), NULL);
		}
		d.append("\\");
		winput.append(d);
		winput.append(" ");

		grouper();

		//winput.append("\"");
		processing();
	}

		void Cplusplusc::processing()
		{
		STARTUPINFOA* si = new STARTUPINFOA;
		PROCESS_INFORMATION* pi = new PROCESS_INFORMATION;

		ZeroMemory(si, sizeof(*si));
		si->cb = sizeof(*si);
		ZeroMemory(pi, sizeof(*pi));
		
		
		//"c:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\vcvars32.bat"

		LPSTR I = const_cast<LPSTR>(winput.c_str());
		CreateProcessA("c:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\VC\\bin\\cl.exe",I, NULL, NULL,FALSE, NULL, NULL, NULL, si, pi);
		WaitForSingleObject(pi->hProcess, 3000);
	

		CloseHandle(pi->hProcess);
		CloseHandle(pi->hThread);

		delete si;
		delete pi;
		}


	//extension checker only uses .cpp files
	bool Cplusplusc::extensionsort(string e)
	{
		int index=e.find_last_of('.') + 1;
		if(e.substr(index)==ext)
			return true;
		else return false;
	}

	//default sets extension and starter for filetypes
	javac::javac()
	{
		prefix="javac -d ";
		ext="java";
	}

	javac::javac(string wdirectory)
	{
		prefix = "javac -d ";
		ext = "java";
		Lister files;
		int count = files.filecounter(wdirectory);  //counts the number of files in the start directory
		string *filenames = new string[count];	// makes an pointer to an array for working with names
		filenames = files.listfiles(wdirectory); // lists all the files in that directory
		//count = count;  //2 files named "." and "..." are always in the directory sets  to ignore those
		Compilethis(wdirectory, filenames, count);

	}

	//constructs the data string for input to be compiled calls compiler at end
	javac::javac(string dir, string* l,int s)
	{
		prefix = "javac -d ";
		ext="java";
		Compilethis(dir,l,s);
	}

	//compiles the files
	void javac::Compilethis(string d, string* l,int s)
	{	
		directory=d;
		size=s;
		list=l;
		winput="";

		winput.append(prefix);
		d.append("\\");
		d.append("CS0_compiled");
		if (GetFileAttributesA(d.c_str())==INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectoryA(d.c_str(), NULL);
		}
		d.append("\\");
		winput.append(d);
		winput.append(" ");

		grouper();

		winput.append("\"");
		processing();
	}

	void javac::processing()
	{
		STARTUPINFOA* si = new STARTUPINFOA;
		PROCESS_INFORMATION* pi = new PROCESS_INFORMATION;

		ZeroMemory(si, sizeof(*si));
		si->cb = sizeof(*si);
		ZeroMemory(pi, sizeof(*pi));
		cout << winput << endl;
		

		LPSTR I = const_cast<LPSTR>(winput.c_str());
		CreateProcessA("C:\\Program Files\\Java\\jdk1.8.0_65\\bin\\javac.exe",I, NULL, NULL,false, NULL, NULL, NULL, si, pi);
		WaitForSingleObject(pi->hProcess, 3000);
		//TerminateProcess(pi->hProcess, 0);

		CloseHandle(pi->hProcess);
		CloseHandle(pi->hThread);

		delete si;
		delete pi;
	}

	//extension checker
	bool javac::extensionsort(string e)
	{
		int index=e.find_last_of('.') + 1;
		if(e.substr(index)==ext)
			return true;
		else return false;
	}