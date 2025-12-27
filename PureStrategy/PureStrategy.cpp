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
* <Main entry point and menu logic>
*
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "Card.h"
#include "Player.h"
#include "UserProfile.h"

void HandleGameSession(UserProfile& p1Profile)
{
	UserProfile p2Profile;
	std::string p2Name, p2Pass;
	bool p2IsRegistered = false;

	// 1. Identify Player 2
	std::cout << "\n=== MATCH SETUP ===\n";
	std::cout << "Player 1 (Host): " << p1Profile.username << "\n";

	// Clean buffer before asking for string
	std::cin.ignore(10000, '\n');

	std::cout << "Enter Player 2 Username: ";
	std::getline(std::cin, p2Name);

	if (p2Name == p1Profile.username)
	{
		std::cout << "You cannot play against yourself!\n";
		return;
	}

	// 2. Authenticate Player 2 (The "Challenger" Login)
	if (UserExists(p2Name))
	{
		std::cout << "User found. Enter Player 2 Password: ";
		std::getline(std::cin, p2Pass);

		// Load profile into a temp variable to check password
		if (LoadUserProfile(p2Name, p2Profile))
		{
			if (p2Profile.password == p2Pass)
			{
				std::cout << "Player 2 Logged in successfully!\n";
				p2IsRegistered = true;
			}
			else
			{
				std::cout << "Incorrect password! Returning to menu...\n";
				return;
			}
		}
	}
	else
	{
		std::cout << "User not found. Playing as Guest (Stats will not be saved).\n";
		p2Profile.username = p2Name;
		p2Profile.totalGamesPlayed = 0;
		p2Profile.totalGamesWon = 0;
	}

	// 3. Initialize Game Objects
	Player p1, p2;
	InitializePlayer(p1, p1Profile.username);
	InitializePlayer(p2, p2Profile.username);

	CreateSuitDeck(p1.hand);
	CreateSuitDeck(p2.hand);

	// 4. Start Game
	std::cout << "\nStarting Game... (P1 looks away!)\n";
	std::cout << "Press Enter to begin.";
	std::cin.get(); // We already ignored the newline earlier

	StartGame(p1, p2);

	// 5. Update Stats
	int score1 = CalculatePlayerScore(p1);
	int score2 = CalculatePlayerScore(p2);

	// Update P1 (The Host)
	p1Profile.totalGamesPlayed++;
	if (score1 > score2) p1Profile.totalGamesWon++;
	UpdateOpponentStat(p1Profile, p2Profile.username, (score1 > score2));
	SaveUserProfile(p1Profile);

	// Update P2 (The Challenger) - ONLY if registered
	if (p2IsRegistered)
	{
		p2Profile.totalGamesPlayed++;
		if (score2 > score1) p2Profile.totalGamesWon++;
		UpdateOpponentStat(p2Profile, p1Profile.username, (score2 > score1));
		SaveUserProfile(p2Profile);
		std::cout << "Stats saved for Player 2.\n";
	}
}

void ShowUserMenu(UserProfile& user)
{
	bool loggedIn = true;
	while (loggedIn)
	{
		std::cout << "\n=== Welcome, " << user.username << " ===\n";
		std::cout << "1. Play Game\n";
		std::cout << "2. View Statistics\n";
		std::cout << "3. Logout\n";
		std::cout << "Choose: ";

		int choice;
		std::cin >> choice;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}

		switch (choice)
		{
		case 1:
			HandleGameSession(user);
			break;
		case 2:
			// You can implement a nice print function in UserProfile.cpp
			// For now, manual print:
			std::cout << "\nStats for " << user.username << ":\n";
			std::cout << "Played: " << user.totalGamesPlayed << "\n";
			std::cout << "Won: " << user.totalGamesWon << "\n";
			break;
		case 3:
			loggedIn = false;
			std::cout << "Logging out...\n";
			break;
		default:
			std::cout << "Invalid choice.\n";
		}
	}
}

int main()
{
	srand((unsigned int)time(NULL));

	bool running = true;
	UserProfile currentUser;

	while (running)
	{
		std::cout << "\n==============================\n";
		std::cout << "   PURE STRATEGY CARD GAME    \n";
		std::cout << "==============================\n";
		std::cout << "1. Register\n";
		std::cout << "2. Login\n";
		std::cout << "3. Exit\n";
		std::cout << "Choose: ";

		int choice;
		std::cin >> choice;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Please enter a number.\n";
			continue;
		}

		switch (choice)
		{
		case 1:
			RegisterUser(currentUser);
			break;

		case 2:
			if (LoginUser(currentUser))
			{
				ShowUserMenu(currentUser);
			}
			break;

		case 3:
			running = false;
			std::cout << "Goodbye!\n";
			break;

		default:
			std::cout << "Invalid option. Try again.\n";
		}
	}

	return 0;
}