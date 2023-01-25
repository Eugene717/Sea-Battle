#pragma once
#include <utility>
#include <vector>
#include "Constants.h"

class AIState
{
public:
	virtual AIState* ShootDeck(char(&enemy)[ROW][COL]) = 0;
	bool SankShip(const char(&enemy)[ROW][COL]);
};

class FirstDeckState : public AIState
{
public:
	AIState* ShootDeck(char(&enemy)[ROW][COL]) override;
};

class SecondDeckState : public AIState
{
public:
	AIState* ShootDeck(char(&enemy)[ROW][COL]) override;
};

class ThirdDeckState : public AIState
{
public:
	AIState* ShootDeck(char(&enemy)[ROW][COL]) override;
};

class FourDeckState : public AIState
{
public:
	AIState* ShootDeck(char(&enemy)[ROW][COL]) override;
};

