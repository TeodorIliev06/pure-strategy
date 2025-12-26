#include <iostream>

#include "Card.h"

int Card::getPoints() const {
	if (value == 1) return 1;
	if (value >= 11) return value;

	return value;
}

std::string Card::toString() const {
	switch (value) {
	case 1:  return "A";
	case 11: return "J";
	case 12: return "Q";
	case 13: return "K";
	default: return std::to_string(value);
	}
}