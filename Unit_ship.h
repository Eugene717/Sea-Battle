#pragma once
#include "Ship.h"

class Unit_Ship :public Ship
{
public:
	Unit_Ship();
	~Unit_Ship();
	void RandomlyArrange(char(&arr)[ROW][COL], char player) override;
	bool Kill(char(&arr)[ROW][COL]) override;
private:
	void Zone(char(&arr)[ROW][COL]) override;
};

