#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <vector> 

using std::vector; 

class BitMap{
	vector<bool> bitmap; 
	int size; 
	int free;	// Denotes the total number of blocks marked false. 

	public: 
		BitMap(int size = 1); 
		~BitMap() = default; 

		// getBlock(blocks) Makes the assumption that the free blocks returned
		//   will now become occupied
		vector<int> getBlock(int blocks);

		// freeBlock(blocks) frees blocks at the supplied indices. 
		void freeBlock(vector<int> blocks);

		// Returns the 'free' variable. 
		int availableSpace() noexcept; 
}; 

#endif 
