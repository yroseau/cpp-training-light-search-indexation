#include <iostream>
#include <time.h>
#include <string.h>

#include "PathHelper.h"
#include "SearchEngine.h"
#include "Analyzer.h"
#include "Tokenizer.h"

#include "String.h"
#include "Vector.h"
#include "Map.h"

#define ARGC_REQUIRED 2

inline bool haveValidArgsNumber(int argc) {
	return argc == ARGC_REQUIRED;
}

inline char* getPath(char *argv[]) {
	return argv[1];
}

inline void displayAppName() {
	std::cout << "" << std::endl; 
	std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "                                                                                                             " << std::endl;
	std::cout << " _     _       _     _     ____                                        _     ____                      _     " << std::endl;
	std::cout << "| |   (_) __ _| |__ | |_  |  _ \\  ___   ___ _   _ _ __ ___   ___ _ __ | |_  / ___|  ___  __ _ _ __ ___| |__  " << std::endl;
	std::cout << "| |   | |/ _` | '_ \\| __| | | | |/ _ \\ / __| | | | '_ ` _ \\ / _ \\ '_ \\| __| \\___ \\ / _ \\/ _` | '__/ __| '_ \\ " << std::endl;
	std::cout << "| |___| | (_| | | | | |_  | |_| | (_) | (__| |_| | | | | | |  __/ | | | |_   ___) |  __/ (_| | | | (__| | | |" << std::endl;
	std::cout << "|_____|_|\\__, |_| |_|\\__| |____/ \\___/ \\___|\\__,_|_| |_| |_|\\___|_| |_|\\__| |____/ \\___|\\__,_|_|  \\___|_| |_|" << std::endl;
	std::cout << "         |___/                                                                                               " << std::endl;
	std::cout << "                                                                                                             " << std::endl;
	std::cout << "-------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "" << std::endl;
}

void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

template class ylib::Vector<ylib::String>;

int main(int argc, char *argv[]) {

	// Display app informations
	displayAppName();
	std::cout << "Author: yroseau" << std::endl;
	std::cout << "Licence MIT" << std::endl;
	std::cout << "v0.0.1" << std::endl;
	std::cout << "" << std::endl;
	
	// check args number (argc)
	if (!haveValidArgsNumber(argc)) {
		std::cout << "[ERROR] Invalid args number. Required: " << ARGC_REQUIRED << " - Got: " << argc << std::endl;
		for (int i = 0; i != argc; ++i) {
			std::cout << i << ": " << argv[i] << std::endl;
		}
		return 0;
	}

	// get path in argv
	char* path = getPath(argv);

	// check path is a valid directory
	if (!PathHelper::isDir(path)) {
		std::cout << "[ERROR] '" << path << "' is not a valid directory !" << std::endl;
		return 0;
	}

	std::cout << "Directory: " << path << std::endl;

	Tokenizer *tokenizer = new Tokenizer();
	Analyzer *analyzer = new Analyzer(tokenizer);
	//Analyzer *analyzer = new ExtensionAnalyzer(tokenizer, '.txt');

	SearchEngine *searchEngine = new SearchEngine(path);
	searchEngine->analyze(analyzer, ".TXT");
	searchEngine->analyze(analyzer, ".txt");

	std::cout << "Search engine has indexed " << searchEngine->getPaths()->size() << " document(s)." << std::endl;

	const char* stopWord = ":q";
	std::cout << "\nWrite '" << stopWord << "' to quit." << std::endl;
	
	char term[1024];
	do {

		std::cin >> term;

		if (strcmp(term, stopWord) == 0) {
			continue;
		}

		std::cout << "\nTerm to search: " << term << std::endl;
		StringVector result = searchEngine->search(term);
		std::cout << "  Find " << result.size() << " result(s)." << std::endl;
		for (ylib::size_t i = 0; i != result.size(); ++i) {
			std::cout << "    - " << (*result[i])->toCharArray() << std::endl;
		}

	} while (strcmp(term, stopWord) != 0);

	return 0;
}
