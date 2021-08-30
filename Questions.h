#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <vector>
#include <algorithm>          
#include <random>  
#include <time.h>

class Questions {
public:
	Questions();
	void shuffle();
	std::string draw();
private:
	std::vector<std::string> m_qcards;
};

#endif
