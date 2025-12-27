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