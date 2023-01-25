#include "AI.h"
#include "Game.h"
#include "AIState.h"

AI::AI(const char& player) :Player(ENEMY_ALIVE, 2)
{
	m_state = new FirstDeckState();
}

AI::~AI()
{}

bool AI::Shoot(char(&enemy)[ROW][COL])
{
	AIState* state = m_state->ShootDeck(enemy);

	if (state != nullptr)
	{
		if (state->SankShip(enemy))
			m_state = new FirstDeckState();
		else
			m_state = state;
		return true;
	}
	return false;
}
