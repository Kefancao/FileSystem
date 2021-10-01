#include "inode.h"

iNode::iNode(string fileID, unsigned int size, vector<int> locations): 
	fileID{fileID}, size{size}, locations{locations}, next{nullptr} {}


vector<int> iNode::getLocations(){
	return locations; 
}

shared_ptr<iNode> iNode::getNext(){
	return next; 
}

void iNode::setNext(shared_ptr<iNode> _next){
	next = _next; 
}

string iNode::getFileID(){
	return fileID; 
}

unsigned int iNode::getSize(){
	return size; 
}
