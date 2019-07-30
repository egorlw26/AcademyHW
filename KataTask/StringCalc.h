#pragma once
#include <string>
#include "Parser.h"

class StringCalc
{
public:
	StringCalc();
	~StringCalc();
	int Add(const std::string& i_string);
private:
	Parser* mp_parser;
};