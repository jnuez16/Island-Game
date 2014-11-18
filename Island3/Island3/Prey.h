#include "stdafx.h"
#include "Animals.h"
#ifndef PREY_H
#define PREY_H

class Prey: public Animals
{
private:
	int HPgain;
public:
	Prey();
	Prey(int HPlost, int chance, int HPgain);
	void setHPgain(int HPgain);
	int getHPgain();
};


#endif