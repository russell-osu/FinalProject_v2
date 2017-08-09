// this is a header file for Combat.cpp

#ifndef MOON_COMBAT_HPP
#define MOON_COMBAT_HPP

#include <memory>
#include "Creature.hpp"
#include <string>

using std::string;
using std::shared_ptr;

class Combat
{
private:
	shared_ptr<Creature> creat1;
	shared_ptr<Creature> creat2;

public:
	void engage();
	void chooseCreatures();
	void runTrials();
	void changeStrength();

	Combat();
	~Combat();
};

#endif
