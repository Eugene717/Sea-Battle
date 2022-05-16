#pragma once
#include "Ship.h"

class Quadraple_Ship :public Ship
{
	std::vector<sf::Vector2f> Zone(char(&arr)[ROW][COL], const bool& draw = false) const;
public:
	Quadraple_Ship();
	~Quadraple_Ship();
	void SetPos(const int& x, const int& y, char(&arr)[ROW][COL], const char& player) override;
	void RandomlyArrange(char(&arr)[ROW][COL], const char& player) override;
	bool Kill(char(&arr)[ROW][COL], const int& board) override;
};

