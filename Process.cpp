#include "Process.h"

//This default constructor begins the program. It allocates dynamic memory and redirects the output from created processes to a buffer.
ProcessRunner::ProcessRunner()
{
	//Creates necessary variables for CreateProcess and redirects its output to a text file.
	prepare();
}

void ProcessRunner::prepare()
{

	//Necessary variable for CreateProcess.
	si = new STARTUPINFOA;
	pi = new PROCESS_INFORMATION;
	//Sets the values for si and pi to 0. Also sets some of the values within si.
	SetZero();

	//Preparing handles used to redirect output from CreateProcess.
	handOutRead = NULL;
	handOutWrite = NULL;
	SetHandleInformation(handOutRead, HANDLE_FLAG_INHERIT, 0);

	//This is where the output is actually redirected
	secAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	secAttr.bInheritHandle = TRUE;
	secAttr.lpSecurityDescriptor = NULL;
	//Create a pipe for the child process's STDOUT. This is a buffer that the text is written to.
	CreatePipe(&(handOutRead), &(handOutWrite), &(secAttr), 0);
	SetHandleInformation(&(handOutRead), HANDLE_FLAG_INHERIT, 0);
	si->hStdError = handOutWrite;
	si->hStdOutput = handOutWrite;
}

ProcessRunner::~ProcessRunner()
{
	//Clearing memory and making sure the handle is no longer used.
	CloseHandle(pi->hProcess);
	CloseHandle(pi->hThread);
	delete si;
	delete pi;
}

void ProcessRunner::SetZero()
{
	//Sets the memory si points to to 0.
	ZeroMemory(si, sizeof(*si));
	si->cb = sizeof(*si);
	//Sets the memory pi points to to 0.
	ZeroMemory(pi, sizeof(*pi));
	//Sets the startup information to have a preset set of flags in the dwFlags section.
	si->dwFlags |= STARTF_USESTDHANDLES;
}

void ProcessRunner::runFileError(LPSTR* execute, string output)
{
	//Gives output that tells an error occured.
	ofstream Error;
	Error.open(output, ios::out | ios::app );
	Error << "\n\n----------------------------------------\n\nFile " << FileName << " exceeded maximum run time.";
	Error.close();
	//Sends the output to a text file named <output>. The parameters are the full path to the file 
	//and the name of the text file that the output is going to.
	fileOutput(execute, output);
	Error.open(output, ios::out | ios::app );
	Error << "\n\n----------------------------------------\n\n";
	Error.close();
}

void ProcessRunner::fileOutput(LPSTR* execute, string output)
{
	//dwRead is a count of the number of characters that have been redirected to a buffer.
	DWORD dwRead, dwWritten;
	//Size of buffer established here.
	CHAR chBuf[12000];
	//Establishes a handle for the output of the created process.
	HANDLE handyPar = GetStdHandle(STD_OUTPUT_HANDLE);
	//Reads the output into a buffer.
	ReadFile(handOutRead, chBuf, 12000, &dwRead, NULL);

	ofstream Output;
	//Makes the output appended rather than overwrite it.
	Output.open(output, ios::out | ios::app );
	//Writes the output to chbuf.
	WriteFile(handyPar, chBuf, dwRead, &dwWritten, NULL);
	//Beginning of output.
    Output << "\n\nFile: " << FileName << "\n----------------------------------------------------------\n\n";
	//This loop sends all of the characters in the buffer to a text file.
	for (int x = 0; x < dwRead; x++)
	{
		Output << chBuf[x];
	}
	//End of output.
	Output << "\n----------------------------------------------------------";
	Output.close();
}

CplusplusRunner::CplusplusRunner(string dirname, string LFile, string output)
{
	//This variable is used to keep the original file name.
	FileName = LFile;
	LPSTR LPfilename=	const_cast<LPSTR>(LFile.c_str());
	string path;
	path.append(dirname);
	path.append("\\");
	path.append(LFile);
	path.append(".exe");
	LPSTR Cpath = const_cast<LPSTR>(path.c_str());
	if(!strncmp(LFile.c_str(),"cs132_austin_ch14_15",MAX_PATH))
		cout << "Austin!!!";

	//RunProcess will return 0 if the file finishes running before the timer expires. Otherwise, it will return 1.
	//Parameter is the full path to the file. This version is for executables.
	if(RunProcess(Cpath))
	{
		//Adds a little bit before and after the output to signify that an error occured and then calls fileOutput(). The parameters are the full path to the file 
		//and the name of the text file that the output is going to.
		runFileError(&LPfilename, output);
	}
	else
	{
		//Sends the output to a text file named <output>. The parameters are the full path to the file 
		//and the name of the text file that the output is going to.
		fileOutput(&LPfilename, output);
	}
}

unsigned short int CplusplusRunner::RunProcess(LPSTR lpFileName)
{

		//Creates the process. The full path of the executable file is <lpFileName>.
		CreateProcessA(NULL,lpFileName, NULL, NULL, TRUE, NULL, NULL, NULL, si, pi);
		if(WaitForSingleObject(pi->hProcess, 5000))
		{
			cout << "\n\nProblem with file. " << FileName << endl << endl;
			TerminateProcess(pi->hProcess, 0);
			RunProcessT();
			return 1;
		}
		TerminateProcess(pi->hProcess, 0);
		return 0;
}

JavaRunner::JavaRunner(string dirname, string LFile, string output)
{
	//This variable is used to keep the original file name.
	LPSTR LPfilename=	const_cast<LPSTR>(LFile.c_str());
	string path="-classpath ";
	path.append(dirname);
	path.append(" ");
	path.append("ArrayBasedDataStructuresDriver");
	LPSTR Jpath = const_cast<LPSTR>(path.c_str());
	cout << Jpath;
	FileName = LFile;

	//RunProcess will return 0 if the file finishes running before the timer expires. Otherwise, it will return 1.
	//Parameter is the full path to the file. This version is for executables.
	if(RunProcess(Jpath))
	{
		//Adds a little bit before and after the output to signify that an error occured and then calls fileOutput(). The parameters are the full path to the file 
		//and the name of the text file that the output is going to.
		runFileError(&LPfilename, output);
	}
	else
	{
		//Sends the output to a text file named <output>. The parameters are the full path to the file 
		//and the name of the text file that the output is going to.
		fileOutput(&LPfilename, output);
	}
}

unsigned short int JavaRunner::RunProcess(LPSTR lpFileName)
{
		//Creates the process. placeHolder -classpath <path> <FileName> is the final contents of <lpFileName>.
		//CreateProcessA("C:\\Program Files\\Java\\jdk1.8.0_65\\bin\\java.exe", lpFileName, NULL, NULL, TRUE, NULL, NULL, NULL, si, pi);
	cout << "commandPrompt> " << lpFileName << endl;
		CreateProcessA("Java", lpFileName, NULL, NULL, TRUE, NULL, NULL, NULL, si, pi);
		//if(WaitForSingleObject(pi->hProcess, 5000000000))
		//{
		//	cout <<"\nProblem with file. " << FileName << endl;

			//TerminateProcess(pi->hProcess, 0);
		//	RunProcessT();
		//	return 1;
		//}
		//TerminateProcess(pi->hProcess, 0);
		return 0;
}

void ProcessRunner::RunProcessT()
{

		//Creates the process. The full path of the executable file is <lpFileName>.
		CreateProcessA(NULL,"T.exe", NULL, NULL, TRUE, NULL, NULL, NULL, si, pi);
		if(WaitForSingleObject(pi->hProcess, 1000))
		{
			TerminateProcess(pi->hProcess, 0);
			
		}
		TerminateProcess(pi->hProcess, 0);
}