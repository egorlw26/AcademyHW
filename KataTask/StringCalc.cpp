#include "StringCalc.h"

StringCalc::StringCalc()
	: mp_parser(nullptr)
{}

StringCalc::~StringCalc()
{
	if (mp_parser != nullptr)
		delete mp_parser;
}

int StringCalc::Add(const std::string & i_string)
{
	mp_parser = new Parser(i_string);
	mp_parser->getDelimeters();
	std::vector<int> negatives;
	std::vector<int> parsed = mp_parser->Parse();
	int ans = 0;
	for (int val : parsed)
	{
		if (val < 0)
		{
			negatives.push_back(val);
			continue;
		}
		if (val > 1000)
			continue;
		ans += val;
	}
	
	if (negatives.size() != 0)
	{
		std::string message = "Negative numbers found: ";
		for (int val : negatives)
			message += std::to_string(val);
		throw std::exception(message.c_str());
	}

	return ans;
}
