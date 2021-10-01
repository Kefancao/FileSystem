#include "filesystem.h"
#include <iostream> 

using std::cin; 
using std::cout; 
using std::endl; 

/* ====================== NOTE =====================

Dear Recruiter, 

Thank you for reading over this code, I have truly enjoyed 
writing this challenge. Please read the documentation.pdf 
for more information on how my program works and to see 
a list of commands if you haven't already! 

I look forward to talking in the future. 

Thanks, 
Kefan Cao 

====================================================*/ 


int main(){
	unsigned totalSize; 
	int blockSize; 

	totSize:
	cout << "Please specify the total size of the disk in MB: "; 

	// In case the user inputs an invalid value. 
	if (!(cin >> totalSize)){
		cin.clear(); 
		cin.ignore(); 
		cout << "Invalid size, please try again" << endl; 
		goto totSize; 
	}

	// In case the user inputs an value greater than 1TB of storage. 
	if (totalSize > 1048576){
		cout << "Total size of disk must be or under 1TB." << endl; 
		cout << "Please try again" << endl; 
		goto totSize; 
	}
	
	totalSize *= 1024;

	block:
	cout << "Please specify the size of each block in KB: "; 

	// In case the user decides to enter an invalid value. 
	if (!(cin >> blockSize)){
		cin.clear();
		cin.ignore(); 
		cout << "Invalid size, please try again" << endl; 
		goto block; 
	}
	
	// In case the user decides to input a block size that does not divide into the total 
	//    memory size. 
	if (totalSize % blockSize){
		cout << "The block size requested does not divide evenly into the disk memory." << endl;
		cout << "Some memory may be truncated if you continue." << endl; 
		cout << "Would you like to reconsider the block size? (y/n)" << endl; 
		char c; 
		cin >> c; 
		// A choice to allow the user to reconsider and enter a divisible block size. 
		if (c == 'y' || c == 'Y') goto block; 
	}

	FileSystem manager{totalSize, blockSize}; 

	// Actual file manager procedure. 
	manager.open(); 
}
