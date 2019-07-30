#pragma once
#include <string>
#include <vector>

class Parser
{
public:
	Parser(const std::string& s);
	Parser();
	~Parser();
	void getDelimeters();
	std::vector<int> Parse();
private:
	std::vector<std::string> m_delimeters;
	size_t m_pos;
	std::string m_string;
};