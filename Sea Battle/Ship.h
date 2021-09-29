#pragma once
#ifndef SHIP_H
#define SHIP_H
#include "Constants.h"

class Ship
{
public:
	Ship() { };
	virtual ~Ship() = 0;
	virtual void RandomlyArrange(char(&arr)[ROW][COL], char player) = 0;
	virtual bool Kill(char(&arr)[ROW][COL]) = 0;
protected:
	int* m_x1, * m_y1, * m_x2, * m_y2, * m_x3, * m_y3, * m_x4, * m_y4;
	char* m_stat1, * m_stat2, * m_stat3, * m_stat4;
	void Zone(char(&arr)[ROW][COL], const int* x, const int* y);
};

inline Ship::~Ship() { }

#endif // !SHIP_H