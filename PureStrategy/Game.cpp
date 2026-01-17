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
* <Implementation of game mechanics>
*
*/

#include <iostream>
#include <cstdlib>
#include "Game.h"

void ClearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void ShufflePrizeDeck(Deck& deck)
{
	for (int i = deck.size() - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		Card temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}
}

int GetPlayerInput(const Player& p, int currentPrize, int potSize)
{
	std::string inputStr;
	int choice = 0;
	bool valid = false;

	while (!valid)
	{
		std::cout << p.username << "'s Turn.\n";
		std::cout << "Prize Card: " << currentPrize << " | Total Pot: " << potSize << "\n";
		std::cout << "Your Hand: ";
		PrintPlayerHand(p);
		std::cout << "\nChoose card to play: ";

		std::cin >> inputStr;
		choice = ParseCardString(inputStr);

		if (choice == 0)
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid input. Please enter a number.\n";
		}
		else if (!PlayerHasCard(p, choice))
		{
			std::cout << "You do not have that card!\n";
		}
		else
		{
			valid = true;
		}
	}
	return choice;
}

int PlayTurn(Player& p1, Player& p2, int currentPrize, int potSize)
{
	int card1 = GetPlayerInput(p1, currentPrize, potSize);
	ClearScreen();

	int card2 = GetPlayerInput(p2, currentPrize, potSize);
	ClearScreen();

	RemoveCardFromHand(p1, card1);
	RemoveCardFromHand(p2, card2);

	std::cout << "--- ROUND RESULT ---\n";
	std::cout << p1.username << " played: " << card1 << "\n";
	std::cout << p2.username << " played: " << card2 << "\n";

	if (card1 > card2) return 1;
	if (card2 > card1) return 2;
	return 0;
}

void StartGame(Player& p1, Player& p2)
{
	Deck prizeDeck;
	CreateSuitDeck(prizeDeck);
	ShufflePrizeDeck(prizeDeck);

	Deck pot;
	int prizeIndex = 0;

	while (prizeIndex < prizeDeck.size() && !p1.hand.empty())
	{
		// Add new prize to the pot
		pot.push_back(prizeDeck[prizeIndex]);
		prizeIndex++;

		// Calculate total value of the pot for display
		int potValue = 0;
		for (size_t i = 0; i < pot.size(); i++) potValue += pot[i].value;

		int result = PlayTurn(p1, p2, pot.back().value, potValue);

		std::cout << std::endl;
		if (result == 1)
		{
			std::cout << p1.username << " wins the pot!\n";
			AddRewards(p1, pot);
			pot.clear();
		}
		else if (result == 2)
		{
			std::cout << p2.username << " wins the pot!\n";
			AddRewards(p2, pot);
			pot.clear();
		}
		else
		{
			std::cout << "It's a TIE! Prize stays in the pot.\n";
		}

		std::cout << "Press Enter to continue...";
		std::cin.ignore(10000, '\n');
		std::cin.get();
		ClearScreen();
	}

	int score1 = CalculatePlayerScore(p1);
	int score2 = CalculatePlayerScore(p2);

	std::cout << "=== GAME OVER ===\n";
	std::cout << p1.username << ": " << score1 << "\n";
	std::cout << p2.username << ": " << score2 << "\n";
}