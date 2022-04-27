#include "Triple_Ship.h"
#include "Game.h"

using namespace std;

Triple_Ship::Triple_Ship()
{
	m_x1 = new int;
	m_y1 = new int;
	m_x2 = new int;
	m_y2 = new int;
	m_x3 = new int;
	m_y3 = new int;
}

Triple_Ship::~Triple_Ship()
{
	delete m_x1;
	delete m_y1;
	delete m_x2;
	delete m_y2;
	delete m_x3;
	delete m_y3;
}

void Triple_Ship::SetPos(const int& x, const int& y, const bool& horiz)
{
	*m_x1 = x;
	*m_y1 = y;
	if (horiz)
	{
		*m_x2 = x + 1;
		*m_x3 = x + 2;
		*m_y2 = y;
		*m_y3 = y;
	}
	else
	{
		*m_x2 = x;
		*m_x3 = x;
		*m_y2 = y + 1;
		*m_y3 = y + 2;
	}
}

void Triple_Ship::RandomlyArrange(char(&arr)[ROW][COL], char player)
{
	Game* game = Game::GetInstance();

	int dir;
	bool isFree = false;
	do
	{
		*m_x1 = game->m_gen() % 10;
		*m_y1 = game->m_gen() % 10;
		//вторая палуба
		if (arr[*m_y1][*m_x1] != MISS && arr[*m_y1][*m_x1] != player)
		{
			dir = game->m_gen() % 4;
			switch (dir)
			{
			case 0:
				if (*m_y1 != 0)
				{
					*m_y2 = *m_y1 - 1;
					*m_x2 = *m_x1;
					swap(*m_y1, *m_y2);
					dir = 2;
					isFree = true;
				}
				break;
			case 1:
				if (*m_x1 != 9)
				{
					*m_y2 = *m_y1;
					*m_x2 = *m_x1 + 1;
					swap(*m_x1, *m_x2);
					dir = 3;
					isFree = true;
				}
				break;
			case 2:
				if (*m_y1 != 9)
				{
					*m_y2 = *m_y1 + 1;
					*m_x2 = *m_x1;
					isFree = true;
				}
				break;
			case 3:
				if (*m_x1 != 0)
				{
					*m_y2 = *m_y1;
					*m_x2 = *m_x1 - 1;
					isFree = true;
				}
				break;
			}
			if (isFree)
			{
				//третья палуба
				if (arr[*m_y2][*m_x2] != MISS && arr[*m_y1][*m_x1] != MISS)
				{
					if (dir == 2)
					{
						if (*m_y2 != 9)
						{
							*m_y3 = *m_y2 + 1;
							*m_x3 = *m_x2;
						}
						else  //m_y2 == 9
						{
							*m_y3 = *m_y2;
							*m_x3 = *m_x2;
							*m_y2 = *m_y1;
							*m_y1 = *m_y1 - 1;
						}
					}
					else  // dir == 3
					{
						if (*m_x2 != 0)
						{
							*m_x3 = *m_x2 - 1;
							*m_y3 = *m_y2;
						}
						else  //m_x2 == 0
						{
							*m_x3 = *m_x2;
							*m_y3 = *m_y2;
							*m_x2 = *m_x1;
							*m_x1 = *m_x1 + 1;
						}
					}
					if (arr[*m_y1][*m_x1] != MISS && arr[*m_y2][*m_x2] != MISS && arr[*m_y3][*m_x3] != MISS)
					{
						m_stat1 = &arr[*m_y1][*m_x1];
						m_stat2 = &arr[*m_y2][*m_x2];
						m_stat3 = &arr[*m_y3][*m_x3];
						*m_stat1 = player;
						*m_stat2 = player;
						*m_stat3 = player;
						Zone(arr);
						return;
					}
				}				
			}
		}
	} while (true);
}

std::vector<sf::Vector2f> Triple_Ship::Zone(char(&arr)[ROW][COL], const bool& draw) const
{
	std::vector<sf::Vector2f> places;
	auto places1 = Ship::Zone(arr, m_x1, m_y1, draw);
	auto places2 = Ship::Zone(arr, m_x2, m_y2, draw);
	auto places3 = Ship::Zone(arr, m_x3, m_y3, draw);

	places.insert(places.end(), std::make_move_iterator(places1.begin()), std::make_move_iterator(places1.end()));
	places.insert(places.end(), std::make_move_iterator(places2.begin()), std::make_move_iterator(places2.end()));
	places.insert(places.end(), std::make_move_iterator(places3.begin()), std::make_move_iterator(places3.end()));

	return places;
}

bool Triple_Ship::Kill(char(&arr)[ROW][COL], const int& board)
{
	if (*m_stat1 == DEAD && *m_stat2 == DEAD && *m_stat3 == DEAD)
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
