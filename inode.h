#ifndef __INODE_H__
#define __INODE_H__

#include <string> 
#include <vector> 
#include <memory> 

using std::shared_ptr; 
using std::make_shared; 
using std::string; 
using std::vector; 

class iNode{
	string fileID; 
	unsigned int size; // Size of the file.
	vector<int> locations; 
	shared_ptr<iNode> next; 

	public:
		iNode(string fileID, unsigned int size, vector<int> locations); 
		~iNode() = default; 

		// Returns the locations/addresses of a file. 
		vector<int> getLocations(); 
		// Returns the next iNode in the linked list.
		shared_ptr<iNode> getNext(); 
		// Sets the next iNode property of 'this'.
		void setNext(shared_ptr<iNode> next); 

		string getFileID(); 
		unsigned int getSize(); 

}; 

#endif
