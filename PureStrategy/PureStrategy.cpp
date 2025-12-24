#include <iostream>

const int USERNAME_MAX_LEN = 32;
const int PASSWORD_MAX_LEN = 32;

const int MAX_CARDS_IN_SUIT = 13;

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

int main()
{

}
