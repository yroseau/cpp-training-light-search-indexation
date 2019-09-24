#pragma once
class PathHelper
{
public:
	PathHelper();
	~PathHelper();

	static bool isValidPath(const char* path);
	static bool isDir(const char* path);
	static bool isFile(const char* path);

	static char* getEntryPath(const char* path, const char* entry);

};

