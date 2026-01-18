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
* <Implementation of User Profile logic>
*
*/

#include <iostream>
#include <fstream>

#include "UserProfile.h"

const int IGNORE_LIMIT = 10000;
const int MIN_PASSWORD_LEN = 3;

std::string GetFilename(const std::string& username)
{
	return username + ".txt";
}

bool UserExists(const std::string& username)
{
	std::ifstream file(GetFilename(username));
	return file.good();
}

bool IsValidPassword(const std::string& password)
{
	if (password.length() < MIN_PASSWORD_LEN)
	{
		std::cout << "Error: Password must be at least " << MIN_PASSWORD_LEN
			<< " characters long.\n";
		return false;
	}

	bool hasSpaces = false;
	for (size_t i = 0; i < password.length(); i++)
	{
		if (password[i] == ' ' || password[i] == '\t')
		{
			hasSpaces = true;
			break;
		}
	}

	if (hasSpaces)
	{
		std::cout << "Error: Password cannot contain spaces.\n";
		return false;
	}

	return true;
}

void SaveUserProfile(const UserProfile& profile)
{
	std::ofstream file(GetFilename(profile.username));

	if (!file.is_open())
	{
		return;
	}

	file << profile.username << "\n";
	file << profile.password << "\n";
	file << profile.totalGamesPlayed << "\n";
	file << profile.totalGamesWon << "\n";

	// Save number of opponents first
	file << profile.opponentStats.size() << "\n";

	for (size_t i = 0; i < profile.opponentStats.size(); i++)
	{
		file << profile.opponentStats[i].opponentName << "\n";
		file << profile.opponentStats[i].gamesPlayed << "\n";
		file << profile.opponentStats[i].gamesWon << "\n";
	}
	file.close();
}

bool LoadUserProfile(const std::string& username, UserProfile& profile)
{
	std::ifstream file(GetFilename(username));

	if (!file.is_open())
		return false;

	std::getline(file, profile.username);
	std::getline(file, profile.password);

	file >> profile.totalGamesPlayed;
	file >> profile.totalGamesWon;

	size_t count;
	file >> count;

	file.ignore(IGNORE_LIMIT, '\n');
	profile.opponentStats.clear();

	for (size_t i = 0; i < count; i++)
	{
		OpponentStat stat;

		std::getline(file, stat.opponentName);

		file >> stat.gamesPlayed;
		file >> stat.gamesWon;

		file.ignore(IGNORE_LIMIT, '\n');
		profile.opponentStats.push_back(stat);
	}
	return true;
}

void UpdateOpponentStat(UserProfile& profile, const std::string& opponentName, bool won)
{
	bool found = false;
	for (size_t i = 0; i < profile.opponentStats.size(); i++)
	{
		if (profile.opponentStats[i].opponentName == opponentName)
		{
			profile.opponentStats[i].gamesPlayed++;

			if (won)
				profile.opponentStats[i].gamesWon++;

			found = true;
			break;
		}
	}

	if (!found)
	{
		OpponentStat newStat;
		newStat.opponentName = opponentName;
		newStat.gamesPlayed = 1;
		newStat.gamesWon = (won ? 1 : 0);
		profile.opponentStats.push_back(newStat);
	}
}

void RegisterUser(UserProfile& activeProfile)
{
	std::string username, password;

	std::cin.ignore(IGNORE_LIMIT, '\n');

	std::cout << "Enter new username: ";
	std::getline(std::cin, username);

	if (UserExists(username))
	{
		std::cout << "Error: User already exists.\n";
		return;
	}

	while (true)
	{
		std::cout << "Enter password: ";
		std::getline(std::cin, password);

		if (IsValidPassword(password))
		{
			break;
		}
	}

	// Reset profile data
	activeProfile.username = username;
	activeProfile.password = password;
	activeProfile.totalGamesPlayed = 0;
	activeProfile.totalGamesWon = 0;
	activeProfile.opponentStats.clear();

	SaveUserProfile(activeProfile);
	std::cout << "Registration successful!\n";
}

bool LoginUser(UserProfile& activeProfile)
{
	std::string username, password;

	std::cin.ignore(IGNORE_LIMIT, '\n');

	std::cout << "Username: ";
	std::getline(std::cin, username);

	if (!UserExists(username))
	{
		std::cout << "Error: User not found.\n";
		return false;
	}

	UserProfile temp;
	if (!LoadUserProfile(username, temp))
		return false;

	std::cout << "Password: ";
	std::getline(std::cin, password);

	if (temp.password == password)
	{
		activeProfile = temp;
		std::cout << "Login successful!\n";
		return true;
	}

	std::cout << "Error: Incorrect password.\n";
	return false;
}