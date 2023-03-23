#include "FileManager.h"

const std::string FileManager::ERR_OPEN = "Failure while opening the file. Make sure the path to the file is correct" ;
const std::string FileManager::ERR_CLOSE = "Failure while closing the file -> The file is not open";
const std::string FileManager::ERR_LOAD = "Failure while loading the file. Make sure the file has a correct format";;

FileManager ::FileManager(const std::string& fileName):filePath(fileName){
	
	try
	{
		file = std::ifstream(filePath);
	}
	catch (...)
	{
		throw Exception(ERR_OPEN);
	}
}


std::vector<std::string> FileManager::load() 
{
	if (!file.is_open())
	{
		throw Exception(ERR_OPEN);
		return {};
	}

	std::vector<std::string> lines;
	std::string line;
	try
	{
		while (std::getline(file, line))
		{
			lines.push_back(line);
		}
	}
	catch (...)
	{
		throw Exception(ERR_LOAD);
	}

	if(lines.size()<1) throw Exception(ERR_LOAD);

	return lines;
}

void FileManager::close() {

	if (!file.is_open())
	{
		throw Exception(ERR_CLOSE);
		return;
	}

	file.close();
}
