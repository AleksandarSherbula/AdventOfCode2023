#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <vector>

#include "Timer.h"

void DayFiveChallenge(const std::string& filepath)
{
	Timer timer;
	
	struct SeedData
	{
		uint64_t number;
		uint64_t range;
	};
	
	std::vector<SeedData> seedsData;
	
	std::ifstream stream(filepath);
	std::string line;
	std::getline(stream, line);

	if (!line.empty())
	{
		std::stringstream ss(line);		
		if (line.find("seeds:") != std::string::npos)
		{
			std::string token;
			while (ss >> token)
			{
				if (std::isdigit(token[0]))
				{
					uint64_t number = std::stoull(token);
					uint64_t range = 0;
					ss >> range;
					seedsData.push_back({ number, range });
				}
			}
		}
	}

	uint64_t minimumLocation = 1844674407370;
	for (int i = 0; i < seedsData.size(); i++)
	{
		for (int j = 0; j < seedsData[i].range; j++)
		{
			std::cout << j << std::endl;
			uint64_t seed = seedsData[i].number + j;
			bool found = false;
			std::ifstream stream(filepath);
			while (getline(stream, line))
			{
				std::stringstream ss(line);
				if (std::isdigit(line[0]))
				{
					uint64_t source;
					uint64_t destination;
					uint64_t range;

					ss >> destination >> source >> range;

					uint64_t initSource = source;
					uint64_t initDestination = destination;

					source = initSource;
					destination = initDestination;

					if (seed >= source && seed < (source + range) && !found)
					{	
						int64_t gap;
						if (destination > source)
						{
							gap = destination - source;
							seed += gap;
						}
						else
						{
							gap = source - destination;
							seed -= gap;
						}
						found = true;
					}
				}
				else 
				{
					found = false;
				}
			}
			if (seed < minimumLocation)
				minimumLocation = seed;
		}
	}
	std::cout << minimumLocation << std::endl;
}
