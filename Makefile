all: build run

build: main.cpp PathHelper.cpp SearchEngine.cpp Analyzer.cpp Tokenizer.cpp String.cpp
	g++ -std=c++11 -Wall -o bin/lightSearch.exe $^

args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`
run:
	./bin/lightSearch.exe $(call args,defaultstring)
