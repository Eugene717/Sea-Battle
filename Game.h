#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <conio.h>
#include "Constants.h"
#include "Players.h"
#include "Ships.h"

char Yes_or_No();

class Game
{
	Player* m_first;   
	Player* m_second; 

	char FirstTurn();
	void AskDisposition();
	void AnnounceWinner(int player);
	friend class AI;	
public:
	void Draw();
	int Menu();
	void SinglePlayer();
	//void LanGame();
	//void OnlineGame();
};

#endif // !GAME_H