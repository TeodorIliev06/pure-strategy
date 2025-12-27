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
	case 11:
		std::cout << "J";
	case 12:
		std::cout << "Q";
	case 13:
		std::cout << "K";
	default:
		std::cout << std::to_string(card.value);
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