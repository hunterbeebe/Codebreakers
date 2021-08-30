#include "Game.h"

Game::Game() {
	dealCards();
	dealQuestions();
}

int Game::dealCards() {
	m_deck.shuffle();	// shuffle the deck
	for (int i = 0; i < 5; i++) {
		m_human.addCardtoHand(m_deck.draw());	// draw cards for the human
	}
	m_human.sortHand();	// sort the humans hand
	for (int j = 0; j < 5; j++) {
		m_robot.addCardtoHand(m_deck.draw());	// draw cards for the robot
	}
	m_robot.sortHand();	// sort the robots hand
	std::vector<std::string> humstring = m_human.giveStringHand();	// set up the history function by adding in a recap of every card the player has
	m_history.push_back("Your cards are " + humstring[0] + ", " + humstring[1] + ", " + humstring[2] + ", " + humstring[3] + ", " + humstring[4]);
	m_history.push_back("You know the following about your opponent's cards: ");
	return 1;
}

int Game::dealQuestions() {
	m_questions.shuffle();
	for (int i = 0; i < 6; i++) {
		m_availquestions.push_back(m_questions.draw());	// draw the top 6 question cards and get them ready to display
	}
	return 1;
}

void Game::displayboard() {
	std::vector<card> humanhand = m_human.giveHand();	// Get the players hand and display each value along with color
	if (showHandOnce == false) {
		std::cout << "Your cards are: " << std::endl;
		std::cout << "a) " << humanhand[0].color << " " << humanhand[0].value << std::endl;
		std::cout << "b) " << humanhand[1].color << " " << humanhand[1].value << std::endl;
		std::cout << "c) " << humanhand[2].color << " " << humanhand[2].value << std::endl;
		std::cout << "d) " << humanhand[3].color << " " << humanhand[3].value << std::endl;
		std::cout << "e) " << humanhand[4].color << " " << humanhand[4].value << std::endl;


		//std::vector<std::string> robothand = m_robot.giveStringHand();	// (for testing) display the robot's hand as well
		//std::cout << "The robot's cards are: " << std::endl;
		//std::cout << "a) " << robothand[0] << std::endl;
		//std::cout << "b) " << robothand[1] << std::endl;
		//std::cout << "c) " << robothand[2] << std::endl;
		//std::cout << "d) " << robothand[3] << std::endl;
		//std::cout << "e) " << robothand[4] << std::endl;

		std::cout << std::endl;
	} 
	showHandOnce = true;
	std::cout << "The questions you can choose from are: " << std::endl;	// list the questions that are available to be asked
	for (int i = 0; i < 6; i++) {
		std::cout << i+1 << ") " << m_availquestions[i] << std::endl;
	}
}

void Game::humanTakeTurn() {
	std::string response;
	response = "0";
	//displayboard();
	std::cout << std::endl;
	std::cout << "If you would like to ask a question, type the number of it" << std::endl;	// prompt the player with their options
	std::cout << "Otherwise, if you want to guess, type Guess" << std::endl;
	std::cout << "Lastly, if you would like a recap of the information you know, type Recap" << std::endl << std::endl;
	while (response != "1" && response != "2" && response != "3" && response != "4" && response != "5" && response != "6" && response != "Guess" && 
		response != "guess" && response != "recap" && response != "Recap") {	// make sure the response is reasonable before continuing
		std::getline(std::cin, response);
	} 
	if (response == "Recap" || response == "recap") {
		std::cout << std::endl << "Your information: " << std::endl;	// if they asked for a recap, print out the history member
		for (auto iterator = m_history.begin(); iterator != m_history.end(); iterator++) {
			std::cout << *iterator << std::endl;
		}
		std::cout << std::endl << std::endl;
		std::string presstocontinue;
		std::getline(std::cin, presstocontinue);
	}
	else if (response == "Guess" || response == "guess") {
		if (humanMakeGuess()) {	// if they want to make a guess, delegate it to the guess member function and see if they were right
			humanGotIt = true;
		}
		if (!humanGotIt) {
			std::cout << "Incorrect" << std::endl << std::endl;
		}
	}
	else {
		std::cout << humanAskQuestion(response) << std::endl << std::endl; /*<< "Press enter to continue" << std::endl;*/	// otherwise, they're asking a question, call that function
		std::string presstocontinue;
		std::getline(std::cin, presstocontinue);
	}
}

std::string Game::humanAskQuestion(std::string qchoice) {
	int qnumber = std::stoi(qchoice);
	std::string qprompt = m_availquestions[qnumber - 1];
	m_availquestions[qnumber - 1] = m_questions.draw();
	std::cout << "You asked: " + qprompt << std::endl;
	std::string answer = QuestionResolver(qprompt, m_robot);
	m_history.push_back(answer);
	return answer;
}

bool Game::humanMakeGuess() {

	std::vector<std::string> robothand = m_robot.giveStringHand();


	std::string first;
	std::string second;
	std::string third;
	std::string fourth;
	std::string fifth;
	std::cout << "The format of a guess is: 'White 2', 'Green 5', etc." << std::endl;
	std::cout << "You will enter the guesses one by one, and be told if you are correct at the end." << std::endl;
	std::cout << "First card: ";
	std::getline(std::cin, first);
	std::cout << std::endl;
	std::cout << "Second card: ";
	std::getline(std::cin, second);
	std::cout << std::endl;
	std::cout << "Third card ";
	std::getline(std::cin, third);
	std::cout << std::endl;
	std::cout << "Fourth card: ";
	std::getline(std::cin, fourth);
	std::cout << std::endl;
	std::cout << "Fifth card: ";
	std::getline(std::cin, fifth);
	std::cout << std::endl;
	std::vector<std::string> guess;
	guess.push_back(first);
	guess.push_back(second);
	guess.push_back(third);
	guess.push_back(fourth);
	guess.push_back(fifth);
	bool correct = true;
	for (int i = 0; i < 5; i++) {
		if (guess[i] != robothand[i]) {
			correct = false;
		}
	}
	return correct;
}

Player Game::retrieveHuman() {
	return m_human;
}

Player Game::retrieveRobot() {
	return m_robot;
}

bool Game::didHumanGetIt() {
	return humanGotIt;
}

void Game::play() {
	while (humanGotIt == false) {
		displayboard();
		humanTakeTurn();
	}
	std::cout << std::endl << "You did it!" << std::endl;
}

std::string QuestionResolver(std::string qprompt, Player target) {
	std::vector<card> hand = target.giveHand();
	std::string answer;

	if (qprompt == "What is the total sum of your cards?") {
		int totalsum = 0;
		for (int i = 0; i < 5; i++) {
			totalsum += hand[i].value;
		}
		answer = "The total sum of the cards is " + std::to_string(totalsum);
	}

	if (qprompt == "What is the sum of your leftmost cards?") {
		int totalsum = 0;
		for (int i = 0; i < 3; i++) {
			totalsum += hand[i].value;
		}
		answer = "The sum of the leftmost cards is " + std::to_string(totalsum);
	}

	if (qprompt == "What is the sum of your middle cards?") {
		int totalsum = 0;
		for (int i = 1; i < 4; i++) {
			totalsum += hand[i].value;
		}
		answer = "The sum of the middle cards is " + std::to_string(totalsum);
	}

	if (qprompt == "What is the sum of your rightmost cards?") {
		int totalsum = 0;
		for (int i = 2; i < 5; i++) {
			totalsum += hand[i].value;
		}
		answer = "The sum of the rightmost cards is " + std::to_string(totalsum);
	}

	if (qprompt == "What is the sum of your black cards?") {
		int totalsum = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i].color == "Black") {
				totalsum += hand[i].value;
			}
		}
		answer = "The sum of the black cards is " + std::to_string(totalsum);
	}

	if (qprompt == "What is the sum of your white cards?") {
		int totalsum = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i].color == "White") {
				totalsum += hand[i].value;
			}
		}
		answer = "The sum of the white cards is " + std::to_string(totalsum);
	}

	if (qprompt == "How many odd cards do you have?") {
		int totalodd = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i].value % 2 != 0) {
				totalodd++;
			}
		}
		answer = "The number of odd cards is " + std::to_string(totalodd);
	}

	if (qprompt == "How many even cards do you have?") {
		int totaleven = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i].value % 2 == 0) {
				totaleven++;
			}
		}
		answer = "The number of even cards is " + std::to_string(totaleven);
	}

	if (qprompt == "Which of your cards are adjacent to a consecutive number?") {
		for (int i = 0; i < 4; i++) {
			if (hand[i + 1].value == hand[i].value + 1) {
				if (i == 0) {
					answer += "A B ";
				}
				if (i == 1) {
					if (answer == "A B ") {
						answer = "A B C ";
					}
					else {
						answer += "B C ";
					}
				}
				if (i == 2) {
					if (answer == "A B C ") {
						answer = "A B C D ";
					}
					else if (answer == "B C") {
						answer = "B C D ";
					}
					else {
						answer += "C D ";
					}
				}
				if (i == 3) {
					if (answer == "A B C D ") {
						answer = "A B C D E ";
					}
					else if (answer == "B C D ") {
						answer = "B C D E ";
					}
					else if (answer == "C D ") {
						answer = "C D E ";
					}
					else {
						answer += "D E ";
					} 
				}
			}
		}
		if (answer == "") {
			answer += "There are no cards adjacent to consecutive numbers";
		}
		else { 
			answer += "are adjacent to consecutive numbers"; 
		} 
	}

	if (qprompt == "How many pairs do you have?") {
		int totalpairs = 0;
		for (int i = 0; i < 4; i++) {
			if (hand[i + 1].value == hand[i].value) {
				totalpairs++;
			}
		}
		if (totalpairs == 0 || totalpairs == 1) {
			answer += "There are no pairs";
		}
		else {
			answer += "There number of pairs is " + std::to_string(totalpairs);
		}
	}

	if (qprompt == "Which adjacent cards of yours are the same color?") {
		for (int i = 0; i < 4; i++) {
			if (hand[i].color == hand[i + 1].color) {
				if (i == 0) {
					answer += "A and B";
				}
				if (i == 1) {
					if (answer == "A and B") {
						answer = "A, B, and C";
					}
					else {
						answer = "B and C";
					}
				}
				if (i == 2) {
					if (answer == "A, B, and C") {
						answer = "A, B, C, and D";
					}
					else if (answer == "B and C") {
						answer = "B, C, and D";
					}
					else if (answer == "A and B") {
						answer = "A and B, C and D";
					}
					else {
						answer = "C and D";
					}
				}
				if (i == 3) {
					if (answer == "A, B, C, and D") {
						answer = "All of the cards are the same color";
						return answer;
					}
					else if (answer == "A and B") {
						answer = "A and B, D and E";
					}
					else if (answer == "A, B, and C") {
						answer = "A and B, B and C, D and E";
					}
					else if (answer == "B and C") {
						answer = "B and C, D and E";
					}
					else if (answer == "B, C, and D") {
						answer = "B and C, D and E";
					}
					else if (answer == "A and B, C and D") {
						answer = "A and B, C and D, D and E";
					}
					else if (answer == "C and D") {
						answer = "C and D, D and E";
					}
					else {
						answer = "D and E";
					}

				}
			}
		}
		if (answer == "") {
			answer = "There are no adjacent cards that are the same color";
		}
		else {
			answer += " are the adjacent cards that are the same color";
		} 
	}

	if (qprompt == "How many black cards do you have?") {
		int blackcards = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i].color == "Black") {
				blackcards++;
			}
		}
		answer += "The number of black cards is " + std::to_string(blackcards);
	}

	if (qprompt == "How many white cards do you have?") {
		int whitecards = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i].color == "White") {
				whitecards++;
			}
		}
		answer += "The number of white cards is " + std::to_string(whitecards);
	}

	if (qprompt == "How many green cards do you have?") {
		int greencards = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i].color == "Green") {
				greencards++;
			}
		}
		answer += "The number of green cards is " + std::to_string(greencards);
	}

	if (qprompt == "Where are your 0's?") {
		if (hand[0].value == 0 && hand[1].value == 0) {
			answer = "There is a 0 in A and B";
		}
		else if (hand[0].value == 0 && hand[1].value != 0) {
			answer = "There is a 0 in A";
		}
		else {
			answer = "There are no 0's";
		}
	}

	if (qprompt == "Where are your 1's or 2's?") {
		std::string choice = "0";
		std::cout << "1 or 2?" << std::endl;
		while (choice != "1" && choice != "2") {
			std::getline(std::cin, choice);
		} 
		if (choice == "1") {
			int howmany = 0;
			for (int i = 0; i < 5; i++) {
				if (hand[i].value == 1) {
					howmany++;
				}
			}
			if (howmany == 0) {
				answer = "There are no 1's";
			}
			if (howmany == 1) {
				for (int j = 0; j < 5; j++) {
					if (hand[j].value == 1) {
						if (j == 0) {
							answer = "There is a 1 in A";
						}
						if (j == 1) {
							answer = "There is a 1 in B";
						}
						if (j == 2) {
							answer = "There is a 1 in C";
						}
					}
				}
			}
			if (howmany == 2) {
				bool done = false;
				for (int k = 0; k < 5; k++) {
					if (hand[k].value == 1 && !done) {
						if (k == 0) {
							done = true;
							answer = "There is a 1 in A and B";
						}
						if (k == 1) {
							done = true;
							answer = "There is a 1 in B and C";
						}
						if (k == 2) {
							done = true;
							answer = "There is a 1 in C and D";
						}
					}
				}
			}
		}
		if (choice == "2") {
			int howmany = 0;
			for (int i = 0; i < 5; i++) {
				if (hand[i].value == 2) {
					howmany++;
				}
			}
			if (howmany == 0) {
				answer = "There are no 2's";
			}
			if (howmany == 1) {
				for (int j = 0; j < 5; j++) {
					if (hand[j].value == 2) {
						if (j == 0) {
							answer = "There is a 2 in A";
						}
						if (j == 1) {
							answer = "There is a 2 in B";
						}
						if (j == 2) {
							answer = "There is a 2 in C";
						}
						if (j == 3) {
							answer = "There is a 2 in D";
						}
						if (j == 4) {
							answer = "There is a 2 in E";
						}
					}
				}
			}
			if (howmany == 2) {
				bool done = false;
				for (int k = 0; k < 5; k++) {
					if (hand[k].value == 2 && !done) {
						if (k == 0) {
							done = true;
							answer = "There is a 2 in A and B";
						}
						if (k == 1) {
							done = true;
							answer = "There is a 2 in B and C";
						}
						if (k == 2) {
							done = true;
							answer = "There is a 2 in C and D";
						}
						if (k == 3) {
							done = true;
							answer = "There is a 2 in D and E";
						}
					}
				}
			}
		}

	}

	if (qprompt == "Where are your 3's or 4's?") {
		std::string choice = "0";
		std::cout << "3 or 4?" << std::endl;
		while (choice != "3" && choice != "4") {
			std::getline(std::cin, choice);
		}
		if (choice == "3") {
			int howmany = 0;
			for (int i = 0; i < 5; i++) {
				if (hand[i].value == 3) {
					howmany++;
				}
			}
			if (howmany == 0) {
				answer = "There are no 3's";
			}
			if (howmany == 1) {
				for (int j = 0; j < 5; j++) {
					if (hand[j].value == 3) {
						if (j == 0) {
							answer = "There is a 3 in A";
						}
						if (j == 1) {
							answer = "There is a 3 in B";
						}
						if (j == 2) {
							answer = "There is a 3 in C";
						}
						if (j == 3) {
							answer = "There is a 3 in D";
						}
						if (j == 4) {
							answer = "There is a 3 in E";
						}
					}
				}
			}
			if (howmany == 2) {
				bool done = false;
				for (int k = 0; k < 5; k++) {
					if (hand[k].value == 3 && !done) {
						if (k == 0) {
							done = true;
							answer = "There is a 3 in A and B";
						}
						if (k == 1) {
							done = true;
							answer = "There is a 3 in B and C";
						}
						if (k == 2) {
							done = true;
							answer = "There is a 3 in C and D";
						}
						if (k == 3) {
							done = true;
							answer = "There is a 3 in D and E";
						}
					}
				}
			}
		}
		if (choice == "4") {
			int howmany = 0;
			for (int i = 0; i < 5; i++) {
				if (hand[i].value == 4) {
					howmany++;
				}
			}
			if (howmany == 0) {
				answer = "There are no 4's";
			}
			if (howmany == 1) {
				for (int j = 0; j < 5; j++) {
					if (hand[j].value == 4) {
						if (j == 0) {
							answer = "There is a 4 in A";
						}
						if (j == 1) {
							answer = "There is a 4 in B";
						}
						if (j == 2) {
							answer = "There is a 4 in C";
						}
						if (j == 3) {
							answer = "There is a 4 in D";
						}
						if (j == 4) {
							answer = "There is a 4 in E";
						}
					}
				}
			}
			if (howmany == 2) {
				bool done = false;
				for (int k = 0; k < 5; k++) {
					if (hand[k].value == 4 && !done) {
						if (k == 0) {
							done = true;
							answer = "There is a 4 in A and B";
						}
						if (k == 1) {
							done = true;
							answer = "There is a 4 in B and C";
						}
						if (k == 2) {
							done = true;
							answer = "There is a 4 in C and D";
						}
						if (k == 3) {
							done = true;
							answer = "There is a 4 in D and E";
						}
					}
				}
			}
		}
	}

	if (qprompt == "Where are your 5's?") {
		int howmany = 0;
		for (int i = 0; i < 5; i++) {
			if (hand[i].value == 5) {
				howmany++;
			}
		}
		if (howmany == 0) {
			answer = "There are no 5's";
		}
		if (howmany == 1) {
			for (int j = 0; j < 5; j++) {
				if (hand[j].value == 5) {
					if (j == 0) {
						answer = "There is a 5 in A";
					}
					if (j == 1) {
						answer = "There is a 5 in B";
					}
					if (j == 2) {
						answer = "There is a 5 in C";
					}
					if (j == 3) {
						answer = "There is a 5 in D";
					}
					if (j == 4) {
						answer = "There is a 5 in E";
					}
				}
			}
		}
		if (howmany == 2) {
			bool done = false;
			for (int k = 0; k < 5; k++) {
				if (hand[k].value == 5 && !done) {
					if (k == 0) {
						done = true;
						answer = "There is a 5 in A and B";
					}
					if (k == 1) {
						done = true;
						answer = "There is a 5 in B and C";
					}
					if (k == 2) {
						done = true;
						answer = "There is a 5 in C and D";
					}
					if (k == 3) {
						done = true;
						answer = "There is a 5 in D and E";
					}
				}
			}
		}

	}

	if (qprompt == "Where are your 6's or 7's?") {
		std::string choice = "0";
		std::cout << "6 or 7?" << std::endl;
		while (choice != "6" && choice != "7") {
			std::getline(std::cin, choice);
		}
		if (choice == "6") {
			int howmany = 0;
			for (int i = 0; i < 5; i++) {
				if (hand[i].value == 6) {
					howmany++;
				}
			}
			if (howmany == 0) {
				answer = "There are no 6's";
			}
			if (howmany == 1) {
				for (int j = 0; j < 5; j++) {
					if (hand[j].value == 6) {
						if (j == 0) {
							answer = "There is a 6 in A";
						}
						if (j == 1) {
							answer = "There is a 6 in B";
						}
						if (j == 2) {
							answer = "There is a 6 in C";
						}
						if (j == 3) {
							answer = "There is a 6 in D";
						}
						if (j == 4) {
							answer = "There is a 6 in E";
						}
					}
				}
			}
			if (howmany == 2) {
				bool done = false;
				for (int k = 0; k < 5; k++) {
					if (hand[k].value == 6 && !done) {
						if (k == 0) {
							done = true;
							answer = "There is a 6 in A and B";
						}
						if (k == 1) {
							done = true;
							answer = "There is a 6 in B and C";
						}
						if (k == 2) {
							done = true;
							answer = "There is a 6 in C and D";
						}
						if (k == 3) {
							done = true;
							answer = "There is a 6 in D and E";
						}
					}
				}
			}
		}
		if (choice == "7") {
			int howmany = 0;
			for (int i = 0; i < 5; i++) {
				if (hand[i].value == 7) {
					howmany++;
				}
			}
			if (howmany == 0) {
				answer = "There are no 7's";
			}
			if (howmany == 1) {
				for (int j = 0; j < 5; j++) {
					if (hand[j].value == 7) {
						if (j == 0) {
							answer = "There is a 7 in A";
						}
						if (j == 1) {
							answer = "There is a 7 in B";
						}
						if (j == 2) {
							answer = "There is a 7 in C";
						}
						if (j == 3) {
							answer = "There is a 7 in D";
						}
						if (j == 4) {
							answer = "There is a 7 in E";
						}
					}
				}
			}
			if (howmany == 2) {
				bool done = false;
				for (int k = 0; k < 5; k++) {
					if (hand[k].value == 7 && !done) {
						if (k == 0) {
							done = true;
							answer = "There is a 7 in A and B";
						}
						if (k == 1) {
							done = true;
							answer = "There is a 7 in B and C";
						}
						if (k == 2) {
							done = true;
							answer = "There is a 7 in C and D";
						}
						if (k == 3) {
							done = true;
							answer = "There is a 7 in D and E";
						}
					}
				}
			}
		}
	}

	if (qprompt == "Where are your 8's or 9's?") {
		std::string choice = "0";
		std::cout << "8 or 9?" << std::endl;
		while (choice != "8" && choice != "9") {
			std::getline(std::cin, choice);
		}
		if (choice == "8") {
			int howmany = 0;
			for (int i = 0; i < 5; i++) {
				if (hand[i].value == 8) {
					howmany++;
				}
			}
			if (howmany == 0) {
				answer = "There are no 8's";
			}
			if (howmany == 1) {
				for (int j = 0; j < 5; j++) {
					if (hand[j].value == 8) {
						if (j == 0) {
							answer = "There is an 8 in A";
						}
						if (j == 1) {
							answer = "There is an 8 in B";
						}
						if (j == 2) {
							answer = "There is an 8 in C";
						}
						if (j == 3) {
							answer = "There is an 8 in D";
						}
						if (j == 4) {
							answer = "There is an 8 in E";
						}
					}
				}
			}
			if (howmany == 2) {
				bool done = false;
				for (int k = 0; k < 5; k++) {
					if (hand[k].value == 8 && !done) {
						if (k == 0) {
							done = true;
							answer = "There is an 8 in A and B";
						}
						if (k == 1) {
							done = true;
							answer = "There is an 8 in B and C";
						}
						if (k == 2) {
							done = true;
							answer = "There is an 8 in C and D";
						}
						if (k == 3) {
							done = true;
							answer = "There is an 8 in D and E";
						}
					}
				}
			}
		}
		if (choice == "9") {
			int howmany = 0;
			for (int i = 0; i < 5; i++) {
				if (hand[i].value == 9) {
					howmany++;
				}
			}
			if (howmany == 0) {
				answer = "There are no 9's";
			}
			if (howmany == 1) {
				for (int j = 0; j < 5; j++) {
					if (hand[j].value == 9) {
						if (j == 0) {
							answer = "There is a 9 in A";
						}
						if (j == 1) {
							answer = "There is a 9 in B";
						}
						if (j == 2) {
							answer = "There is a 9 in C";
						}
						if (j == 3) {
							answer = "There is a 9 in D";
						}
						if (j == 4) {
							answer = "There is a 9 in E";
						}
					}
				}
			}
			if (howmany == 2) {
				bool done = false;
				for (int k = 0; k < 5; k++) {
					if (hand[k].value == 9 && !done) {
						if (k == 0) {
							done = true;
							answer = "There is a 9 in A and B";
						}
						if (k == 1) {
							done = true;
							answer = "There is a 9 in B and C";
						}
						if (k == 2) {
							done = true;
							answer = "There is a 9 in C and D";
						}
						if (k == 3) {
							done = true;
							answer = "There is a 9 in D and E";
						}
					}
				}
			}
		}
	}

	if (qprompt == "Is your middle card greater than 4?") {
		if (hand[2].value > 4) {
			answer = "The middle card is greater than 4";
		}
		else {
			answer = "The middle card is not greater than 4";
		}
	}

	if (qprompt == "What is the difference between your largest and smallest number?") {
		int diff = hand[4].value - hand[0].value;
		answer = "The difference between the largest and smallest number is " + std::to_string(diff);
	}

	return answer;
}