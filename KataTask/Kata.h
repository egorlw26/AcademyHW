#pragma once

#include <string>
#include <vector>

int Add(const std::string& input)
{
	if (input.length() < 3)
		return 0;
	int ans = 0;
	std::string number = "";
	std::vector<int> negatives = {};
	std::string numbers = "0123456789";
	bool negative = false;

	size_t pos = 2;
	while (input[pos] != '\n')
	{
		++pos;
	}
	++pos;

	for (size_t i = pos; i < input.length(); ++i)
	{
		if (input[i] == '-')
		{
			negative = true;
			continue;
		}

		if (find(numbers.begin(), numbers.end(), input[i]) != numbers.end())
			number += input[i];
		else
			if (!negative && number.length() < 4)
			{
				if (number.length() != 0)
					ans += std::stoi(number);
				number = "";
				negative = false;
			}
			else
				negatives.push_back(-std::stoi(number));
	}

	if (number.length() != 0 && number.length() < 4)
		if (!negative)
			ans += std::stoi(number);
		else
			negatives.push_back(-std::stoi(number));

	if (negatives.size() != 0)
	{
		std::string message = "Negative numbers found: ";
		for (int i : negatives)
			message += std::to_string(i) + ", ";
		throw std::string(message);
	}

	return ans;
}

// //[delims]\n[numbers]