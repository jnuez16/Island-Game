#include "stdafx.h"
#include "Tile.h"

Tile::Tile(int location, int rate) //initializes the variables
{
	
	setLoc(location);
	setRate(rate);
}

void Tile::setLoc(int location) //sets the location of the tile
{
	this->location = location;
}

void Tile::setRate(int rate) //sets the rate of each tile
{
	this->rate = rate;
}

int Tile::getLoc()//access to the location
{
	return location;
}

int Tile::getRate()//access to the rate
{
	return rate;
}



