#ifndef __DISK_H__
#define __DISK_H__

#include <vector> 
#include <string> 
#include <memory> 
#include "bitMap.h"
#include "inode.h"

using std::vector; 
using std::string;
using std::make_shared; 
using std::shared_ptr;  

class Disk{
	// Vector of bools used to mark the population/occupancy. 
	BitMap blocks; 
	unsigned int totalSize; // in KB
	int blockSize; // in KB
	
	// Hash table containing information about the files. 
	vector<shared_ptr<iNode>> index_nodes;

	// Ensures file id supplied by a save action does not already exist. 
	bool validateFileID(string fileID); 

	public: 
		Disk(unsigned int totalSize = 0, int blockSize = 0); 
		~Disk() = default; 

		// Returns a vector of ints representing the blocks 'fileID' has been saved to. 
		vector<int> save(string fileID, unsigned int fileSize); 
		
		// Returns a vector of ints representing the blocks 'fileID' occupies.
		vector<int> read(string fileID); 

		// Erases 'fileID' from the disk.
		void del(string fileID); 

		// Returns the space available
		int availableSpace() noexcept;

		// Returns the totalSize 
		int getTotalSize() noexcept;

		// Lists the available files
		void listFiles() noexcept; 
}; 


#endif
