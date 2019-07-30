#include "Parser.h"

Parser::Parser(const std::string & s)
	: m_string(s), m_delimeters({ ",", "\n" }), m_pos(0)
{}

Parser::Parser()
{}

Parser::~Parser()
{}

void Parser::getDelimeters()
{
	if (m_string.length() > 2 && m_string[0] == m_string[1] && m_string[0] == '/')
	{
		m_pos = 2;
		std::string delim = "";
		while (m_string[m_pos] != '\n')
		{
			if (m_string[m_pos] != '[' && m_string[m_pos] != ']')
				delim += m_string[m_pos];
			if (m_string[m_pos] == ']')
				if (delim.length())
				{
					m_delimeters.push_back(delim);
					delim = "";
				}
			++m_pos;
		}
		++m_pos;
	}
}

std::vector<int> Parser::Parse()
{
	if (m_string.length() == 0)
		return std::vector<int>{0};

	std::vector<int> ans;
	m_string = m_string.substr(m_pos);
	m_pos = 0;

	while (true)
	{
		size_t delim_num = 0;
		std::string substr = m_string.substr(0, m_string.find(m_delimeters[0]));

		for (size_t i = 1; i < m_delimeters.size(); ++i)
			if (m_string.substr(0, m_string.find(m_delimeters[i])).length() < substr.length())
			{
				substr = m_string.substr(0, m_string.find(m_delimeters[i]));
				delim_num = i;
			}
		ans.push_back(std::stoi(substr));
		std::string t_string = m_string;
		m_string = m_string.substr(m_string.find(m_delimeters[delim_num]) + m_delimeters[delim_num].length());
		if (t_string == m_string)
			break;
	}
	return ans;
}
