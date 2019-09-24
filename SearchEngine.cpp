#include "SearchEngine.h"

#include "PathHelper.h"
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <algorithm>

//SearchEngine::SearchEngine(ylib::String& path) : m_path(path.toCharArray())
//{
//
//}

SearchEngine::SearchEngine(const char* path) : m_path(path)
{

}

SearchEngine::~SearchEngine()
{
	// clearAnalyze(); // not required, will be clear on respective destructors
}

void SearchEngine::clearAnalyze() {

	m_tokens.clear();
	m_paths.clear();
	m_analyzers.clear();

}

StringVector SearchEngine::search(const char* term) const {

	ylib::Vector<ylib::String> tokens;
	
	for (ylib::size_t i = 0; i != m_analyzers.size(); ++i) {
		tokens.mergeUnique((*m_analyzers[i])->analyze(term));
	}

	StringVector result;

	for (ylib::size_t i = 0; i != tokens.size(); ++i) {

		StringVector* paths = m_tokens.getValue(*tokens[i]);
		if (paths != nullptr) {
			result.mergeUnique(*paths);
		}

	}

	return result;

}

void SearchEngine::analyze(Analyzer* analyzer, const char* fileExtension) {

	m_analyzers.add(analyzer);
	this->recursiveDirAnalyze(analyzer, m_path, fileExtension);
	
}

void SearchEngine::recursiveDirAnalyze(Analyzer* analyzer, const char* path, const char* fileExtension) {

	DIR * dir = opendir(path);
	struct dirent *entry;

	if (dir == nullptr) {
		std::cout << "[ERROR] Impossible to open directory '" << path << "' !" << std::endl;
		return;
	}

	// std::cout << "[INFO] Analyze directory: " << path << std::endl;

	while ((entry = readdir(dir)) != nullptr)
	{

		switch (entry->d_type) {
			case DT_BLK: // block device
				std::cout << "[INFO] block device skipped: " << entry->d_name << std::endl;
				break;
			case DT_CHR: // character device
				std::cout << "[INFO] character device skipped: " << entry->d_name << std::endl;
				break;
			case DT_DIR: // directory
				if (
					strcmp(entry->d_name, ".") != 0 &&
					strcmp(entry->d_name, "..") != 0
				) {
					char *entryPath = PathHelper::getEntryPath(path, entry->d_name);
					this->recursiveDirAnalyze(analyzer, entryPath, fileExtension); // @todo analyze in new thread ?? improve performance for big entries
					free(entryPath);
				}
				break;
			case DT_FIFO: // named pipe (FIFO)
				std::cout << "[INFO]  named pipe (FIFO) skipped: " << entry->d_name << std::endl;
				break;
			case DT_REG: // regular file
				ylib::String fileName(entry->d_name);
				if (fileName.finishWith(fileExtension) == 0) {
					char *entryPath = PathHelper::getEntryPath(path, entry->d_name);
					this->regularFileAnalyze(analyzer, entryPath);
					free(entryPath);
				}
				break;
		}

	}

	if (closedir(dir) != 0) {
		std::cout << "[ERROR] The directory '" << path << "' was not closed !" << std::endl;
	}

}

void SearchEngine::regularFileAnalyze(Analyzer* analyzer, const char* path) {

	FILE* file;

	// @todo use ifstream.open ??
	// open file
	#ifdef __cplusplus
		file = fopen(path, "r");
		bool isOpen = (file != nullptr);
	#else	
		errno_t err = fopen_s(&file, path, "r");
		bool isOpen = (err == 0);
	#endif

	if (!isOpen) {
		std::cout << "[ERROR] Impossible to open file '" << path << "' !" << std::endl;
		return;
	}

	// obtain file size
	fseek(file, 0, SEEK_END);
	long lSize = ftell(file);
	rewind(file);

	// allocate memory to contain the whole file
	char *buffer = (char*)malloc(sizeof(char)*lSize);
	if (buffer == NULL) {
		std::cout << "[ERROR] Impossible to allocate memory !" << std::endl;
		return;
	}

	// copy the file into the buffer
	size_t result = fread(buffer, 1, lSize, file);
	if (result != static_cast<size_t>(lSize)) {
		std::cout << "[ERROR] Impossible to read file '" << path << "' !" << std::endl;
		return;
	}

	ylib::Vector<ylib::String> tokens = analyzer->analyze(buffer);

	// stop if no token found
	if (tokens.size() == 0) {
		return;
	}

	// get or add path
	ylib::String stringPath(path);
	ylib::usize_t pathPosition = m_paths.find(stringPath);
	if (pathPosition == -1) {
		pathPosition = m_paths.size();
		m_paths.add(stringPath);
	}

	for (size_t i = 0; i < tokens.size(); ++i) {

		ylib::String* token = tokens[i];
		
		// search token
		StringVector* tokenPaths = m_tokens.getValue(*token);
		// add token if not exists
		if (tokenPaths == nullptr) {
			StringVector v;
			m_tokens.add(*token, v);
			tokenPaths = m_tokens.last();
		}

		// add path in token list if not exists
		if (tokenPaths->find(m_paths[pathPosition]) == -1) {
			tokenPaths->add(m_paths[pathPosition]);
		}

	}

	// close file
	if (fclose(file) != 0) {
		std::cout << "[ERROR] The file '" << path << "' was not closed !" << std::endl;
	}

	free(buffer);

}
