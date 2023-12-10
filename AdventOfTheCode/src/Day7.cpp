#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <utility>

#include "Timer.h"

void DaySevenPartOneChallenge(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;

	enum CardType
	{
		HIGH_CARD,
		ONE_PAIR,
		TWO_PAIR,
		THREE_OF_KIND,
		FULL_HOUSE,
		FOUR_OF_KIND,
		FIVE_OF_KIND
	};

	struct NonNumbericSymbols
	{
		char symbol;
		int value;
	};

	std::array<NonNumbericSymbols, 5> nonNumericSymbols = 
	{{
		{'T', 10},
		{'J', 11},
		{'Q', 12},
		{'K', 13},
		{'A', 14}
	}};

	struct Hand
	{
		std::string cards = "";
		int charID;
		int bid = 0;
		CardType type = HIGH_CARD;
	};

	auto SymbolToInt = [&](char c)
		{
			int charID = -1;
			if (std::isdigit(c))
			{
				charID = c - 48;
			}
			else
			{
				for (int j = 0; j < nonNumericSymbols.size(); j++)
				{
					if (c == nonNumericSymbols[j].symbol)
					{
						charID = nonNumericSymbols[j].value;
						break;
					}
				}
			}

			return charID;
		};

	std::vector<Hand> hands;

	while (std::getline(stream, line))
	{
		std::stringstream ss(line);

		std::string cards;
		int bid;
		int charID;
		ss >> cards >> bid;

		charID = SymbolToInt(cards[0]);

		hands.push_back({ cards, charID, bid });
	}

	for (int i = 0; i < hands.size(); i++)
	{	
		std::unordered_set<char> uniqueSet;

		for (char c : hands[i].cards)
			uniqueSet.insert(c).second;

		if (uniqueSet.size() == 5)
			hands[i].type = HIGH_CARD;
		else if (uniqueSet.size() == 4)
			hands[i].type = ONE_PAIR;
		else if (uniqueSet.size() == 3)
		{
			std::unordered_map<char, int> charCount;
			for (char uniqueChar : uniqueSet) 
			{
				charCount[uniqueChar] = std::count(hands[i].cards.begin(), hands[i].cards.end(), uniqueChar);
				if (charCount[uniqueChar] == 2)
				{
					hands[i].type = TWO_PAIR;
					break;
				}

				if (charCount[uniqueChar] == 3)
				{
					hands[i].type = THREE_OF_KIND;
					break;
				}				
			}
		}
		else if (uniqueSet.size() == 2)
		{
			std::unordered_map<char, int> charCount;
			for (char uniqueChar : uniqueSet) 
			{
				charCount[uniqueChar] = std::count(hands[i].cards.begin(), hands[i].cards.end(), uniqueChar);

				if (charCount[uniqueChar] == 2 || charCount[uniqueChar] == 3)
				{
					hands[i].type = FULL_HOUSE;
					break;
				}

				if (charCount[uniqueChar] == 4)
				{
					hands[i].type = FOUR_OF_KIND;
					break;
				}
			}
		}
		else if (uniqueSet.size() == 1)
		{
			hands[i].type = FIVE_OF_KIND;
		}
	}

	std::sort(hands.begin(), hands.end(), [](const Hand& hand1, const Hand& hand2) {
		return hand1.type < hand2.type; });

	std::unordered_set<CardType> uniqueTypeSet;
	for (int i = 0; i < hands.size(); i++)
	{
		uniqueTypeSet.insert(hands[i].type);
	}	
	
	int iterator = 0;
	for (CardType type : uniqueTypeSet)
	{		
		int count = std::count_if(hands.begin(), hands.end(),
			[type](const Hand& hand) { return hand.type == type; });
		
		if (count > 1)
		{
			int start = iterator;
			int end = iterator + count;

			std::sort(hands.begin() + start, hands.begin() + end, [&](const Hand& hand1, const Hand& hand2) 
				{
					if (hand1.charID == hand2.charID)
					{
						int i = 0;
						int charOne;
						int charTwo;
						do
						{
							i++;
							charOne = SymbolToInt(hand1.cards[i]);
							charTwo = SymbolToInt(hand2.cards[i]);
						} while (charOne == charTwo && i < hand1.cards.size());

						return charOne < charTwo;
					}
					return hand1.charID < hand2.charID;
				});
		}
		iterator += count;
	}

	int sum = 0;
	for (int i = 0; i < hands.size(); i++)
		sum += hands[i].bid * (i + 1);

	std::cout << sum << std::endl;
}

//void DaySevenPartTwoChallenge(const std::string& filepath)
//{
//	std::ifstream stream(filepath);
//	std::string line;
//
//	enum CardType
//	{
//		HIGH_CARD,
//		ONE_PAIR,
//		TWO_PAIR,
//		THREE_OF_KIND,
//		FULL_HOUSE,
//		FOUR_OF_KIND,
//		FIVE_OF_KIND
//	};
//
//	struct NonNumbericSymbols
//	{
//		char symbol;
//		int value;
//	};
//
//	std::array<NonNumbericSymbols, 5> nonNumericSymbols =
//	{ {
//		{'J', 1},
//		{'T', 10},
//		{'Q', 12},
//		{'K', 13},
//		{'A', 14}
//	} };
//
//	struct Hand
//	{
//		std::string cards = "";
//		int charID;
//		int bid = 0;
//		CardType type = HIGH_CARD;
//		std::vector<int> jIndices;
//	};
//
//	auto SymbolToInt = [&](char c)
//		{
//			int charID = -1;
//			if (std::isdigit(c))
//			{
//				charID = c - 48;
//			}
//			else
//			{
//				for (int j = 0; j < nonNumericSymbols.size(); j++)
//				{
//					if (c == nonNumericSymbols[j].symbol)
//					{
//						charID = nonNumericSymbols[j].value;
//						break;
//					}
//				}
//			}
//
//			return charID;
//		};
//
//	auto IntToSymbol = [&](int n)
//		{
//			char c = ' ';
//
//			switch (n)
//			{
//			case 1:  c = 'J'; break;
//			case 10: c = 'T'; break;
//			case 12: c = 'Q'; break;
//			case 13: c = 'K'; break;
//			case 14: c = 'A'; break;
//			}
//
//			return c;
//		};
//
//	auto ChangeJtoMax = [&](Hand& hand)
//		{
//			int found = hand.cards.find('J');
//			int max = SymbolToInt(hand.cards[0]);
//			for (int j = 1; j < hand.cards.size(); j++)
//			{
//				if (j == found)
//					continue;
//				else
//				{
//					if (SymbolToInt(hand.cards[j]) > max)
//						max = SymbolToInt(hand.cards[j]);
//				}
//			}
//
//			while (found != std::string::npos)
//			{
//				hand.jIndices.push_back(found);
//				char c;
//				if (max >= 2 && max <= 9)
//					c = max + 48;
//				else
//					c = IntToSymbol(max);
//				hand.cards[found] = c;
//				if (found == 0) 
//					hand.charID = max;
//				found = hand.cards.find('J', found + 1);
//			}
//		};
//
//	std::vector<Hand> hands;
//
//	while (std::getline(stream, line))
//	{
//		std::stringstream ss(line);
//
//		std::string cards;
//		int bid;
//		int charID;
//		ss >> cards >> bid;
//
//		charID = SymbolToInt(cards[0]);
//
//		hands.push_back({ cards, charID, bid });
//	}
//
//	for (int i = 0; i < hands.size(); i++)
//	{
//		std::unordered_set<char> uniqueSet;
//
//		for (char c : hands[i].cards)
//			uniqueSet.insert(c).second;
//		//if (hands[i].cards.find('J') != std::string::npos)
//		//	std::cout << "Found" << std::endl;
//
//		if (uniqueSet.size() == 5)
//		{
//			if (hands[i].cards.find('J') != std::string::npos)
//			{
//				ChangeJtoMax(hands[i]);
//				hands[i].type = ONE_PAIR;
//			}
//			else
//				hands[i].type = HIGH_CARD;
//		}
//		else if (uniqueSet.size() == 4)
//		{
//			int found = hands[i].cards.find('J');
//			if (found != std::string::npos)
//			{
//				std::unordered_map<char, int> charCount;
//				for (char uniqueChar : uniqueSet)
//				{
//					charCount[uniqueChar] = std::count(hands[i].cards.begin(), hands[i].cards.end(), uniqueChar);
//					if (charCount[uniqueChar] == 2)
//					{
//						if (uniqueChar == 'J')
//						{
//							ChangeJtoMax(hands[i]);
//						}
//						else
//						{
//							hands[i].jIndices.push_back(found);
//							hands[i].cards[found] = uniqueChar;
//							if (found == 0) hands[i].charID = SymbolToInt(uniqueChar);
//						}
//						hands[i].type = THREE_OF_KIND;
//						break;
//					}
//				}
//			}
//			else
//				hands[i].type = ONE_PAIR;
//		}
//		else if (uniqueSet.size() == 3)
//		{			
//			std::unordered_map<char, int> charCount;
//			int found = hands[i].cards.find('J');
//			if (found != std::string::npos)
//			{
//				charCount['J'] = std::count(hands[i].cards.begin(), hands[i].cards.end(), 'J');
//
//				if (charCount['J'] == 1)
//				{
//					char firstChar = ' ';
//					char secondChar = ' ';
//					for (char otherUniqueChar : uniqueSet)
//					{
//						if (otherUniqueChar != 'J')
//						{
//							charCount[otherUniqueChar] = std::count(hands[i].cards.begin(), hands[i].cards.end(), otherUniqueChar);
//
//							if (charCount[otherUniqueChar] == 3)
//							{
//								hands[i].jIndices.push_back(found);
//								hands[i].cards[found] = otherUniqueChar;
//								if (found == 0) hands[i].charID = SymbolToInt(otherUniqueChar);
//
//								hands[i].type = FOUR_OF_KIND;
//								break;
//							}
//							else if (charCount[otherUniqueChar] == 2)
//							{
//								if (firstChar == ' ')
//									firstChar = otherUniqueChar;
//								else
//								{
//									secondChar = otherUniqueChar;
//									char max = ' ';
//									if (SymbolToInt(firstChar) > SymbolToInt(secondChar))
//										max = firstChar;
//									else
//										max = secondChar;
//
//									int found = hands[i].cards.find('J');
//									hands[i].jIndices.push_back(found);
//									hands[i].cards[found] = max;
//									if (found == 0) hands[i].charID = SymbolToInt(max);
//
//									hands[i].type = THREE_OF_KIND;
//									break;
//								}
//							}
//						}
//					}
//				}
//				else if (charCount['J'] == 2)
//				{
//					for (char otherUniqueChar : uniqueSet)
//					{
//						if (otherUniqueChar != 'J')
//						{
//							charCount[otherUniqueChar] = std::count(hands[i].cards.begin(), hands[i].cards.end(), otherUniqueChar);
//
//							if (charCount[otherUniqueChar] == 2)
//							{								
//								while (found != std::string::npos)
//								{
//									hands[i].jIndices.push_back(found);
//									hands[i].cards[found] = otherUniqueChar;
//									if (found == 0) hands[i].charID = SymbolToInt(otherUniqueChar);
//									found = hands[i].cards.find('J', found + 1);
//								}
//								hands[i].type = FOUR_OF_KIND;
//								break;
//							}
//						}
//					}
//				}
//				else if (charCount['J'] == 3)
//				{
//					char firstChar = ' ';
//					char secondChar = ' ';
//					for (char otherUniqueChar : uniqueSet)
//					{
//						if (otherUniqueChar != 'J')
//						{
//							if (firstChar == ' ')
//								firstChar = otherUniqueChar;
//							else
//							{
//								secondChar = otherUniqueChar;
//								char max = ' ';
//								if (SymbolToInt(firstChar) > SymbolToInt(secondChar))
//									max = firstChar;
//								else
//									max = secondChar;
//
//								while (found != std::string::npos)
//								{
//									hands[i].jIndices.push_back(found);
//									hands[i].cards[found] = max;
//									if (found == 0) hands[i].charID = SymbolToInt(max);
//									found = hands[i].cards.find('J', found + 1);
//
//									hands[i].type = FOUR_OF_KIND;
//								}
//								
//							}
//
//						}
//					}
//				}
//			}
//			else
//			{
//				for (char uniqueChar : uniqueSet)
//				{
//					charCount[uniqueChar] = std::count(hands[i].cards.begin(), hands[i].cards.end(), uniqueChar);
//					if (charCount[uniqueChar] == 2)
//					{
//						hands[i].type = TWO_PAIR;
//						break;
//					}
//
//					if (charCount[uniqueChar] == 3)
//					{
//						hands[i].type = THREE_OF_KIND;
//						break;
//					}
//				}
//			}
//		}
//		else if (uniqueSet.size() == 2)
//		{
//			std::unordered_map<char, int> charCount;
//			int found = hands[i].cards.find('J');
//			if (found != std::string::npos)
//			{
//				char twoCharacters[2] = { ' ' };
//				int k = 0;
//				for (char uniqueChar : uniqueSet)
//				{
//					twoCharacters[k] = uniqueChar;
//					k++;
//				}
//
//				char nonJchar;
//				if (twoCharacters[0] == 'J')
//					nonJchar = twoCharacters[1];
//				else
//					nonJchar = twoCharacters[0];
//
//				while (found != std::string::npos)
//				{
//					hands[i].jIndices.push_back(found);
//					hands[i].cards[found] = nonJchar;
//					if (found == 0) hands[i].charID = SymbolToInt(nonJchar);
//					found = hands[i].cards.find('J', found + 1);
//				}
//				hands[i].type = FIVE_OF_KIND;
//			}
//			else
//			{
//				for (char uniqueChar : uniqueSet)
//				{
//					charCount[uniqueChar] = std::count(hands[i].cards.begin(), hands[i].cards.end(), uniqueChar);
//
//					if (charCount[uniqueChar] == 2 || charCount[uniqueChar] == 3)
//					{
//						hands[i].type = FULL_HOUSE;
//						break;
//					}
//
//					if (charCount[uniqueChar] == 4)
//					{
//						hands[i].type = FOUR_OF_KIND;
//						break;
//					}
//				}
//			}
//		}
//		else if (uniqueSet.size() == 1)
//		{
//			if (hands[i].cards.find('J') != std::string::npos)
//			{
//				int found = hands[i].cards.find('J');
//				for (int j = 0; j < hands[i].cards.size(); j++)
//				{
//					hands[i].jIndices.push_back(found);
//					hands[i].cards[j] = 'A';
//				}
//				hands[i].charID = 14;
//
//			}
//			hands[i].type = FIVE_OF_KIND;
//		}
//
//	}
//
//	std::sort(hands.begin(), hands.end(), [](const Hand& hand1, const Hand& hand2) {
//		return hand1.type < hand2.type; });
//
//
//	std::unordered_set<CardType> uniqueTypeSet;
//	for (int i = 0; i < hands.size(); i++)
//	{
//		uniqueTypeSet.insert(hands[i].type);
//	}
//
//	int iterator = 0;
//	for (CardType type : uniqueTypeSet)
//	{
//		int count = std::count_if(hands.begin(), hands.end(),
//			[type](const Hand& hand) { return hand.type == type; });
//
//		if (count > 1)
//		{
//			int start = iterator;
//			int end = iterator + count;
//
//			std::sort(hands.begin() + start, hands.begin() + end, [&](Hand& hand1, Hand& hand2)
//				{
//					auto revertToOriginal = [&](Hand& hand)
//						{
//							for (int i = 0; i < hand.jIndices.size(); i++)
//							{
//								hand.cards[hand.jIndices[i]] = 'J';
//								if (hand.jIndices[i] == 0) 
//									hand.charID = SymbolToInt(hand.cards[i]);
//							}
//						};
//
//					if (hand1.jIndices.size() > 0)
//						revertToOriginal(hand1);
//					if (hand2.jIndices.size() > 0)
//						revertToOriginal(hand2);
//
//					if (hand1.charID == hand2.charID)
//					{
//						int i = 0;
//						int charOne;
//						int charTwo;
//						do
//						{
//							i++;
//							charOne = SymbolToInt(hand1.cards[i]);
//							charTwo = SymbolToInt(hand2.cards[i]);
//						} while (charOne == charTwo && i < hand1.cards.size());
//
//						return charOne < charTwo;
//					}
//					return hand1.charID < hand2.charID;
//				});
//		}
//		iterator += count;
//	}
//
//	//249109578
//	//
//	//249184069
//	
//
//	int sum = 0;
//	for (int i = 0; i < hands.size(); i++)
//	{
//		std::cout << hands[i].cards << " " << hands[i].type << std::endl;
//		sum += hands[i].bid * (i + 1);
//	}
//
//	std::cout << sum << std::endl;
//}