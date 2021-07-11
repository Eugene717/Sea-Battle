#pragma once
#include "Ship.h"

class Twin_Ship :public Ship
{
public:
	Twin_Ship();
	~Twin_Ship();
	void RandomlyArrange(char(&arr)[ROW][COL], char player) override;
	bool Kill(char(&arr)[ROW][COL]) override;
private:
	void Zone(char(&arr)[ROW][COL]) override;
};
