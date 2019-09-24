#include "Tokenizer.h"

#include <iostream>
#include <string.h>

Tokenizer::Tokenizer()
{
}


Tokenizer::~Tokenizer()
{
}

ylib::Vector<ylib::String> Tokenizer::getTokens(const char* str) {

	int i = 0;

	ylib::Vector<ylib::String> tokens;

	char c;
	char *token;
	const char *startPointer;
	size_t size = 0;
	while ((c = str[i]) != '\0' && c != EOF) {
		if (isspace(c)) {
			if (size != 0) {
				token = (char*)malloc(sizeof(char)*(size+1));
				strncpy(token, startPointer, size);
				token[size] = '\0';
				tokens += token;
				size = 0;
			}
		}
		else {
			if (size == 0) {
				startPointer = &str[i];
			}
			++size;
		}
		++i;
	}

	if (size != 0) {
		token = (char*)malloc(sizeof(char)*(size + 1)); 
		strncpy(token, startPointer, size);
		token[size] = '\0';
		tokens += token;
	}

	return tokens;

}