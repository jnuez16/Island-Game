#include "stdafx.h"
#include "Animals.h"
#ifndef PREDATOR_H
#define PREDATOR_H

class Predator: public Animals
{
private:
	int APgain;
public:
	Predator();
	Predator(int HPlost, int chance, int APgain);
	void setAPgain(int APgain);
	int getAPgain();

};

#endif