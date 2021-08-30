#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>          
#include <random>  
#include <time.h>

struct card {
	int value;
	std::string color;
};

class Deck {
public:
	Deck();
	void shuffle();
	card draw();
private:
	std::vector<card> m_fulldeck;
};

#endif // DECK_H
