#pragma once
#include "Ship.h"

class Quadraple_Ship :public Ship
{
public:
	Quadraple_Ship();
	~Quadraple_Ship();
	void RandomlyArrange(char(&arr)[ROW][COL], char player) override;
	bool Kill(char(&arr)[ROW][COL]) override;
private:
	void Zone(char(&arr)[ROW][COL]) override;
};

