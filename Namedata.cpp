#include "NameData.h"
#include <fstream>

    
	//uses data of the old name to create the new name. 
    void NameData::setnewname()// eliminates canvas generated clutter
    {
        int newstart=0;
        int badcount=0;
        for (int i=0;badcount<3;i++)//finds when the canvas crap ends
        {
            if (originalname[i]=='_')
            {
                badcount++;
                newstart=i+1;
            }
			
        }
        newname.assign(originalname, newstart,-1); //makes the name without canvas crap
    }

	
	//takes all the data in the name convention and stores it.
    void NameData::makenamedata()
    {   
		int nameend=newname.find_last_of('.');
		int end=5;
		int i=6;
		int start=0;
		
		if (i<=nameend) 
		{	
			classname.assign(newname,start,end); //stores the class
		}
		
		//finds the end of the student name
		start=start+end+1;
		end=0;
		while (newname[i]!='_' && i<=nameend)
		{
			i++;
			end++;
		}
		if (i<=nameend)
		{	
			student.assign(newname,start,end); //stores the student name
		}

		//finds the proplem name
		start=start+end+1;
		end=5;
		i=start+5;
		if (i<=nameend)
		{	
		while(newname[i]!=46 && newname[i]!='_'  && i<=nameend) 
		{
			i++;
			end++;
		}
			problem.assign(newname,start,end); //stores problem name
		}
		
		badname=false; //denotes name was processed as a valid type

		if (i>nameend) //name didn't track as standard nameing convention markes as so
		{
			string nameended="CS0_";
			newname=nameended.append(originalname);
			badnamed();
		}
    }
    
	//updates late status if late tag was in filename.
    void NameData::amIlate() 
    {
        for (int i=0;i<originalname.length();i++)
        {
            if (originalname[i]=='l' && originalname[i+1]=='a' && originalname[i+2]=='t' && originalname[i+3]=='e')
            {
                latestatus=true;
				i=originalname.length(); //ends if loop
				ofstream late;
				late.open("late_status.txt", ios::out | ios::app );
				late<< newname <<" is late\n\n";
				late.close();

			}
            else latestatus=false;
        }
    }
    
	//master function put in bad name return good name and stores data in the structure for any future use.
    string NameData::canvasnamessuck(string badnames)
    {
		originalname=badnames;
		setnewname();
        makenamedata();
		fetch();
		amIlate();
        return newname;
    }
	 
	void NameData::fetch() //  makes a filename search tag to use withlisting function
	{
		searchtag.append(classname);
		searchtag.append("_");
		searchtag.append(student);
		searchtag.append("_");
		searchtag.append(problem);
		

	}

	string NameData::allgoodname(string noncanvas)  //processes namedata if file was good
    {
		originalname=noncanvas;
		if(noncanvas[2]=='0') 
		{//markes files that were previously failed name checks as bad
			newname=noncanvas;
			badnamed();
		}
		else
		{
			newname=noncanvas;
			makenamedata();
		}
		amIlate();
		fetch();
        return newname;
    }

	void NameData::badnamed()// if file failed to process naming convention
	{
			classname="bad";
			student="bad";
			problem="bad";
			searchtag=originalname;
			badname=true;		
	}

	