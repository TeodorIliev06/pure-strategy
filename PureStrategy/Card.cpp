/**
*
* Solution to course project #1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Teodor Iliev
* @idnumber 4MI0600570
* @compiler VS
*
* <Implementation of Card logic>
*
*/

#include <iostream>

#include "Card.h"

int GetCardPoints(const Card& card)
{
	return card.value;
}

void PrintCard(const Card& card)
{
	switch (card.value)
	{
	case 1:
		std::cout << "A";
		break;
	case 11:
		std::cout << "J";
		break;
	case 12:
		std::cout << "Q";
		break;
	case 13:
		std::cout << "K";
		break;
	default:
		std::cout << std::to_string(card.value);
		break;
	}
}

int ParseCardString(const std::string& input)
{
	if (input == "A" || input == "a" || input == "1") return 1;
	if (input == "J" || input == "j" || input == "11") return 11;
	if (input == "Q" || input == "q" || input == "12") return 12;
	if (input == "K" || input == "k" || input == "13") return 13;
	if (input == "10") return 10;

	if (input.length() == 1)
	{
		char c = input[0];
		if (c >= '2' && c <= '9')
		{
			return c - '0';
		}
	}

	return 0;
}

void CreateSuitDeck(Deck& deck)
{
	deck.clear();

	for (int i = CARD_MIN_VALUE; i <= CARD_MAX_VALUE; i++)
	{
		Card newCard;
		newCard.value = i;
		deck.push_back(newCard);
	}
}