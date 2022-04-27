#include "Player.h"
#include "Ships.h"

Player::Player(const char& player, const int& board_number) :m_player(player), m_board_number(board_number)
{
	m_Ships.push_back(std::make_unique<Quadraple_Ship>());
	m_Ships.push_back(std::make_unique<Triple_Ship>());
	m_Ships.push_back(std::make_unique<Triple_Ship>());
	m_Ships.push_back(std::make_unique<Twin_Ship>());
	m_Ships.push_back(std::make_unique<Twin_Ship>());
	m_Ships.push_back(std::make_unique<Twin_Ship>());
	m_Ships.push_back(std::make_unique<Unit_Ship>());
	m_Ships.push_back(std::make_unique<Unit_Ship>());
	m_Ships.push_back(std::make_unique<Unit_Ship>());
	m_Ships.push_back(std::make_unique<Unit_Ship>());
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
}

void Player::SetShipPos(const int& i, const int& x, const int& y, const bool& horiz)
{
	m_Ships[i]->SetPos(x, y, horiz);
}

void Player::CleardBoard()
{
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
		if ((*m_Ships[i]).Kill(m_Board, m_board_number))
		{
			m_Ships.erase(remove(m_Ships.begin(), m_Ships.end(), m_Ships[i]), m_Ships.end());
			return;
		}
	}
}
