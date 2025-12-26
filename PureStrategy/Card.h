#pragma once

#include <string>
#include <vector>

const int CARD_MIN_VALUE = 1;
const int CARD_MAX_VALUE = 13;

struct Card {
    int value;

    int getPoints() const;
    std::string toString() const;
};

using Deck = std::vector<Card>;
