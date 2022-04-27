#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>
#include "Constants.h"

class Ship;

class Player
{
	const int m_board_number;
	const char& m_player;
protected:
	std::vector<std::unique_ptr<Ship>> m_Ships;
public:
	char m_Board[ROW][COL]{ };
	Player(const char& player, const int& board_number);
	~Player();
	bool Loss() const;
	void RandomShipsArrangement();
	void SetShipPos(const int& i, const int& x, const int& y, const bool& horiz);
	void CleardBoard();
	void SearchDead();
	virtual bool Shoot(char(&enemy)[ROW][COL]) = 0;	
};

#endif // !PLAYER_H