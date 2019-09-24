#pragma once

#include "String.h"
#include "Vector.h"

class Tokenizer
{
public:
	Tokenizer();
	~Tokenizer();

	ylib::Vector<ylib::String> getTokens(const char* str);
};
