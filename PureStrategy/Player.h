#pragma once

#include <string>
#include "Card.h"

struct Player
{
	std::string username;
	Deck hand;
	Deck rewards;
};

void InitializePlayer(Player& p, const std::string& name);

bool PlayerHasCard(const Player& p, int cardValue);

void RemoveCardFromHand(Player& p, int cardValue);

void AddRewards(Player& p, const Deck& wonCards);

int CalculatePlayerScore(const Player& p);

void PrintPlayerHand(const Player& p);

void PrintPlayerRewards(const Player& p);
