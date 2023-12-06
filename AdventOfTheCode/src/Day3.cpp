#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <vector>

#include "Timer.h"

void DayThreeChallenge(const std::string& filepath)
{
	Timer timer;
	std::ifstream stream(filepath);
	std::stringstream ss;
	std::string line;

	while (getline(stream, line))
	{
		ss << line;
	}
	const std::string& input = ss.str();
	int width = line.size();

	int i = 0;
	int sumOfPartsNumber = 0;
	int sumOfGearRatio = 0;

	struct StoredData
	{
		int gearIndex = -1;
		int number = -1;
	};
	
	std::vector<StoredData> storedData;

	while (i < input.size())
	{
		if (std::isdigit(input[i]))
		{
			int firstDigitIndex = i;
			while (std::isdigit(input[i]))
			{
				i++;
			}
			int lastDigitIndex = i - 1;

			int adjBoxWidth = (lastDigitIndex - firstDigitIndex) + 3;
			int adjBoxHeight = (firstDigitIndex - width < 0 || firstDigitIndex + width > input.size()) ? 2 : 3;

			int start = firstDigitIndex - width - 1;
			if (start < 0)
			{
				start += width;
				if (start < 0)
				{
					start++;
					adjBoxWidth = (lastDigitIndex - firstDigitIndex) + 2;
				}
			}

			
			for (int y = 0; y < adjBoxHeight; y++)
			{
				for (int x = 0; x < adjBoxWidth; x++)
				{
					// Part 1
					if (input[start + ((y * width) + x)] != '.' && !std::isdigit(input[start + ((y * width) + x)]))
					{
						std::string strNumber = "";
						for (int j = firstDigitIndex; j <= lastDigitIndex; j++)
							strNumber += input[j];

						int number = std::stoi(strNumber);

						// Part 2
						if (input[start + ((y * width) + x)] == '*')
						{
							for (int k = 0; k < storedData.size(); k++)
							{
								if (start + ((y * width) + x) == storedData[k].gearIndex)
								{
									sumOfGearRatio += storedData[k].number * number;
									goto next;
								}
							}

							storedData.push_back({ start + ((y * width) + x) , number });
							
						}
						next:
						sumOfPartsNumber += number;
						goto end;
					}
				}
			}
		end:;
		}
		else
			i++;
		
	}
	std::cout << "Part 1: " << sumOfPartsNumber << std::endl;
	std::cout << "Part 2: " << sumOfGearRatio << std::endl;
}