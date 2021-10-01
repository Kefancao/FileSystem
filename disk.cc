#include "disk.h"
#include "bitMap.h"
#include "Exception.h"
#include <cmath>
#include <iostream> 

using std::cout; 
using std::endl;

Disk::Disk(unsigned int totalSize, int blockSize) : 
	totalSize{totalSize}, blockSize{blockSize}, index_nodes{nullptr}
{
	int totalBlocks = totalSize/blockSize; 
	blocks = BitMap(totalBlocks); 

	// Note that this is a hash table and the number 10 is used for modulo hash codes 
	index_nodes = vector<shared_ptr<iNode>>(10, nullptr);
}

// Provides strong exception guarantee, the state is unaltered if exception is thrown. 
vector<int> Disk::save(string fileID, unsigned int fileSize){
	int hashCode = fileID[0] % 10;
	
	// Makes the assumption that fileSize and blockSize are in the same unit. 
	int blocksNeeded = ceil((float)fileSize/(float)blockSize); 

	// If a match is found, then throw DuplicateFileException to indicate this fiel exists already.
	// 		Validation of fileID essentially. 
	try{
		read(fileID); 
		throw DuplicateFileException{}; 
	} catch (NoMatchException&){}

	// May throw a NoRoomException if blocksNeeded > freespace, caught by caller. 
	vector<int> locations = blocks.getBlock(blocksNeeded); 

	shared_ptr<iNode> target = make_shared<iNode>(fileID, fileSize, locations); 
	shared_ptr<iNode> hashedNode = index_nodes[hashCode]; 

	// Cons the new index node to the hashed index of the vector. 
	target->setNext(hashedNode); 
	index_nodes[hashCode] = target; 

	return locations; 
}

// Read the fileID if it exists, throws NoMatchException if not. Strong exception guarantee. 
vector<int> Disk::read(string fileID){
	int hashCode = fileID[0] % 10; 

	shared_ptr<iNode> targetNode = index_nodes[hashCode]; 

	// Search for the fileID in hashTable. 
	for (; targetNode; targetNode = targetNode->getNext()){
		if (fileID == targetNode->getFileID()){
			return targetNode->getLocations(); 
		}
	}

	throw NoMatchException{}; 
}

// Delete fileID if it exists, throws NoMatchException if not. Strong exception guarantee. 
void Disk::del(string fileID){
	int hashCode = fileID[0] % 10; 

	shared_ptr<iNode> targetNode = index_nodes[hashCode]; 
	shared_ptr<iNode> prev = targetNode;

	// If the hash doesn't contain anything, no match is found, throw. 
	if (!prev) throw NoMatchException{}; 

	targetNode = targetNode->getNext(); 
	if (prev->getFileID() == fileID){
		blocks.freeBlock(prev->getLocations()); 
		index_nodes[hashCode] = prev->getNext();
		// Deleted node is freed as it runs off of the stack because of the shared_ptr. 
		return;  
	}

	// Advances the prev and targetNode until a match is found. 
	for (; targetNode; prev = targetNode, targetNode = targetNode->getNext()){ 
		if (targetNode->getFileID() == fileID){
			blocks.freeBlock(targetNode->getLocations()); 
			prev->setNext(targetNode->getNext()); 
			// As before, deleted node is freed because of shared_ptr. 
			return; 
		}
	}

	// If no matches found, then the fileID provided is invalid.
	throw NoMatchException{}; 
}

int Disk::availableSpace() noexcept{
	return blocks.availableSpace() * blockSize; 
}

int Disk::getTotalSize() noexcept{
	return totalSize; 
}

void Disk::listFiles() noexcept{
	// Indentation lines 
	cout << string(20, '=') << endl; 

	for (size_t i = 0; i < index_nodes.size(); ++i){
		// Traverse the hashtable for the files
		for (shared_ptr<iNode> temp = index_nodes[i]; temp; temp = temp->getNext()){
			// Print the file id along with the size 
			cout << temp->getFileID() << " (" << temp->getSize() << "KB)" << endl; 
		}
	}

	cout << string(20, '=') << endl; 
}
