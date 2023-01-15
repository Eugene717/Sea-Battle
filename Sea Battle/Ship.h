#pragma once
#ifndef SHIP_H
#define SHIP_H
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

struct ShipIMPL;

class Ship :public sf::Drawable
{
	bool* m_horiz;
public:
	Ship(const int& decksNumber);
	virtual ~Ship() = 0;
	virtual void SetPos(const int& x, const int& y, char(&arr)[ROW][COL], const char& player) = 0;
	virtual void RandomlyArrange(char(&arr)[ROW][COL], const char& player) = 0;
	virtual void SetMPPos(char(&arr)[ROW][COL]) = 0;
	virtual bool Kill(char(&arr)[ROW][COL], const int& board) = 0; 
	void Rotate();
	sf::FloatRect getGlobalBounds() const;
	void setPosition(const float& x, const float& y); 
	void replace();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool Horiz();
	void Desposited();
	bool Disposition();
	virtual void DrawZone(char(&arr)[ROW][COL]) = 0;
	virtual	void ClearZone(char(&arr)[ROW][COL]) = 0;
	void EndArrange();	
protected:
	ShipIMPL* m_pImpl;
	sf::Vector2f* m_posGraphic;
	sf::RectangleShape* m_body;
	bool* m_disposited;
	std::vector<sf::Vector2f> Zone(char(&arr)[ROW][COL], const int x, const int y, const bool& draw = false) const;
};

inline Ship::~Ship() { }

#endif // !SHIP_H