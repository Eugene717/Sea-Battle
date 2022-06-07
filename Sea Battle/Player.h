#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <sfml/Network.hpp>
#include <vector>
#include <memory>
#include "Constants.h"

class Ship;

class Player
{
	const char& m_player;
protected:
	std::vector<std::unique_ptr<Ship>> m_Ships;
	const int m_board_number;
public:
	char m_Board[ROW][COL]{ };
	Player(const char& player, const int& board_number);
	~Player();
	bool Loss() const;
	void RandomShipsArrangement();
	void CleardBoard();
	bool SearchDead();
	virtual bool Shoot(char(&enemy)[ROW][COL]) = 0;	
	void SendShips(sf::Packet& packet);
	void GetShips(sf::Packet& packet);
};

#endif // !PLAYER_H