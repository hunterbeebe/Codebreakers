#include "Player.h"

bool codeCompare(card cardone, card cardtwo);
std::vector<std::string> cardConverter(std::vector<card> hand);

Player::Player() {

}

std::vector<card> Player::giveHand() {
	return m_hand;	// send the hand back
}

std::vector<std::string> Player::giveStringHand() {
	return m_stringhand;
}

void Player::addCardtoHand(card dealt) {
	m_hand.push_back(dealt);	// add the dealt card into the hand
}

void Player::sortHand() {
	std::sort(m_hand.begin(), m_hand.end(), codeCompare);	// sort the hand using our compare function below
	m_stringhand = cardConverter(m_hand); // now that it's sorted we can also create the string form of it
}

bool codeCompare(card cardone, card cardtwo) {
	if (cardone.value < cardtwo.value) {
		return true;		// sort by numeric value first of all
	}
	if (cardone.value == cardtwo.value) {
		if (cardone.color == "Black") {
			return true;	// black goes before white if the number is the same
		}					// if it's green then the order doesn't matter to us
	}
	return false;
}

std::vector<std::string> cardConverter(std::vector<card> hand) {
	std::vector<std::string> stringhand;
	for (auto iterator = hand.begin(); iterator != hand.end(); iterator++) {
		card added = *iterator;
		stringhand.push_back(added.color + " " + std::to_string(added.value));
	}
	return stringhand;
}
