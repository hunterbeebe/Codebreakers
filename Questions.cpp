#include "Questions.h"

Questions::Questions() {
	m_qcards.push_back("What is the total sum of your cards?");
	m_qcards.push_back("What is the sum of your leftmost cards?");
	m_qcards.push_back("What is the sum of your middle cards?");
	m_qcards.push_back("What is the sum of your rightmost cards?");
	m_qcards.push_back("What is the sum of your black cards?");
	m_qcards.push_back("What is the sum of your white cards?");
	m_qcards.push_back("How many odd cards do you have?");
	m_qcards.push_back("How many even cards do you have?");
	m_qcards.push_back("Which of your cards are adjacent to a consecutive number?");
	m_qcards.push_back("How many pairs do you have?");
	m_qcards.push_back("Which adjacent cards of yours are the same color?");
	m_qcards.push_back("How many black cards do you have?");
	m_qcards.push_back("How many white cards do you have?");
	m_qcards.push_back("How many green cards do you have?");
	m_qcards.push_back("Where are your 0's?");
	m_qcards.push_back("Where are your 1's or 2's?");
	m_qcards.push_back("Where are your 3's or 4's?");
	m_qcards.push_back("Where are your 5's?");
	m_qcards.push_back("Where are your 6's or 7's?");
	m_qcards.push_back("Where are your 8's or 9's?");
	m_qcards.push_back("Is your middle card greater than 4?");
	m_qcards.push_back("What is the difference between your largest and smallest number?");
}

void Questions::shuffle() {		// use same methodology as shuffling/drawing the deck
	srand(time(0));
	std::shuffle(m_qcards.begin(), m_qcards.end(), std::default_random_engine(rand()));
}

std::string Questions::draw() {
	std::string top = *m_qcards.begin();
	m_qcards.erase(m_qcards.begin());
	return top;
}