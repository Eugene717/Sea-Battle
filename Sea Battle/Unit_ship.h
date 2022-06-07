#pragma once
#include "Ship.h"

class Unit_Ship :public Ship
{
	std::vector<sf::Vector2f> Zone(char(&arr)[ROW][COL], const bool& draw = false) const;
public:
	Unit_Ship();
	~Unit_Ship();
	void SetPos(const int& x, const int& y, char(&arr)[ROW][COL], const char& player) override;
	void RandomlyArrange(char(&arr)[ROW][COL], const char& player) override;
	void SetMPPos(char(&arr)[ROW][COL]) override;
	bool Kill(char(&arr)[ROW][COL], const int& board) override;

	friend sf::Packet& operator<<(sf::Packet& packet, Unit_Ship* m);
	friend sf::Packet& operator>>(sf::Packet& packet, Unit_Ship* m);
};

