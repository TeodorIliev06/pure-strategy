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
* <Header file for Card struct and related logic>
*
*/

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
