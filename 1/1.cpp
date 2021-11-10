#include <iostream>
#include <stdarg.h>
#include <string>
#include <list>
#include <fstream>
#include <cstdarg>
#include <algorithm>




bool searchFunc(const std::string& substr,const std::string& sourceString) {
	size_t position = sourceString.find(substr);
	if (position != std::string::npos)
		return true;
		std::cout << position;
		return false;
}


std::list<std::string> searchInFiles(bool(*)(const std::string&,const std::string&), const std::string& substr, int filesCount, char* fileName,...) {

	std::va_list args;
	std::list<std::string> result;
	va_start(args, fileName);
	std::string searchFileName = fileName;
	for (int i = 0; i < filesCount; i++)
	{
		std::string buffer;
		std::string wholeFile;
		std::ifstream inputFile(searchFileName);
		if (inputFile.is_open()) {
			
			while (std::getline(inputFile, buffer))
			{
				wholeFile += buffer;
				wholeFile.push_back('\n');
			}
			if (searchFunc(substr, wholeFile)) {
				result.push_back(searchFileName);
			}
			std::string searchFileName = va_arg(args, std::string);
		}
	}
	va_end(args);
	return result;
}







int main()
{
	std::list<std::string> result = searchInFiles(searchFunc, std::string(" "), 3, (char*)"1", "2", "3");
	for (std::string resultElem : result) {
		std::cout << resultElem << "\t";
	}





	return 0;
}
