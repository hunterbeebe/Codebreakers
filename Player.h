#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include <string>


class Player {
public:
	Player();
	std::vector<card> giveHand();
	std::vector<std::string> giveStringHand();
	void addCardtoHand(card dealt);
	void sortHand();
private:
	std::vector<card> m_hand;
	std::vector<std::string> m_stringhand;
};

#endif
