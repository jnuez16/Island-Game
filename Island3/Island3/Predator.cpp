#include "stdafx.h"
#include "Predator.h"

Predator::Predator(int HPlost, int chance, int APgain) //sets the predators status
{
	setHPlost(HPlost);
	setChance(chance);
	setAPgain(APgain);
}

void Predator::setAPgain(int APgain) // sets the predators attack points gained
{
	this->APgain = APgain;
}

int Predator::getAPgain() //access to attack points gained
{
	return APgain;
}
