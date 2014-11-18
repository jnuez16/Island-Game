#include "stdafx.h"
#include "Player.h"

Player::Player(int health, int attack) //constructor to give the player health and attack
{
	setHealth(health);
	setAttack(attack);
}

void Player::setHealth(int health) //function that sets health
{
	this->health = health;
}

void Player::setAttack(int attack) //function that sets the attack
{
	this->attack = attack;
}

int Player::getHealth() //access to health
{
	return health;
}

int Player::getAttack() //access to attack
{
	return attack;
}

void Player::healthGain(int gain) //allows for health gain
{
	health += gain;
}

void Player::healthLost(int lost) // allows for health lost
{
	health -= lost;
}

void Player::attackGain(int aGain) //allows for attack gain
{
	attack += aGain;
}

void Player::attackLost(int aLost) //allows for attack gain
{
	attack -= aLost;
}







