#include "stdafx.h"
#include "Prey.h"

Prey::Prey(int HPlost, int chance, int HPgain) //sets the status for the prey
{
	setHPlost(HPlost);
	setChance(chance);
	setHPgain(HPgain);
}

void Prey::setHPgain(int HPgain) //sets the health gain
{
	this->HPgain = HPgain;
}

int Prey::getHPgain()//access to the health gain
{
	return HPgain;
}
