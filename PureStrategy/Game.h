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
* <Header file for Game mechanics and flow>
* 
*/

#pragma once

#include "Player.h"

void ClearScreen();

void ShufflePrizeDeck(Deck& deck);

int GetPlayerInput(const Player& p, int currentPrize, int potSize);

int PlayTurn(Player& p1, Player& p2, int currentPrize, int potSize);

void StartGame(Player& p1, Player& p2);
