#include "PathHelper.h"

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

PathHelper::PathHelper()
{
}

PathHelper::~PathHelper()
{
}

bool PathHelper::isValidPath(const char* path) {

	return PathHelper::isDir(path) || PathHelper::isFile(path);

}

bool PathHelper::isDir(const char* path) {

	DIR * dir = opendir(path);

	if (dir != nullptr) {
		if (closedir(dir) != 0) {
			std::cout << "[ERROR] The directory '" << path << "' was not closed !" << std::endl;
		}
		return true;
	}
	else {
		return false;
	}
}

bool PathHelper::isFile(const char* path) {

	FILE* file;

	#ifdef __cplusplus
		file = fopen(path, "r");
		bool isOpen = (file != nullptr);
	#else
		errno_t err = fopen_s(&file, path, "r");
		bool isOpen = (err == 0);
	#endif

	if (isOpen) {
		if (fclose(file) != 0) {
			std::cout << "[ERROR] The file '" << path << "' was not closed !" << std::endl;
		}
		return true;
	}
	else {
		return false;
	}

}

char* PathHelper::getEntryPath(const char* path, const char* entry) {
	char *entryPath = (char*)malloc(sizeof(char)*(strlen(path) + strlen(entry) + 2));
	strcpy(entryPath, path);
	strcat(entryPath, "/");
	strcat(entryPath, entry);
	return entryPath;
}
