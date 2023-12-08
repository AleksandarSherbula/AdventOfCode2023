#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <vector>

#include "Timer.h"

// Easily the slowest code i have ever written. This one is definitely word revisiting.

void DayFourChallenge(const std::string& filepath)
{
	Timer timer;
	std::ifstream stream(filepath);
	std::string line;

	int totalScore = 0;
	int cardNumber = 0;

	struct CardCopy
	{
		int id = 0;
		int numOfCopies = 1;
	};

	std::vector<CardCopy> cardCopies;	

	while (getline(stream, line))
	{
		std::stringstream ss(line);
		std::string token;

		std::vector<int> winningNumbers;
		std::vector<int> givenNumbers;

		ss >> token >> cardNumber >> token >> token;
		int numberOfCopies;
		if (cardNumber - 1 >= cardCopies.size())
		{
			cardCopies.push_back({ cardNumber, 1 });
		}
		numberOfCopies = cardCopies[cardNumber - 1].numOfCopies;

		while (token.find("|") == std::string::npos)
		{
			int number = std::stoi(token);
			winningNumbers.push_back(number);
			ss >> token;
		}

		while (ss >> token)
		{
			int number = std::stoi(token);
			givenNumbers.push_back(number);
		}

		int cardScore = 0;
		for (int copy = 0; copy < numberOfCopies; copy++)
		{
			int nextCardNumber = cardNumber + 1;
			for (int i = 0; i < winningNumbers.size(); i++)
			{
				for (int j = 0; j < givenNumbers.size(); j++)
				{
					if (givenNumbers[j] == winningNumbers[i])
					{
						int it = nextCardNumber - 1;

						if (it >= cardCopies.size())
						{
							cardCopies.push_back({ nextCardNumber });
						}
						cardCopies[it].numOfCopies++;
						nextCardNumber++;
						break;
					}
				}
			}
		}
		
	}
	
	int totalSumOfCopies = 0;
	for (int c = 0; c < cardCopies.size(); c++)
		totalSumOfCopies += cardCopies[c].numOfCopies;

	std::cout << totalSumOfCopies << std::endl;
}