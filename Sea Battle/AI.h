#pragma once
#include "Player.h"
#include "Point.h"

class AI :public Player
{
	Point* m_one;
	Point* m_two;
	Point* m_three;
	Point* m_four;
	bool m_SecondDeck;
	bool m_ThirdDeck;
	bool m_FourthDeck;

	bool Shoot1Deck(char(&enemy)[ROW][COL]);
	bool Shoot2Deck(char(&enemy)[ROW][COL]);
	bool Shoot3Deck(char(&enemy)[ROW][COL]);
	bool Shoot4Deck(char(&enemy)[ROW][COL]);
public:
	AI(const char& player = ENEMY_ALIVE);
	~AI();
	void SankShip(const char(&enemy)[ROW][COL]);
	bool Shoot(char(&enemy)[ROW][COL]) override;
};

