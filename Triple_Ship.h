#pragma once
#include "Ship.h"

class Triple_Ship :public Ship
{
public:
	Triple_Ship();
	~Triple_Ship();
	void RandomlyArrange(char(&arr)[ROW][COL], char player) override;
	bool Kill(char(&arr)[ROW][COL]) override;
};
