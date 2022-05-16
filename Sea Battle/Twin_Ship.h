#pragma once
#include "Ship.h"

class Twin_Ship :public Ship
{
	std::vector<sf::Vector2f> Zone(char(&arr)[ROW][COL], const bool& draw = false) const;
public:
	Twin_Ship();
	~Twin_Ship();
	void SetPos(const int& x, const int& y, char(&arr)[ROW][COL], const char& player) override;
	void RandomlyArrange(char(&arr)[ROW][COL], const char& player) override;
	bool Kill(char(&arr)[ROW][COL], const int& board) override;
};
