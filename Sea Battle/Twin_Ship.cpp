#include "Twin_Ship.h"
#include "Game.h"

using namespace std;

Twin_Ship::Twin_Ship() :Ship(2)
{
	m_x1 = new int;	m_y1 = new int;
	m_x2 = new int;	m_y2 = new int;
}

Twin_Ship::~Twin_Ship()
{
	delete m_x1;
	delete m_y1;
	delete m_x2;
	delete m_y2;
}

void Twin_Ship::SetPos(const int& x, const int& y, char(&arr)[ROW][COL], const char& player)
{	
	int y2, x2;
	if (Horiz())
	{ x2 = x; y2 = y + 1; }
	else
	{ x2 = x + 1; y2 = y; }

	if (arr[y][x] != EMPTY || arr[y2][x2] != EMPTY)
	{
		m_body->setPosition(*m_posGraphic);
		if (!*m_disposited)
			return;
		if (*m_x1 == *m_x2)
		{
			if (!Horiz())
				Rotate();
		}
		else
			if (Horiz())
				Rotate();			
	}
	else
	{
		*m_disposited = true;
		*m_x1 = x;
		*m_y1 = y;
		*m_x2 = x2;
		*m_y2 = y2;
		m_body->setPosition(50 + 30 * (float(*m_y1 + *m_y2) / 2) + 15, 80 + 30 * (float(*m_x1 + *m_x2) / 2) + 15);
		*m_posGraphic = m_body->getPosition();
	}

	std::vector<sf::Vector2f> zone = Zone(arr, true);
	for (int i = 0; i < zone.size(); i++)
	{
		arr[(int)zone[i].x][(int)zone[i].y] = MISS;
	}
	m_stat1 = &arr[*m_y1][*m_x1];
	*m_stat1 = player;
	m_stat2 = &arr[*m_y2][*m_x2];
	*m_stat2 = player;
}

void Twin_Ship::RandomlyArrange(char(&arr)[ROW][COL], const char& player)
{
	Game* game = Game::GetInstance();

	if (!Horiz())
		Rotate();
	*m_disposited = true;
	bool isFree = false;
	do
	{
		*m_x1 = game->m_gen() % 10;
		*m_y1 = game->m_gen() % 10;
		if (arr[*m_y1][*m_x1] == EMPTY)
		{
			switch (int dir(game->m_gen() % 4); dir)
			{
			case 0:
				if (*m_y1 != 0)
				{
					*m_y2 = *m_y1 - 1;
					*m_x2 = *m_x1;
					isFree = true;
				}
				break;
			case 1:
				if (*m_x1 != 9)
				{
					*m_y2 = *m_y1;
					*m_x2 = *m_x1 + 1;
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
				if (arr[*m_y1][*m_x1] == EMPTY && arr[*m_y2][*m_x2] == EMPTY)
				{
					m_stat1 = &arr[*m_y1][*m_x1];
					m_stat2 = &arr[*m_y2][*m_x2];
					*m_stat1 = player;
					*m_stat2 = player;
					m_body->setPosition(50 + 30 * (float(*m_y1 + *m_y2) / 2) + 15, 80 + 30 * (float(*m_x1 + *m_x2) / 2) + 15);
					if (*m_y1 == *m_y2)
						if (Horiz())
							Rotate();
					Zone(arr);
					return;
				}
			}
		}
	} while (true);
}

void Twin_Ship::SetMPPos(char(&arr)[ROW][COL])
{
	m_stat1 = &arr[*m_y1][*m_x1];
	m_stat2 = &arr[*m_y2][*m_x2];
	*m_stat1 = ENEMY_ALIVE;
	*m_stat2 = ENEMY_ALIVE;
}

std::vector<sf::Vector2f> Twin_Ship::Zone(char(&arr)[ROW][COL], const bool& draw) const
{
	std::vector<sf::Vector2f> places;
	auto places1 = Ship::Zone(arr, m_x1, m_y1, draw);
	auto places2 = Ship::Zone(arr, m_x2, m_y2, draw);

	places.insert(places.end(), std::make_move_iterator(places1.begin()), std::make_move_iterator(places1.end()));
	places.insert(places.end(), std::make_move_iterator(places2.begin()), std::make_move_iterator(places2.end()));
	
	return places;
}

bool Twin_Ship::Kill(char(&arr)[ROW][COL], const int& board)
{
	if (*m_stat1 == DEAD && *m_stat2 == DEAD)
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

sf::Packet& operator<<(sf::Packet& packet, Twin_Ship* m)
{
	return packet << *m->m_x1 << *m->m_y1  << *m->m_x2 << *m->m_y2;
}

sf::Packet& operator>>(sf::Packet& packet, Twin_Ship* m)
{
	return packet >> *m->m_x1 >> *m->m_y1 >> *m->m_x2 >> *m->m_y2;
}
