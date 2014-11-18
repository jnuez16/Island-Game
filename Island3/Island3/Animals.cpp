#include "stdafx.h"
#include "Animals.h"

Animals::Animals() //default constructor: initializes variables to zero
{
	HPlost = 0;
	chance = 0;
}


Animals::Animals(int HPlost, int chance) //constructor: sets values for the variables HPlost and chance
{
	setHPlost(HPlost);
	setChance(chance);
}

void Animals::setHPlost(int HPlost) //sets the values for HPlost
{
	this->HPlost = HPlost;
}

void Animals::setChance(int chance)//sets the values for chance
{
	this->chance = chance;
}

int Animals::getHPlost()//allows you to access the private variable HPlost
{
	return HPlost;
}

int Animals::getChance()//allows you to access the private variable chance
{
	return chance;
}
