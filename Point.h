#pragma once
#ifndef POINT_H
#define POINT_H

#include <iostream>

enum Direction {
	UP = -1, DOWN = 1, RIGHT = 1, LEFT = -1
};

class Point
{
	short m_x, m_y;
public:
	Point();
	Point(const short& x, const short& y);
	Point Move(const short& x, const short& y);
	Point& SetValues(const short& x, const short& y);
	Point MoveCopy(const short& x, const short& y) const;
	Point CopyNMove(const short& x, const short& y);
	short GetX() const;
	short GetY() const;
	friend std::istream& operator>>(std::istream& is, Point& point);
};

#endif // !POINT_H