#include "bitMap.h"
#include "Exception.h"

BitMap::BitMap(int size): size{size}, free{size} {
	bitmap = vector<bool>(size, false); 
}


// Returns a list of memory of size n that are now occupied. 
vector<int> BitMap::getBlock(int blocks){
	// If there are no more room on the disk, then throw exception to caller. 
	if (blocks > free) throw NoRoomException{};

	// Iterate through the bitmap to find free memory.  
	vector<int> allocatedMem; // Contains the addresses of the blocks.

	for (int i = 0; i < size; ++i){
		if (!bitmap[i]){
			bitmap[i] = true; 
			allocatedMem.push_back(i); 
			
			if (allocatedMem.size() == blocks) break; 
		}
	}
	// Subtract the memory used from the total available memory. 
	free -= blocks; 
	return allocatedMem; 
	
}

void BitMap::freeBlock(vector<int> blocks){
	free += blocks.size(); 
	// Free each of the elements in the array as indices
	for (auto n : blocks){
		bitmap[n] = false; 
	}

}

int BitMap::availableSpace() noexcept{
	return free; 
}

