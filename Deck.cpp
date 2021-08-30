#include "Deck.h"

Deck::Deck() {
	m_fulldeck.resize(20);	// We have 20 cards in the deck
	for (int i = 0; i < 10; i++) {	// Assign every white card, make the 5 green
		m_fulldeck[i].value = i;
		m_fulldeck[i].color = "White";
		if (i == 5) {
			m_fulldeck[i].color = "Green";
		}

	}
	for (int j = 10; j < 20; j++) { // Assign every black card, make the 5 green
		m_fulldeck[j].value = j - 10;
		m_fulldeck[j].color = "Black";
		if (j - 10 == 5) {
			m_fulldeck[j].color = "Green";
		}
	}
}

void Deck::shuffle() {
	srand(time(0));
	std::shuffle(m_fulldeck.begin(), m_fulldeck.end(), std::default_random_engine(rand()));
}

card Deck::draw() {
	card top = *m_fulldeck.begin();
	m_fulldeck.erase(m_fulldeck.begin());
	return top;
}