#ifndef FileManager_H
#define FileManager_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Exception.h"
class  FileManager
{
public:
	
	static const std::string ERR_OPEN;
	static const std::string ERR_CLOSE;
	static const std::string ERR_LOAD;

	FileManager(const std::string& fileName);

	std::vector<std::string> load() ;
	void close();
 
private:
	std::string filePath;
	std::ifstream file;

	
};
#endif
//random device