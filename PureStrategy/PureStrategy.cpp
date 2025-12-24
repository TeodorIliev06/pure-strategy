#include <iostream>
#include <cstdlib>
#include <ctime>

const int USERNAME_MAX_LEN = 32;
const int PASSWORD_MAX_LEN = 32;

const int CARDS_IN_SUIT = 13;

const int CARD_MIN_VALUE = 1;
const int CARD_MAX_VALUE = 13;

const int INITIAL_CARDS_CAPACITY = 4;

struct Card
{
	int value;
};

struct CardArray
{
	Card* data;
	int count;
	int capacity;
};

struct Player
{
	char username[USERNAME_MAX_LEN];
	CardArray hand;
	CardArray rewards;
};

// ==== Cards functions ====

void InitializeCardArray(CardArray& arr)
{
	arr.capacity = INITIAL_CARDS_CAPACITY;
	arr.count = 0;
	arr.data = new Card[arr.capacity];
}

void ResizeCardArray(CardArray& arr)
{
	int newCapacity = arr.capacity * 2;
	Card* newData = new Card[newCapacity];

	for (int i = 0; i < arr.count; i++)
	{
		newData[i] = arr.data[i];
	}

	delete[] arr.data;

	arr.data = newData;
	arr.capacity = newCapacity;
}

void AddCard(CardArray& arr, Card card)
{
	if (arr.count >= arr.capacity)
	{
		ResizeCardArray(arr);
	}

	arr.data[arr.count] = card;
	arr.count++;
}

void RemoveCardAt(CardArray& array, int index)
{
	if (index < 0 || index >= array.count)
	{
		return;
	}

	for (int i = index; i < array.count - 1; i++)
	{
		array.data[i] = array.data[i + 1];
	}

	array.count--;
}

void FreeCardArray(CardArray& array)
{
	delete[] array.data;

	array.data = nullptr;
	array.count = 0;
	array.capacity = 0;
}

// ==== Dealing logic ====

void InitializePlayer(Player& player, const char* name)
{
	int i = 0;

	while (name[i] != '\0' && i < USERNAME_MAX_LEN - 1)
	{
		player.username[i] = name[i];
		i++;
	}

	player.username[i] = '\0';

	InitializeCardArray(player.hand);
	InitializeCardArray(player.rewards);
}

void DealCardsToPlayer(Player& player)
{
	for (int value = 1; value <= CARDS_IN_SUIT; value++)
	{
		Card card;
		card.value = value;
		AddCard(player.hand, card);
	}
}

void CreatePrizeDeck(CardArray& prizeDeck)
{
	InitializeCardArray(prizeDeck);

	for (int value = 1; value <= CARDS_IN_SUIT; value++)
	{
		Card card;
		card.value = value;
		AddCard(prizeDeck, card);
	}
}

void ShufflePrizeDeck(CardArray& deck)
{
	for (int i = deck.count - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);

		Card temp = deck.data[i];
		deck.data[i] = deck.data[j];
		deck.data[j] = temp;
	}
}

// ==== Display logic ====

void DisplayCard(int value)
{
	switch (value)
	{
	case 1:
		std::cout << "A";
		break;
	case 11:
		std::cout << "J";
		break;
	case 12:
		std::cout << "Q";
		break;
	case 13:
		std::cout << "K";
		break;
	default:
		std::cout << value;
		break;
	}
}

void DisplayHand(const CardArray& hand)
{
	for (int i = 0; i < hand.count; i++)
	{
		DisplayCard(hand.data[i].value);
		if (i < hand.count - 1)
		{
			std::cout << " ";
		}
	}
}

void DisplayRewards(const CardArray& rewards)
{
	int totalPoints = 0;
	for (int i = 0; i < rewards.count; i++)
	{
		totalPoints += rewards.data[i].value;
	}

	std::cout << "Rewards: ";
	DisplayHand(rewards);
	std::cout << " (Total: " << totalPoints << " points)";
}

void ClearScreen()
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << std::endl;
	}
}

// ==== Input functions ====
int FindCardIndex(const CardArray& hand, int value)
{
	for (int i = 0; i < hand.count; i++)
	{
		if (hand.data[i].value == value)
		{
			return i;
		}
	}
	return -1;
}

int GetPlayerCardChoice(const Player& player, int lastPrizeValue, int totalPrizeValue)
{
	std::cout << player.username << "'s turn" << std::endl;
	std::cout << "Current prize card: ";
	DisplayCard(lastPrizeValue);
	std::cout << " (" << lastPrizeValue << " points)" << std::endl;
	std::cout << "Total stakes: " << totalPrizeValue << " points";

	std::cout << std::endl;
	std::cout << std::endl;
	DisplayRewards(player.rewards);
	std::cout << std::endl;
	std::cout << "Your hand: ";
	DisplayHand(player.hand);
	std::cout << std::endl;
	std::cout << std::endl;

	int choice = 0;
	bool validInput = false;

	while (!validInput)
	{
		std::cout << "Choose a card to play (1-13, A=1, J=11, Q=12, K=13): ";
		std::cin >> choice;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid input. Please enter a number." << std::endl;
			continue;
		}

		if (choice < CARD_MIN_VALUE || choice > CARD_MAX_VALUE)
		{
			std::cout << "Card value must be between 1 and 13." << std::endl;
			continue;
		}

		int cardIndex = FindCardIndex(player.hand, choice);
		if (cardIndex == -1)
		{
			std::cout << "You don't have that card or already played it." << std::endl;
			continue;
		}

		validInput = true;
	}

	return choice;
}
// ==== Game logic ====
void PlayRound(Player& p1, Player& p2, CardArray& prizeDeck, int& prizeIndex)
{
	if (prizeIndex >= prizeDeck.count || p1.hand.count == 0)
	{
		return;
	}

	int currentPrizeValue = prizeDeck.data[prizeIndex].value;
	CardArray accumulatedPrizes;
	InitializeCardArray(accumulatedPrizes);
	AddCard(accumulatedPrizes, prizeDeck.data[prizeIndex]);
	prizeIndex++;

	bool roundComplete = false;

	while (!roundComplete)
	{
		int totalPrizeValue = 0;
		for (int i = 0; i < accumulatedPrizes.count; i++)
		{
			totalPrizeValue += accumulatedPrizes.data[i].value;
		}

		int p1Choice = GetPlayerCardChoice(p1, currentPrizeValue, totalPrizeValue);
		ClearScreen();

		int p2Choice = GetPlayerCardChoice(p2, currentPrizeValue, totalPrizeValue);
		ClearScreen();

		std::cout << p1.username << " played: ";
		DisplayCard(p1Choice);
		std::cout << " (" << p1Choice << " points)" << std::endl;

		std::cout << p2.username << " played: ";
		DisplayCard(p2Choice);
		std::cout << " (" << p2Choice << " points)" << std::endl;

		std::cout << std::endl;

		int p1Index = FindCardIndex(p1.hand, p1Choice);
		int p2Index = FindCardIndex(p2.hand, p2Choice);

		RemoveCardAt(p1.hand, p1Index);
		RemoveCardAt(p2.hand, p2Index);

		if (p1Choice > p2Choice)
		{
			std::cout << p1.username << " wins the prize(s)!" << std::endl;
			for (int i = 0; i < accumulatedPrizes.count; i++)
			{
				AddCard(p1.rewards, accumulatedPrizes.data[i]);
			}

			roundComplete = true;
		}
		else if (p2Choice > p1Choice)
		{
			std::cout << p2.username << " wins the prize(s)!" << std::endl;
			for (int i = 0; i < accumulatedPrizes.count; i++)
			{
				AddCard(p2.rewards, accumulatedPrizes.data[i]);
			}

			roundComplete = true;
		}
		else
		{
			std::cout << "Tie! Both cards removed. Playing again for accumulated prizes..." << std::endl;

			if (prizeIndex < prizeDeck.count)
			{
				currentPrizeValue = prizeDeck.data[prizeIndex].value;
				AddCard(accumulatedPrizes, prizeDeck.data[prizeIndex]);
				prizeIndex++;
			}
			else
			{
				std::cout << "No more prize cards. Prizes discarded." << std::endl;
				roundComplete = true;
			}
		}

		if (p1.hand.count == 0)
		{
			roundComplete = true;
		}

		if (!roundComplete)
		{
			std::cout << "Press Enter to continue...";
			std::cin.ignore(10000, '\n');
			std::cin.get();
			ClearScreen();
		}
	}

	FreeCardArray(accumulatedPrizes);

	std::cout << "Press Enter to continue...";
	std::cin.ignore(10000, '\n');
	std::cin.get();
	ClearScreen();
}

void PlayGame(Player& p1, Player& p2)
{
	CardArray prizeDeck;
	CreatePrizeDeck(prizeDeck);
	ShufflePrizeDeck(prizeDeck);

	int prizeIndex = 0;

	while (p1.hand.count > 0 && prizeIndex < prizeDeck.count)
	{
		PlayRound(p1, p2, prizeDeck, prizeIndex);
	}

	int p1Score = 0;
	int p2Score = 0;

	for (int i = 0; i < p1.rewards.count; i++)
	{
		p1Score += p1.rewards.data[i].value;
	}

	for (int i = 0; i < p2.rewards.count; i++)
	{
		p2Score += p2.rewards.data[i].value;
	}

	std::cout << "===== GAME OVER =====" << std::endl;
	std::cout << std::endl;
	std::cout << p1.username << " final score: " << p1Score << std::endl;
	std::cout << p2.username << " final score: " << p2Score << std::endl;
	std::cout << std::endl;

	if (p1Score > p2Score)
	{
		std::cout << p1.username << " wins!" << std::endl;
	}
	else if (p2Score > p1Score)
	{
		std::cout << p2.username << " wins!" << std::endl;
	}
	else
	{
		std::cout << "It's a tie!" << std::endl;
	}

	FreeCardArray(prizeDeck);
}

int main()
{
	srand((unsigned int)time(NULL));

	Player playerOne;
	Player playerTwo;

	InitializePlayer(playerOne, "Player1");
	InitializePlayer(playerTwo, "Player2");

	DealCardsToPlayer(playerOne);
	DealCardsToPlayer(playerTwo);

	PlayGame(playerOne, playerTwo);

	FreeCardArray(playerOne.hand);
	FreeCardArray(playerOne.rewards);
	FreeCardArray(playerTwo.hand);
	FreeCardArray(playerTwo.rewards);

	return 0;
}
