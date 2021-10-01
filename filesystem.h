#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "disk.h"

class FileSystem{
	// Disk object storing all the files. 
	Disk disk; 

	public: 
		FileSystem(unsigned int totalSize, int blockSize);
		~FileSystem() = default;

		// The main loop for the file system manager. 
		void open(); 	
}; 

#endif
