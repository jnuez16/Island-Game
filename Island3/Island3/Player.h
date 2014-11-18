#include "stdafx.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
	int health;
	int attack;
public:
	Player();
	Player(int health, int attack);
	void setHealth(int health);
	void setAttack(int attack);
	int getHealth();
	int getAttack();
	void healthGain(int gain);
	void healthLost(int lost);
	void attackGain(int aGain);
	void attackLost(int aLost);
};

#endif