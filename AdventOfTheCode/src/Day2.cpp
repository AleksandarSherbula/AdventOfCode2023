#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Timer.h"

void DayTwoChallenge(const std::string& filepath)
{
	Timer timer;
	std::ifstream stream(filepath);
	std::string line;

	int sum = 0;
	int power = 0;
	while (getline(stream, line))
	{
		int id;
		int redCubes = 0;
		int greenCubes = 0;
		int blueCubes = 0;

		int maxPossibleRedCubes = 0;
		int maxPossibleGreenCubes = 0;
		int maxPossibleBlueCubes = 0;

		std::stringstream ss(line);
		std::string token;

		bool impossibleDraw = false;
		
		ss >> token >> id;
		while (ss >> token)
		{
			int number = 0;
			if (std::isdigit(token[0]))
			{
				number = std::stoi(token);
				ss >> token;
				if (token.find("red") != std::string::npos)
				{
					redCubes = number;

					if (maxPossibleRedCubes < redCubes)
						maxPossibleRedCubes = redCubes;
				}
				else if (token.find("green") != std::string::npos)
				{
					greenCubes = number;

					if (maxPossibleGreenCubes < greenCubes)
						maxPossibleGreenCubes = greenCubes;
				}
				else if (token.find("blue") != std::string::npos)
				{
					blueCubes = number;
					if (maxPossibleBlueCubes < blueCubes)
						maxPossibleBlueCubes = blueCubes;
				}

				if (redCubes > 12 || greenCubes > 13 || blueCubes > 14)
				{
					impossibleDraw = true;
				}
			}
		}

		power += maxPossibleRedCubes * maxPossibleGreenCubes * maxPossibleBlueCubes;
		
		if (!impossibleDraw)
			sum += id;
	}

	std::cout << sum << std::endl;
	std::cout << power << std::endl;
}