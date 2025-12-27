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
* <Implementation of Player logic>
*
*/

#include <iostream>
#include "Player.h"

void InitializePlayer(Player& p, const std::string& name)
{
	p.username = name;
	p.hand.clear();
	p.rewards.clear();
}

bool PlayerHasCard(const Player& p, int cardValue)
{
	for (size_t i = 0; i < p.hand.size(); i++)
	{
		if (p.hand[i].value == cardValue)
		{
			return true;
		}
	}
	return false;
}

void RemoveCardFromHand(Player& p, int cardValue)
{
	for (size_t i = 0; i < p.hand.size(); i++)
	{
		if (p.hand[i].value == cardValue)
		{
			p.hand.erase(p.hand.begin() + i);
			return;
		}
	}
}

void AddRewards(Player& p, const Deck& wonCards)
{
	for (size_t i = 0; i < wonCards.size(); i++)
	{
		p.rewards.push_back(wonCards[i]);
	}
}

int CalculatePlayerScore(const Player& p)
{
	int total = 0;
	for (size_t i = 0; i < p.rewards.size(); i++)
	{
		total += GetCardPoints(p.rewards[i]);
	}

	return total;
}

void PrintPlayerHand(const Player& p)
{
	for (size_t i = 0; i < p.hand.size(); i++)
	{
		PrintCard(p.hand[i]);
		if (i < p.hand.size() - 1)
		{
			std::cout << " ";
		}
	}

	std::cout << std::endl;
}

void PrintPlayerRewards(const Player& p)
{
	std::cout << "Collected Rewards: ";

	for (size_t i = 0; i < p.rewards.size(); i++)
	{
		PrintCard(p.rewards[i]);
		std::cout << " ";
	}

	std::cout << "(Total: " << CalculatePlayerScore(p) << ")" << std::endl;
}