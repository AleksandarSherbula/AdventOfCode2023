#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

void DayOneChallenge(const std::string& filepath);
void DayTwoChallenge(const std::string& filepath);
void DayThreeChallenge(const std::string& filepath);
void DayFourChallenge(const std::string& filepath);
void DayFiveChallenge(const std::string& filepath);
void DaySixPartOneChallenge(const std::string& filepath);
void DaySixPartTwoChallenge(const std::string& filepath);

int main()
{
	DaySixPartOneChallenge("files/Day6_PuzzleInput.txt");
	DaySixPartTwoChallenge("files/Day6_PuzzleInput.txt");

	return 0;
}