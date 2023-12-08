#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <vector>

#include "Timer.h"

void DaySixPartOneChallenge(const std::string& filepath)
{
	Timer timer;
	std::ifstream stream(filepath);
	std::string line;

	struct RaceData
	{
		int time = 0;
		int distance = 0;
	};

	std::vector<RaceData> raceData;

	while (std::getline(stream, line))
	{
		std::stringstream ss(line);
		std::string token;
		if (line.find("Time:") != std::string::npos)
		{
			if (raceData.empty())
			{
				while (ss >> token)
				{
					if (std::isdigit(token[0]))
						raceData.push_back({ std::stoi(token), 0 });
				}
			}
		}
		else if (line.find("Distance:") != std::string::npos)
		{
			if (!raceData.empty())
			{
				int i = 0;
				while (ss >> token)
				{
					if (std::isdigit(token[0]))
					{
						raceData[i].distance = std::stoi(token);
						i++;
					}
					
				}
			}
			else
				std::cout << "Attempted to add distance, but vector hasn't been initialized\n";
		}
	}

	int sum = 1;
	for (int i = 0; i < raceData.size(); i++)
	{
		int buttonHeldTime = 0;
		int countsToWin = 0;

		while (buttonHeldTime <= raceData[i].time)
		{
			int timeLeft = raceData[i].time - buttonHeldTime;

			int distance = buttonHeldTime * timeLeft;

			if (distance > raceData[i].distance)
				countsToWin++;
			buttonHeldTime++;
		}

		sum *= countsToWin;
	}
	std::cout << sum << std::endl;
	std::cout << "Part 1 time: ";
}

void DaySixPartTwoChallenge(const std::string& filepath)
{
	std::cout << "\n";
	Timer timer;
	std::ifstream stream(filepath);
	std::string line;

	uint64_t raceTime = 0;
	uint64_t raceDistance = 0;

	while (std::getline(stream, line))
	{
		std::stringstream ss(line);
		std::string token;
		if (line.find("Time:") != std::string::npos)
		{
			std::string strTime = "";
			while (ss >> token)
			{
				if (std::isdigit(token[0]))
					strTime += token;
			}
			raceTime = std::stoi(strTime);
		}
		else if (line.find("Distance:") != std::string::npos)
		{			
			std::string strDistance = "";
			while (ss >> token)
			{
				if (std::isdigit(token[0]))
					strDistance += token;
			}
			raceDistance = std::stoull(strDistance);
		}
	}

	uint64_t buttonHeldTime = 0;
	uint64_t countsToWin = 0;

	while (buttonHeldTime <= raceTime)
	{
		uint64_t timeLeft = raceTime - buttonHeldTime;

		uint64_t distance = buttonHeldTime * timeLeft;

		if (distance > raceDistance)
			countsToWin++;
		buttonHeldTime++;
	}

	std::cout << countsToWin << std::endl;
	std::cout << "Part 2 time: ";
}