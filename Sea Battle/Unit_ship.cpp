#include "Unit_ship.h"
#include "Game.h"

struct ShipIMPL
{
	int m_x1, m_y1;
	char* m_stat1;
};

Unit_Ship::Unit_Ship() :Ship(1)
{
	m_pImpl = new ShipIMPL;
	m_pImpl->m_stat1 = nullptr;
}

Unit_Ship::~Unit_Ship()
{
	delete m_pImpl;
}

void Unit_Ship::SetPos(const int& x, const int& y, char(&arr)[ROW][COL], const char& player)
{
	if (arr[y][x] != EMPTY)
	{
		m_body->setPosition(*m_posGraphic);
		if (!*m_disposited)
			return;
	}
	else
	{
		*m_disposited = true;
		m_pImpl->m_x1 = x;
		m_pImpl->m_y1 = y;
		m_body->setPosition(50 + 30 * y + 15, 80 + 30 * x + 15);
		*m_posGraphic = m_body->getPosition();
	}

	std::vector<sf::Vector2f> zone = Zone(arr, true);
	for (int i = 0; i < zone.size(); i++)
	{
		arr[(int)zone[i].x][(int)zone[i].y] = MISS;
	}
	m_pImpl->m_stat1 = &arr[y][x];
	*m_pImpl->m_stat1 = player;
}

void Unit_Ship::RandomlyArrange(char(&arr)[ROW][COL], const char& player)
{
	Game* game = Game::GetInstance();

	*m_disposited = true;
	do
	{
		int x1 = game->m_gen() % 10;
		int y1 = game->m_gen() % 10;
		if (arr[y1][x1] == EMPTY)
		{
			m_pImpl->m_x1 = x1;
			m_pImpl->m_y1 = y1;
			m_pImpl->m_stat1 = &arr[y1][x1];
			*m_pImpl->m_stat1 = player;
			m_body->setPosition(50 + 30 * y1 + 15, 80 + 30 * x1 + 15);
			Zone(arr);		
			return;
		}
	} while (true);
}

void Unit_Ship::SetMPPos(char(&arr)[ROW][COL])
{
	m_pImpl->m_stat1 = &arr[m_pImpl->m_y1][m_pImpl->m_x1];
	*m_pImpl->m_stat1 = ENEMY_ALIVE;
}

void Unit_Ship::DrawZone(char(&arr)[ROW][COL])
{
	if (m_pImpl->m_stat1 != nullptr)
		Zone(arr, true);
}

void Unit_Ship::ClearZone(char(&arr)[ROW][COL])
{
	std::vector<sf::Vector2f> zone = Ship::Zone(arr, m_pImpl->m_x1, m_pImpl->m_y1, true);

	for (int i = 0; i < zone.size(); i++)
	{
		arr[(int)zone[i].x][(int)zone[i].y] = EMPTY;
	}

	*m_pImpl->m_stat1 = EMPTY;
	m_pImpl->m_stat1 = nullptr;
}

std::vector<sf::Vector2f> Unit_Ship::Zone(char(&arr)[ROW][COL], const bool& draw) const
{ 
	std::vector<sf::Vector2f> places = Ship::Zone(arr, m_pImpl->m_x1, m_pImpl->m_y1, draw);

	return places;
}

bool Unit_Ship::Kill(char(&arr)[ROW][COL], const int& board)
{
	if (*m_pImpl->m_stat1 == DEAD)
	{
		Game* game = Game::GetInstance();
		int min_board_x;
		if (board == 1)
			min_board_x = MIN_F_BOARD_X;
		else if (board == 2)
			min_board_x = MIN_S_BOARD_X;

		std::vector<sf::Vector2f> places = Zone(arr, true);

		for (size_t i = 0; i < places.size(); i++)
		{
			places[i].x = min_board_x + places[i].x * SQUARE_SIDE_SIZE + 15;
			places[i].y = MIN_Y + places[i].y * SQUARE_SIDE_SIZE + 15;
		}

		game->PlaySound(Sounds::sank);
		game->DrawShots(places, sf::Color(858585));
		Zone(arr);

		return true;
	}
	return false;
}

sf::Packet& operator<<(sf::Packet& packet, Unit_Ship* m)
{
	return packet << m->m_pImpl->m_x1 << m->m_pImpl->m_y1;
}

sf::Packet& operator>>(sf::Packet& packet, Unit_Ship* m)
{
	return packet >> m->m_pImpl->m_x1 >> m->m_pImpl->m_y1;
}
