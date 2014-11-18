#include "stdafx.h"
#ifndef ANIMALS_H
#define ANIMALS_H

class Animals
{
private:
	int HPlost;
	int chance;
public:
	Animals();
	Animals(int HPlost, int chance);
	void setHPlost(int HPlost);
	void setChance(int chance);
	int getHPlost();
	int getChance();
};


#endif