#pragma once
#include "Ship.h"

class Twin_Ship :public Ship
{
	std::vector<sf::Vector2f> Zone(char(&arr)[ROW][COL], const bool& draw = false) const;
public:
	Twin_Ship();
	~Twin_Ship();
	void RandomlyArrange(char(&arr)[ROW][COL], char player) override;
	bool Kill(char(&arr)[ROW][COL], const int& board) override;
};
