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

bool Player::SearchDead()
{
	for (size_t i = 0; i < m_Ships.size(); i++)
	{
		if ((*m_Ships[i]).Kill(m_Board, m_board_number))
		{
			m_Ships.erase(remove(m_Ships.begin(), m_Ships.end(), m_Ships[i]), m_Ships.end());
			return true;
		}
	}
	return false;
}

void Player::SendShips(sf::Packet& packet)
{
	packet << static_cast<Quadraple_Ship*>(&*m_Ships[0]);
	packet << static_cast<Triple_Ship*>(&*m_Ships[1]);
	packet << static_cast<Triple_Ship*>(&*m_Ships[2]);
	packet << static_cast<Twin_Ship*>(&*m_Ships[3]);
	packet << static_cast<Twin_Ship*>(&*m_Ships[4]);
	packet << static_cast<Twin_Ship*>(&*m_Ships[5]);
	packet << static_cast<Unit_Ship*>(&*m_Ships[6]);
	packet << static_cast<Unit_Ship*>(&*m_Ships[7]);
	packet << static_cast<Unit_Ship*>(&*m_Ships[8]);
	packet << static_cast<Unit_Ship*>(&*m_Ships[9]);
}

void Player::GetShips(sf::Packet& packet)
{
	packet >> static_cast<Quadraple_Ship*>(&*m_Ships[0]);
	packet >> static_cast<Triple_Ship*>(&*m_Ships[1]);
	packet >> static_cast<Triple_Ship*>(&*m_Ships[2]);
	packet >> static_cast<Twin_Ship*>(&*m_Ships[3]);
	packet >> static_cast<Twin_Ship*>(&*m_Ships[4]);
	packet >> static_cast<Twin_Ship*>(&*m_Ships[5]);
	packet >> static_cast<Unit_Ship*>(&*m_Ships[6]);
	packet >> static_cast<Unit_Ship*>(&*m_Ships[7]);
	packet >> static_cast<Unit_Ship*>(&*m_Ships[8]);
	packet >> static_cast<Unit_Ship*>(&*m_Ships[9]);

	for (int i = 0; i < 10; i++)
		m_Ships[i]->SetMPPos(m_Board);
}
