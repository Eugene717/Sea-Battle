#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Ships.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Player
{
	const char& m_player;
protected:
	std::vector<std::unique_ptr<Ship>> m_Ships;
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