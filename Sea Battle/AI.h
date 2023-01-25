#pragma once
#include "Player.h"

class AIState;
class FirstDeckState;
class SecondDeckState;
class ThirdDeckState;
class FourDeckState;

class AI :public Player
{
	AIState* m_state;
public:
	static FirstDeckState m_first_state;
	static SecondDeckState m_second_state;
	static ThirdDeckState m_third_state;
	static FourDeckState m_four_state;

	AI(const char& player = ENEMY_ALIVE);
	~AI();
	bool Shoot(char(&enemy)[ROW][COL]) override;
};

