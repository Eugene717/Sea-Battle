#include "Unit_ship.h"
#include "Game.h"

using namespace std;

Unit_Ship::Unit_Ship() :Ship(1)
{
	m_x1 = new int;	m_y1 = new int;
}

Unit_Ship::~Unit_Ship()
{
	delete m_x1;
	delete m_y1;
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
		*m_x1 = x;
		*m_y1 = y;
		m_body->setPosition(50 + 30 * *m_y1 + 15, 80 + 30 * *m_x1 + 15);
		*m_posGraphic = m_body->getPosition();
	}

	std::vector<sf::Vector2f> zone = Zone(arr, true);
	for (int i = 0; i < zone.size(); i++)
	{
		arr[(int)zone[i].x][(int)zone[i].y] = MISS;
	}
	m_stat1 = &arr[*m_y1][*m_x1];
	*m_stat1 = player;
}

void Unit_Ship::RandomlyArrange(char(&arr)[ROW][COL], const char& player)
{
	Game* game = Game::GetInstance();

	*m_disposited = true;
	do
	{
		*m_y1 = game->m_gen() % 10;
	    *m_x1 = game->m_gen() % 10;
		if (arr[*m_y1][*m_x1] == EMPTY)
		{
			m_stat1 = &arr[*m_y1][*m_x1];
			*m_stat1 = player;
			m_body->setPosition(50 + 30 * *m_y1 + 15, 80 + 30 * *m_x1 + 15);
			Zone(arr);		
			return;
		}
	} while (true);
}

std::vector<sf::Vector2f> Unit_Ship::Zone(char(&arr)[ROW][COL], const bool& draw) const
{ 
	std::vector<sf::Vector2f> places = Ship::Zone(arr, m_x1, m_y1, draw);

	return places;
}

bool Unit_Ship::Kill(char(&arr)[ROW][COL], const int& board)
{
	if (*m_stat1 == DEAD)
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
