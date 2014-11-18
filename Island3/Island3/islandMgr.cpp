#include "stdafx.h"
#include "islandMgr.h"
using namespace std;


islandMgr::islandMgr() //initializes 
{
	int x = 1;
	day = 0;
	rescueDate = (rand()%10)+10;
	gameOver = false;
	playerPlace = false;
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			player[i][j] = false;
			board[i][j] = x;
			x++;
		}

	}


	Tile First(1, 20);
	Tile Second(2, 25);
	Tile Third(3, 20);
	Tile Fourth(4, 30);
	Tile Fifth(5, 25);
	Tile Sixth(6, 20);
	Tile Seventh(7, 30);
	Tile Eighth(8, 25);
	Tile Ninth(9, 20);

	isletile.push_back(First);
	isletile.push_back(Second);
	isletile.push_back(Third);
	isletile.push_back(Fourth);
	isletile.push_back(Fifth);
	isletile.push_back(Sixth);
	isletile.push_back(Seventh);
	isletile.push_back(Eighth);
	isletile.push_back(Ninth);


}

void Reset(islandMgr &imgr) //resets the game
{
	srand(time(NULL));
	int x = 0;
	imgr.day = 0;
	imgr.rescueDate = (rand()%10)+10;
	imgr.gameOver = false;
	imgr.playerPlace = false;
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			imgr.player[i][j] = false;
			imgr.board[i][j] = x;
			x++;
		}

	}

}

void DrawGrid(Player &pl, islandMgr &imgr, HWND hwnd, HDC hdc) //Draws the grid over the image
{
	//Draws 9x9 grid
	MoveToEx(hdc,200,100,NULL); LineTo(hdc,200,400);
	MoveToEx(hdc,300,100,NULL); LineTo(hdc,300,400);
	MoveToEx(hdc,100,200,NULL); LineTo(hdc,400,200);
	MoveToEx(hdc,100,300,NULL); LineTo(hdc,400,300);
	//Draw the Box around the grid
	MoveToEx(hdc, 100, 100, NULL); LineTo(hdc, 100, 400);
	MoveToEx(hdc, 400, 100, NULL); LineTo(hdc, 400, 400);
	MoveToEx(hdc, 100, 100, NULL); LineTo(hdc, 400, 100);
	MoveToEx(hdc, 100, 400, NULL); LineTo(hdc, 400, 400);

	//draws the texts
	HGDIOBJ fnt = GetStockObject(ANSI_VAR_FONT);
	HGDIOBJ fntOld = SelectObject(hdc, fnt);

	string health = "Health: ";
	char hbuf[4];
	health = health + itoa(pl.getHealth(), hbuf, 10);

	string rescueDate = "Rescue date: ";
	char hbuf1[3];
	rescueDate = rescueDate + itoa(imgr.rescueDate, hbuf1, 10);

	string day = "Day: ";
	day = day + itoa(imgr.day, hbuf1, 10);

	string att = "Attack: ";
	att = att + itoa(pl.getAttack(), hbuf1, 10);

	TextOut(hdc, 100, 10, health.c_str(), 11);
	TextOut(hdc, 100, 25, rescueDate.c_str(), 15);
	TextOut(hdc, 100, 40, day.c_str(), 7);
	TextOut(hdc, 300, 10, att.c_str(), 10);

	if(imgr.gameOver == true && pl.getHealth() > 0)
	{
		TextOut(hdc, 200, 200, "You Survived!", 15);
	}

	if(imgr.gameOver == true && pl.getHealth() <= 0)
	{
		TextOut(hdc, 200, 200, "YOU DIED!", 10);
	}

	SelectObject(hdc, fntOld);


	for (int i=0; i<3; i++) 
	{
		for (int j=0; j<3; j++) 
		{
			if(imgr.playerPlace == true) //deletes the previous mark
			{
				for(int i = 0; i < row; i++)
				{
					for(int j = 0; j < col; j++)
					{
						imgr.player[i][j] = false;
						imgr.playerPlace = false;
					}

				}
			}

			if (imgr.player[i][j] == true) //marks the players location
			{
				DrawPlayer(hdc, i, j);
				imgr.day++;
				imgr.playerPlace = true;
			}

		}
	}
}

void SetMove(islandMgr &imgr, int i, int j)
{

	if(i >= 0 && i <= 2 && j >= 0 && j <= 2)
	{
		if(imgr.gameOver == false)
		{
			imgr.player[i][j] = true; //allows the player to place a piece on the intended tile/box/array
		}

	}

}

void CheckWinner(Player &pl, islandMgr &imgr, HWND hwnd)
{
	if(imgr.day == imgr.rescueDate || pl.getHealth() <= 0) //tells the program that the game is over
		imgr.gameOver = true;
	

}

void DrawPlayer(HDC hdc, int i, int j) //Draws the player on the grid
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	HBRUSH brush = CreateHatchBrush(HS_DIAGCROSS, RGB(254, 254, 254));
	HGDIOBJ penOld, brushOld;

	penOld = SelectObject(hdc, pen);
	brushOld = SelectObject(hdc, brush);

	Ellipse(hdc, 110 + (100*(i)), 110 + (100*(j)), 190 + (100*(i)), 190 + (100*(j)));

	SelectObject(hdc, brushOld);
	SelectObject(hdc, penOld);

	DeleteObject(brush);
	DeleteObject(pen);

}

void HPup(Prey hunt, Player &pl) //function to let the player gain health
{
	pl.healthGain(hunt.getHPgain());
}

void HPdown(Prey hunt, Player &pl) //function to let the player to lose health
{
	pl.healthLost(hunt.getHPlost());
}

void train(Player &pl) //allows the player to lose health and gain attack
{
	pl.healthLost(10);
	pl.attackGain(2);
}

void rest(Player &pl) //allows the player to lose attack and gain health
{
	pl.attackLost(1);
	pl.healthGain(10);
}

void fight(Player &pl, Predator &prd) //allows the player to fight off predator at a gain or cost
{
	srand(time(NULL));
	int x = (rand()% pl.getAttack())*2;
	if(x > pl.getAttack())
	{
		pl.healthLost(30);
	}
	else
	{
		pl.attackGain(prd.getAPgain());
	}


	
}

void run(Player &pl) //allows the player to run while losing health
{
	pl.healthLost(15);
}



