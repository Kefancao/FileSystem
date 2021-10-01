#include "filesystem.h"
#include "Exception.h"
#include <iostream> 
#include <cmath> 

using std::cout; 
using std::cin; 
using std::endl; 

void printLocations(vector<int> locations){
	cout << "[" << endl << " "; 
	for (size_t i = 0; i < locations.size()-1; ++i){
		// Some whitespace indent for visual purposes. 
		if (i % 5 == 0 && i) cout << endl << " "; 

		// Print the actual content here.
		cout << locations[i] << ", "; 
	}
	cout << locations[locations.size()-1] << endl << "]" << endl; 
	cout << "Total Blocks: " << locations.size() << endl << endl; 
}

FileSystem::FileSystem(unsigned int totalSize, int blockSize): disk{totalSize, blockSize}{}

void FileSystem::open(){
	// Input exception.
	cin.exceptions(std::ios::eofbit|std::ios::failbit);
	
	// Variables for use 
	char option; 
	string fileID; 
	unsigned int fileSize;
	float availableMem, totalMem; 
	vector<int> locations; 

	while (true){
		// Welcome screen. 
		cout << "Please select from one of the three options below" << endl; 
		cout << " - save (s)" << endl; 
		cout << " - read (r)" << endl; 
		cout << " - delete (d)" << endl; 
		cout << " - room (x)" << endl;
		cout << " - list (l)" << endl; 
		cout << " - quit (q)" << endl; 

		try{
			// Letter option. 
			cin >> option; 

			switch (option){
				// Saving a file given its fileID and size in KB
				case 's': 
					cout << "Please enter a file id to be saved: "; 
					cin >> fileID; 

					sizeEntry: 
					cout << "Please enter the file size in KB: " << endl;

					// In the case where the user inputs an invalid case.  
					try{
						cin >> fileSize; 

						// If the file doesn't exist, then it is not store. 
						if (!fileSize) break; 
						
					} catch (std::ios::failure&){
						cout << "Invalid Size, please try again!" << endl; 
						cin.clear(); 
						cin.ignore(); 
						goto sizeEntry;
					}

					// Try & catch for when there are no room for a file this big 
					try{
						printLocations(disk.save(fileID, fileSize));
					} catch (NoRoomException&){
						cout << "File storage failed. Not enough room, please try with a smaller file" << endl; 
						cout << "To see how much room is available, use the command \'room\'." << endl; 
					} catch (DuplicateFileException&){
						cout << "File storage failed. A file with id \'" << fileID << "\' already exists." << endl; 
						cout << "Please change the file id to be a different id." << endl; 
						cout << "To see the file ids, use the command \'list\'." << endl; 
					}

					break; 

				// Read only case 
				case 'r': 
					cout << "Please enter a file id to be read: "; 
					cin >> fileID; 

					// Try reading the fileID from disk, catch a NoMatchException when none are found. 
					try{
						printLocations(disk.read(fileID)); 
					} catch (NoMatchException&){
						cout << "This file id does not exist in the file system" << endl; 
						cout << "To see the file ids, use the list command \'l\'." << endl; 
					}
					break; 

				break; 

				// Deletion case 
				case 'd': 
					cout << "Please enter a file id to be deleted: "; 
					cin >> fileID; 
					
					// Try deleting a fileID from disk, but if none exist, exception is caught. 
					try{
						disk.del(fileID); 
					} catch (NoMatchException&){
						cout << "This file id does not exist in the file system" << endl; 
						cout << "To see the file ids, use the list command \'l\'." << endl; 
						break; 
					}

					cout << "File \'" << fileID << "\' has been deleted" << endl; 

					break; 

				case 'x': 

					// Calculate the available memory in MB.
					availableMem = (float)disk.availableSpace() / (float) 1024; 
					totalMem = (float)disk.getTotalSize() / (float) 1024; 

					cout << "The available memory is " << round(availableMem * 100)/(float)100 << "MB." << endl; 
					cout << "The total memory is " << round(totalMem * 100) / (float) 100 << "MB." << endl; 
					break; 

				case 'l': 
					// Lists all available files along with their size in KB 
					disk.listFiles(); 
					break; 

				case 'q': 
					return; 

				default: 
					cout << "Invalid selection, please select again" << endl; 
					break; 

			}
		} catch (std::ios::failure&){
			return; 
		}

	}
}
