#pragma once
#include "Ship.h"

class Triple_Ship :public Ship
{
	std::vector<sf::Vector2f> Zone(char(&arr)[ROW][COL], const bool& draw = false) const;
public:
	Triple_Ship();
	~Triple_Ship();
	void SetPos(const int& x, const int& y, const bool& horiz) override;
	void RandomlyArrange(char(&arr)[ROW][COL], char player) override;
	bool Kill(char(&arr)[ROW][COL], const int& board) override;
};
