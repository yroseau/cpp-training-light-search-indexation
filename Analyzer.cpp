#include "Analyzer.h"

Analyzer::Analyzer(Tokenizer* tokenizer) : m_tokenizer(tokenizer)
{

}

Analyzer::~Analyzer()
{
}

ylib::Vector<ylib::String> Analyzer::analyze(const char* str) {

	// @todo apply some filters on str

	return m_tokenizer->getTokens(str);

}
