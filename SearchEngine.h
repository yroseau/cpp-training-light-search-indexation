#pragma once

#include "Analyzer.h"
#include "Map.h"

typedef ylib::Vector<const ylib::String* const> StringVector;

class SearchEngine
{

public:
	SearchEngine(const char* path);
	~SearchEngine();

	void analyze(Analyzer* analyzer, const char* fileExtension);
	void clearAnalyze();

	StringVector search(const char* term) const;

	inline const ylib::Vector<ylib::String>* const getPaths() const {
		return &m_paths;
	}

protected:
	const char* m_path;
	ylib::Vector<ylib::String> m_paths;
	ylib::Map<StringVector> m_tokens;
	ylib::Vector<Analyzer*> m_analyzers;

	void recursiveDirAnalyze(Analyzer* analyzer, const char* path, const char* fileExtension);
	void regularFileAnalyze(Analyzer* analyzer, const char* path);

};
