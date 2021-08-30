#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include "Questions.h"
#include <iostream>
#include <stdlib.h>

std::string QuestionResolver(std::string qprompt, Player target);

class Game {
public:
	Game();
	int dealCards();
	int dealQuestions();
	void displayboard();
	void humanTakeTurn();
	std::string humanAskQuestion(std::string qchoice);
	bool humanMakeGuess();
	bool didHumanGetIt();
	Player retrieveHuman();
	Player retrieveRobot();
	void play();

private:
	Deck m_deck;
	Questions m_questions;
	std::vector<std::string> m_availquestions;
	std::vector<std::string> m_history;
	Player m_human;
	Player m_robot;
	bool humanGotIt = false;
	bool showHandOnce = false;

};

#endif // GAME_H