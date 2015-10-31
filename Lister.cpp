#include "Lister.h"

	//returns a pointer to an array of file names in a directory, main purpose of class
	string* Lister::listfiles(string dir) 
	{
	directory=dir;
	directory.append("\\*");
	searchNlist();
	return thelist;
	}
    
	// returns a list of files that start in a certain way. 
	string* Lister::listfiles(string dir,string name)
    {
        directory=dir;
        directory.append("\\");
        directory.append(name);
        directory.append("*");
		searchNlist();
		return thelist;
    }
	
	//  counts all the files in a directory and returns the number, sets size of list to return
	int Lister::filecounter() 
	{
		 HANDLE h = FindFirstFileA(directory.c_str(), &data);	
	if( h!=INVALID_HANDLE_VALUE )
        {
			filetotal=0;
            do
            {
                filetotal++;
            } while(FindNextFileA(h,&data));
        }
		thelist=new string[filetotal];
        return filetotal;
	}
	
	//counts files in a directory
	int Lister::filecounter(string dir)
{
    directory=dir;
    directory.append("\\*");
    HANDLE h = FindFirstFileA(directory.c_str(), &data);
	if( h!=INVALID_HANDLE_VALUE )
    {
        filetotal=0;
        do
        {
            filetotal++;
        } while(FindNextFileA(h,&data));
    }
    thelist=new string[filetotal];
    return filetotal;
}

	
	//counts files of a given name in a directory
    int Lister::filecounter(string dir,string name)
{
    directory=dir;
    directory.append("\\");
    directory.append(name);
    directory.append("*");
    HANDLE h = FindFirstFileA(directory.c_str(), &data);
	if( h!=INVALID_HANDLE_VALUE )
    {
        filetotal=0;
        do
        {
            filetotal++;
        } while(FindNextFileA(h,&data));
    }

    return filetotal;
}

	//makes the list of files from a directory input, called by listfiles
	void Lister::searchNlist() 
    {
	
    HANDLE h = FindFirstFileA(directory.c_str(), &data);	
	
	if( h!=INVALID_HANDLE_VALUE )
        {
			int filecount=0;
            do
            {
                int a=lstrlenA( data.cFileName ) + 1;
                char*   nPtr = new char [a];
                for( int i = 0; i < lstrlenA( data.cFileName ); i++ )
                    nPtr[i] = char( data.cFileName[i] );
            
                nPtr[lstrlenA( data.cFileName )] = '\0';
                thelist[filecount]=nPtr;
                filecount++;
            } while(FindNextFileA(h,&data));
        }
        
    }