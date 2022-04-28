#pragma once
#include "Player.h"

struct AI_IMPL;

class AI :public Player
{
	AI_IMPL* m_pImpl;

	bool Shoot1Deck(char(&enemy)[ROW][COL]);
	bool Shoot2Deck(char(&enemy)[ROW][COL]);
	bool Shoot3Deck(char(&enemy)[ROW][COL]);
	bool Shoot4Deck(char(&enemy)[ROW][COL]);
public:
	AI(const char& player = ENEMY_ALIVE);
	~AI();
	void SankShip(const char(&enemy)[ROW][COL]);
	bool Shoot(char(&enemy)[ROW][COL]) override;
};

