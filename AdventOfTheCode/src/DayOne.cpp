#include <string>
#include <fstream>
#include <iostream>

#include <vector>
#include <array>

#include "Timer.h"

void DayOneChallenge(std::string filepath)
{
	Timer timer;

	std::vector<int> calibNums;

	std::ifstream stream(filepath);

	std::string line;

	std::array<std::string, 10> numbers = 
	{
		"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
	};

	while (getline(stream, line))
	{
		int firstDigit = -1;
		int lastDigit = -1;

		struct Word
		{
			int index = -1;
			int value = -1;
		} foundWord;

		Word firstWord;
		Word lastWord;

		for (int i = 0; i < numbers.size(); i++)
		{			
			size_t found = std::string::npos;
			found = line.find(numbers[i]);
			if (found != std::string::npos)
			{
				if (firstWord.index == -1 || firstWord.index > found)
				{
					firstWord.index = found;
					firstWord.value = i;
				}
			}
		}

		{
			std::array<int, 10> str_indices_found;
			for (int i = 0; i < numbers.size(); i++)
			{
				size_t found = std::string::npos;
				int str_index = 0;
				while (str_index + numbers[i].size() < line.size())
				{					
					if (line.find(numbers[i], str_index) != std::string::npos)
					{
						found = line.find(numbers[i], str_index);
						str_index = found + numbers[i].size();
					}
					else
					{
						break;
					}
				}

				str_indices_found[i] = found;
			}

			
			for (int i = 0; i < str_indices_found.size(); i++)
			{				
				if (str_indices_found[i] > lastWord.index)
				{
					lastWord.index = str_indices_found[i];
					lastWord.value = i;
				}
			}
		}

		for (int i = 0; i < line.size(); i++)
		{
			if (i == firstWord.index)
			{
				firstDigit = firstWord.value;
				break;
			}
		
			if ((line[i] >= 48 && line[i] <= 57))
			{
				firstDigit = line[i] - 48;
				break;
			}
		}

		if (firstDigit != -1)
		{
			for (int i = line.size() - 1; i >= 0; i--)
			{
				if (i == lastWord.index)
				{
					lastDigit = lastWord.value;
					calibNums.push_back(firstDigit * 10 + lastDigit);
					break;
				}

				if (line[i] >= 48 && line[i] <= 57)
				{
					lastDigit = line[i] - 48;
					calibNums.push_back(firstDigit * 10 + lastDigit);

					break;
				}
			}
		}
	}

	int sumOfCalib = 0;
	for (int n : calibNums)
		sumOfCalib += n;
}