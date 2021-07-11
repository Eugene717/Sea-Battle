#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Constants.h"
#include "Ships.h"
#include "Point.h"
#include <deque>

class Player
{
	const char& m_player;
protected:
	std::deque<std::unique_ptr<Ship>> m_Ships;
public:
	char m_Board[ROW][COL]{ };
	Player(const char& player);
	~Player();
	bool Loss() const;
	void RandomShipsArrangement();
	void SearchDead();
	virtual bool Shoot(char(&enemy)[ROW][COL]) = 0;	
};

#endif // !PLAYER_H