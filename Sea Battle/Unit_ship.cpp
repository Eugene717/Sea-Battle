#include "Unit_ship.h"
#include "Game.h"

using namespace std;

Unit_Ship::Unit_Ship()
{
	m_x1 = new int;
	m_y1 = new int;
}

Unit_Ship::~Unit_Ship()
{
	delete m_x1;
	delete m_y1;
}

void Unit_Ship::SetPos(const int& x, const int& y, const bool& horiz)
{
	*m_x1 = x;
	*m_y1 = y;
}

void Unit_Ship::RandomlyArrange(char(&arr)[ROW][COL], char player)
{
	Game* game = Game::GetInstance();

	do
	{
		*m_y1 = game->m_gen() % 10;
	    *m_x1 = game->m_gen() % 10;
		if (arr[*m_y1][*m_x1] != MISS && arr[*m_y1][*m_x1] != player)
		{
			m_stat1 = &arr[*m_y1][*m_x1];
			*m_stat1 = player;
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

		game->DrawShots(places, sf::Color(858585));
		Zone(arr);

		return true;
	}
	return false;
}
