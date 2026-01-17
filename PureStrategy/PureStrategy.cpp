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

void PrintStats(const UserProfile& user)
{
	std::cout << "\n=== STATISTICS FOR " << user.username << " ===\n";

	double winRate = 0.0;
	if (user.totalGamesPlayed > 0) 
	{
		winRate = ((double)user.totalGamesWon / user.totalGamesPlayed) * 100.0;
	}

	std::cout << "Total Games: " << user.totalGamesPlayed << "\n";
	std::cout << "Total Wins:  " << user.totalGamesWon << " (" << (int)winRate << "%)\n";

	std::cout << "--- Against Opponents ---\n";
	if (user.opponentStats.empty())
	{
		std::cout << "(No games played against specific opponents yet)\n";
	}
	else
	{
		for (size_t i = 0; i < user.opponentStats.size(); i++)
		{
			const OpponentStat& op = user.opponentStats[i];
			double opWinRate = 0.0;
			if (op.gamesPlayed > 0)
			{
				opWinRate = ((double)op.gamesWon / op.gamesPlayed) * 100.0;
			}

			std::cout << op.opponentName << ": "
				<< op.gamesPlayed << " games ("
				<< op.gamesWon << "/" << (int)opWinRate << "% wins)\n";
		}
	}
	std::cout << "===========================\n";
}

bool SetupPlayer2(UserProfile& p2Profile)
{
	std::string p2Name, p2Pass;
	std::cin.ignore(10000, '\n'); // Clear buffer before reading string

	while (true)
	{
		std::cout << "\nEnter Player 2 Username: ";
		std::getline(std::cin, p2Name);

		if (p2Name.empty()) {
			std::cout << "Name cannot be empty.\n";
			continue;
		}
		break;
	}

	if (UserExists(p2Name))
	{
		for (int attempts = 0; attempts < 3; attempts++)
		{
			std::cout << "Enter Password for " << p2Name << ": ";
			std::getline(std::cin, p2Pass);

			if (LoadUserProfile(p2Name, p2Profile))
			{
				if (p2Profile.password == p2Pass) {
					std::cout << ">> Player 2 Logged in!\n";
					return true;
				}
			}
			std::cout << "Incorrect password. (" << (2 - attempts) << " tries left)\n";
		}
		std::cout << "Too many failed attempts. Returning to menu.\n";
		return false;
	}
	else
	{
		std::cout << "User '" << p2Name << "' not found. Register? (y/n): ";
		char choice;
		std::cin >> choice;
		std::cin.ignore(10000, '\n');

		if (choice == 'y' || choice == 'Y')
		{
			std::cout << "Set Password: ";
			std::getline(std::cin, p2Pass);

			p2Profile.username = p2Name;
			p2Profile.password = p2Pass;
			p2Profile.totalGamesPlayed = 0;
			p2Profile.totalGamesWon = 0;
			p2Profile.opponentStats.clear();
			SaveUserProfile(p2Profile);

			std::cout << ">> Player 2 Registered and Logged in!\n";
			return true;
		}
		return false;
	}
}

void UpdateAndSaveStats(UserProfile& current, const std::string& opponentName, bool won)
{
	current.totalGamesPlayed++;
	if (won) current.totalGamesWon++;

	UpdateOpponentStat(current, opponentName, won);
	SaveUserProfile(current);
}

void HandleGameSession(UserProfile& p1Profile)
{
	UserProfile p2Profile;

	std::cout << "\n=== MATCH SETUP ===\n";
	std::cout << "Player 1: " << p1Profile.username << "\n";

	if (p1Profile.username.empty()) {
		std::cout << "Error: Player 1 not loaded.\n";
		return;
	}

	// We pass the validation responsibility to SetupPlayer2
	if (!SetupPlayer2(p2Profile))
	{
		std::cout << "Match setup cancelled.\n";
		return;
	}

	if (p1Profile.username == p2Profile.username)
	{
		std::cout << "You cannot play against yourself!\n";
		return;
	}

	// 2. Initialize Game Objects
	Player p1, p2;
	InitializePlayer(p1, p1Profile.username);
	InitializePlayer(p2, p2Profile.username);
	CreateSuitDeck(p1.hand);
	CreateSuitDeck(p2.hand);

	// 3. Start Game
	std::cout << "\nStarting Game... Press Enter.";
	std::cin.get();
	ClearScreen();
	StartGame(p1, p2);

	// 4. Calculate Scores
	int score1 = CalculatePlayerScore(p1);
	int score2 = CalculatePlayerScore(p2);

	// 5. Update & Save Stats
	UpdateAndSaveStats(p1Profile, p2Profile.username, (score1 > score2));
	UpdateAndSaveStats(p2Profile, p1Profile.username, (score2 > score1));

	std::cout << "[System] Statistics saved for both players.\n";
}

void ShowUserMenu(UserProfile& user)
{
	bool loggedIn = true;
	while (loggedIn)
	{
		std::cout << "\n=== " << user.username << "'s Menu ===\n";
		std::cout << "1. Play Game\n";
		std::cout << "2. View Statistics\n";
		std::cout << "3. Logout\n";
		std::cout << "Choose: ";

		int choice;
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear(); std::cin.ignore(10000, '\n');
			continue;
		}

		switch (choice)
		{
		case 1: HandleGameSession(user); break;
		case 2: PrintStats(user); break;
		case 3: loggedIn = false; break;
		default: std::cout << "Invalid choice.\n";
		}
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	UserProfile currentUser;
	bool running = true;

	while (running)
	{
		std::cout << "=== PURE STRATEGY ===\n";
		std::cout << "1. Register\n";
		std::cout << "2. Login\n";
		std::cout << "3. Exit\n";
		std::cout << "Choose: ";

		int choice;
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear(); std::cin.ignore(10000, '\n');
			std::cout << "Input error.\n"; continue;
		}

		switch (choice)
		{
		case 1: RegisterUser(currentUser); break;
		case 2:
			if (LoginUser(currentUser)) ShowUserMenu(currentUser);
			break;
		case 3: running = false; break;
		default: std::cout << "Invalid option.\n";
		}
	}
	return 0;
}