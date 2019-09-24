#pragma once

#include "Tokenizer.h"

class Analyzer
{
public:
	Analyzer(Tokenizer* tokenizer);
	~Analyzer();

	ylib::Vector<ylib::String> analyze(const char* str);

protected:
	Tokenizer* m_tokenizer;
};

