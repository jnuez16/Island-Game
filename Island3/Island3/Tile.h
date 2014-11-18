#include "stdafx.h"
#ifndef TILE_H
#define TILE_H

class Tile
{
private:
	int location;
	int rate;
public:
	Tile(int location, int rate);
	void setRate(int rate);
	void setLoc(int location);
	int getRate();
	int getLoc();
};

#endif