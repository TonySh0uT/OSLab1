#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <stdarg.h>
#include <algorithm>




bool searchFunc(const std::string& substr,const std::string& sourceString) {
	size_t position = sourceString.find(substr);
	if (position != std::string::npos)
		return true;
		return false;
}


std::list<std::string> searchInFiles(bool(*)(const std::string&,const std::string&), const std::string& substr, int filesCount,...) {

	va_list args;
	std::list<std::string> result;
	va_start(args, filesCount);
	for (int i = 0; i < filesCount; i++)
	{
		std::string searchFileName = va_arg(args, char*);
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
		}
		inputFile.close();
	}
	va_end(args);
	return result;
}







int main()
{
	std::list<std::string> result = searchInFiles(searchFunc, std::string(" "), 3, (char*)"1", (char*)"2", (char*)"3");
	for (std::string resultElem : result) {
		std::cout << resultElem << "\t";
	}





	return 0;
}
