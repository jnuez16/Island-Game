
#include "stdafx.h"
#include "Tile.h"
#include "Prey.h"
#include "Predator.h"
#include "Player.h"
#include <vector>
#include <string>
#include <ctime>

using namespace std;

const int row = 3;
const int col = 3;

class islandMgr
{
public:
	int board[row][col];
	int rescueDate;
	int day;
	//bool xMove;
	bool player[row][col];
	bool playerPlace;
	bool gameOver;
	vector<Tile> isletile;


	islandMgr();
};

void Reset(islandMgr &imgr);
void DrawGrid(Player &pl, islandMgr &imgr, HWND hwnd, HDC hdc);
void SetMove(islandMgr &imgr, int i, int j);
void CheckWinner(Player &pl, islandMgr &imgr, HWND hwnd);
void DrawPlayer(HDC hdc, int i, int j);
void HPup(Prey hunt, Player &pl);
void HPdown(Prey hunt, Player &pl);
void train(Player &pl);
void rest(Player &pl);
void fight(Player &pl, Predator &prd);
void run(Player &pl);
//string text(string s, int i);
//void DrawO(HDC hdc, int i, int j);