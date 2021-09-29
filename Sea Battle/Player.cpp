#include "Player.h"

Player::Player(const char& player) :m_player(player)
{
	m_Ships.emplace_back(std::make_unique<Quadraple_Ship>());
	m_Ships.emplace_back(std::make_unique<Triple_Ship>());
	m_Ships.emplace_back(std::make_unique<Triple_Ship>());
	m_Ships.emplace_back(std::make_unique<Twin_Ship>());
	m_Ships.emplace_back(std::make_unique<Twin_Ship>());
	m_Ships.emplace_back(std::make_unique<Twin_Ship>());
	m_Ships.emplace_back(std::make_unique<Unit_Ship>());
	m_Ships.emplace_back(std::make_unique<Unit_Ship>());
	m_Ships.emplace_back(std::make_unique<Unit_Ship>());
	m_Ships.emplace_back(std::make_unique<Unit_Ship>());
}

Player::~Player()
{
	m_Ships.clear();
}

bool Player::Loss() const
{
	return m_Ships.empty();
}

void Player::RandomShipsArrangement()
{
	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
			m_Board[y][x] = EMPTY;
	}

	for (size_t i = 0; i < 10; i++)
	{
		(*m_Ships[i]).RandomlyArrange(m_Board, m_player);
	}

	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			if (m_Board[y][x] == MISS)
				m_Board[y][x] = EMPTY;
		}
	}
}

void Player::SearchDead()
{
	for (size_t i = 0; i < m_Ships.size(); i++)
	{
		if ((*m_Ships[i]).Kill(m_Board))
		{
			m_Ships.erase(remove(m_Ships.begin(), m_Ships.end(), m_Ships[i]), m_Ships.end());
			return;
		}
	}
}
