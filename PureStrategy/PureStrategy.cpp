#include <iostream>
#include <cstdlib>

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

int main()
{
	srand((unsigned int)time(NULL));

	Player playerOne;
	Player playerTwo;
	CardArray prizeDeck;

	InitializePlayer(playerOne, "Player1");
	InitializePlayer(playerTwo, "Player2");

	DealCardsToPlayer(playerOne);
	DealCardsToPlayer(playerTwo);

	CreatePrizeDeck(prizeDeck);
	ShufflePrizeDeck(prizeDeck);

	std::cout << "Player 1 hand:" << std::endl;
	for (int i = 0; i < playerOne.hand.count; i++)
	{
		std::cout << playerOne.hand.data[i].value << " ";
	}
	std::cout << std::endl;

	std::cout << "Prize deck:" << std::endl;
	for (int i = 0; i < prizeDeck.count; i++)
	{
		std::cout << prizeDeck.data[i].value << " ";
	}
	std::cout << std::endl;

	FreeCardArray(playerOne.hand);
	FreeCardArray(playerOne.rewards);
	FreeCardArray(playerTwo.hand);
	FreeCardArray(playerTwo.rewards);
	FreeCardArray(prizeDeck);

	return 0;
}
