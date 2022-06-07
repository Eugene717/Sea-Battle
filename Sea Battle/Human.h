#pragma once
#include "Player.h"

class Human :public Player
{
public:
	Human(const char& player, const int& board_number);
	bool Shoot(char(&enemy)[ROW][COL]) override;
	bool ShootMP(char(&enemy)[ROW][COL], sf::TcpSocket& socket);
	bool SetDisposition();
};
