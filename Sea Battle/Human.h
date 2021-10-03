#pragma once
#include "Player.h"

class Human :public Player
{
public:
	Human(const char& player);
	bool Shoot(char(&enemy)[ROW][COL], sf::RenderWindow& window) override;
};
