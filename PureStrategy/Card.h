#pragma once

#include <string>
#include <vector>

const int CARD_MIN_VALUE = 1;
const int CARD_MAX_VALUE = 13;

struct Card {
    int value;
};

typedef std::vector<Card> Deck;

int GetCardPoints(const Card& card);

void PrintCard(const Card& card);

void CreateSuitDeck(Deck& deck);
