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
* <Header file for user profile data and file I/O>
*
*/

#pragma once

#include <string>
#include <vector>

struct OpponentStat
{
	std::string opponentName;
	int gamesPlayed;
	int gamesWon;
};

struct UserProfile
{
	std::string username;
	std::string password;
	int totalGamesPlayed;
	int totalGamesWon;
	std::vector<OpponentStat> opponentStats;
};

bool IsValidPassword(const std::string& password);

bool UserExists(const std::string& username);

void SaveUserProfile(const UserProfile& profile);

bool LoadUserProfile(const std::string& username, UserProfile& profile);

void UpdateOpponentStat(UserProfile& profile, const std::string& opponentName, bool won);

void RegisterUser(UserProfile& activeProfile);

bool LoginUser(UserProfile& activeProfile);
