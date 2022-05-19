#pragma once
#ifndef SHIP_H
#define SHIP_H
#include "Constants.h"
#include <SFML/Graphics.hpp>

class Ship :public sf::Drawable
{
	bool* m_horiz;
public:
	Ship(const int& decksNumber);
	virtual ~Ship() = 0;
	virtual void SetPos(const int& x, const int& y, char(&arr)[ROW][COL], const char& player) = 0;
	virtual void RandomlyArrange(char(&arr)[ROW][COL], const char& player) = 0;
	virtual bool Kill(char(&arr)[ROW][COL], const int& board) = 0; 
	void Rotate();
	sf::FloatRect getGlobalBounds() const;
	void setPosition(const float& x, const float& y); 
	void replace();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool Horiz();
	void Desposited();
	bool Disposition();
	void DrawZone(char(&arr)[ROW][COL]);
	void ClearZone(char(&arr)[ROW][COL]);
	void EndArrange();
protected:
	int* m_x1, * m_y1, * m_x2, * m_y2, * m_x3, * m_y3, * m_x4, * m_y4;
	char* m_stat1, * m_stat2, * m_stat3, * m_stat4;
	sf::Vector2f* m_posGraphic;
	sf::RectangleShape* m_body;
	bool* m_disposited;
	std::vector<sf::Vector2f> Zone(char(&arr)[ROW][COL], const int* x, const int* y, const int& draw = false) const;
};

inline Ship::~Ship() { }

#endif // !SHIP_H