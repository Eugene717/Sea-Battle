#include "Quadraple_Ship.h"
#include "Game.h"

struct ShipIMPL
{
	int m_x1, m_y1;
	int m_x2, m_y2;
	int m_x3, m_y3;
	int m_x4, m_y4;
	char* m_stat1, * m_stat2, * m_stat3, * m_stat4;
};

Quadraple_Ship::Quadraple_Ship() :Ship(4)
{
	m_pImpl = new ShipIMPL;
	m_pImpl->m_stat1 = nullptr;
	m_pImpl->m_stat2 = nullptr;
	m_pImpl->m_stat3 = nullptr;
	m_pImpl->m_stat4 = nullptr;
}

Quadraple_Ship::~Quadraple_Ship()
{
	delete m_pImpl;
}

void Quadraple_Ship::SetPos(const int& x, const int& y, char(&arr)[ROW][COL], const char& player)
{	
	int y2, x2, y3, x3, y4, x4;
	if (Horiz())
	{
		x2 = x; y2 = y + 1;
		x3 = x; y3 = y2 + 1;
		x4 = x; y4 = y3 + 1;
	}
	else
	{
		x2 = x + 1; y2 = y;
		x3 = x2 + 1; y3 = y;
		x4 = x3 + 1; y4 = y;
	}
	if (arr[y][x] != EMPTY || arr[y2][x2] != EMPTY || arr[y3][x3] != EMPTY || arr[y4][x4] != EMPTY)
	{
		m_body->setPosition(*m_posGraphic);

		if (!*m_disposited)
		{
			if (!Horiz())
				Rotate();
			return;
		}

		if (m_pImpl->m_y1 == m_pImpl->m_y2)  //vert
		{
			if (Horiz())
				Rotate();
		}
		else
			if (!Horiz())
				Rotate();

	}
	else
	{
		*m_disposited = true;

		m_pImpl->m_x1 = x;
		m_pImpl->m_y1 = y;
		m_pImpl->m_x2 = x2;
		m_pImpl->m_x3 = x3;
		m_pImpl->m_x4 = x4;
		m_pImpl->m_y2 = y2;
		m_pImpl->m_y3 = y3;
		m_pImpl->m_y4 = y4;
		m_body->setPosition(50 + 30 * (float(y + y4) / 2) + 15, 80 + 30 * (float(x + x4) / 2) + 15);
		*m_posGraphic = m_body->getPosition();
	}

	std::vector<sf::Vector2f> zone = Zone(arr, true);
	for (int i = 0; i < zone.size(); i++)
	{
		arr[(int)zone[i].x][(int)zone[i].y] = MISS;
	}
	m_pImpl->m_stat1 = &arr[m_pImpl->m_y1][m_pImpl->m_x1];
	*m_pImpl->m_stat1 = player;
	m_pImpl->m_stat2 = &arr[m_pImpl->m_y2][m_pImpl->m_x2];
	*m_pImpl->m_stat2 = player;
	m_pImpl->m_stat3 = &arr[m_pImpl->m_y3][m_pImpl->m_x3];
	*m_pImpl->m_stat3 = player;
	m_pImpl->m_stat4 = &arr[m_pImpl->m_y4][m_pImpl->m_x4];
	*m_pImpl->m_stat4 = player;
}

void Quadraple_Ship::RandomlyArrange(char(&arr)[ROW][COL], const char& player)
{
	Game* game = Game::GetInstance();

	if (!Horiz())
		Rotate();
	*m_disposited = true;
	int dir;
	bool isFree = false;
	do
	{
		m_pImpl->m_x1 = game->m_gen() % 10;
		m_pImpl->m_y1 = game->m_gen() % 10;
		//������ ������
		dir = game->m_gen() % 4;
		switch (dir)
		{
		case 0:
			if (m_pImpl->m_y1 != 0)
			{
				m_pImpl->m_y2 = m_pImpl->m_y1 - 1;
				m_pImpl->m_x2 = m_pImpl->m_x1;
				std::swap(m_pImpl->m_y1, m_pImpl->m_y2);
				dir = 2;
				isFree = true;
			}
			break;
		case 1:
			if (m_pImpl->m_x1 != 9)
			{
				m_pImpl->m_y2 = m_pImpl->m_y1;
				m_pImpl->m_x2 = m_pImpl->m_x1 + 1;
				std::swap(m_pImpl->m_x1, m_pImpl->m_x2);
				dir = 3;
				isFree = true;
			}
			break;
		case 2:
			if (m_pImpl->m_y1 != 9)
			{
				m_pImpl->m_y2 = m_pImpl->m_y1 + 1;
				m_pImpl->m_x2 = m_pImpl->m_x1;
				isFree = true;
			}
			break;
		case 3:
			if (m_pImpl->m_x1 != 0)
			{
				m_pImpl->m_y2 = m_pImpl->m_y1;
				m_pImpl->m_x2 = m_pImpl->m_x1 - 1;
				isFree = true;
			}
			break;
		}
		//������ ������		
		if (isFree)
		{
			if (dir == 2)
			{
				if (m_pImpl->m_y2 != 9)
				{
					m_pImpl->m_y3 = m_pImpl->m_y2 + 1;
					m_pImpl->m_x3 = m_pImpl->m_x2;
				}
				else  //*m_y2 == 9
				{
					m_pImpl->m_y3 = m_pImpl->m_y2;
					m_pImpl->m_x3 = m_pImpl->m_x2;
					m_pImpl->m_y2 = m_pImpl->m_y1;
					m_pImpl->m_y1 = m_pImpl->m_y1 - 1;
				}
			}
			else  // dir == 3
			{
				if (m_pImpl->m_x2 != 0)
				{
					m_pImpl->m_x3 = m_pImpl->m_x2 - 1;
					m_pImpl->m_y3 = m_pImpl->m_y2;
				}
				else  //*m_x2 == 0
				{
					m_pImpl->m_x3 = m_pImpl->m_x2;
					m_pImpl->m_y3 = m_pImpl->m_y2;
					m_pImpl->m_x2 = m_pImpl->m_x1;
					m_pImpl->m_x1 = m_pImpl->m_x1 + 1;
				}
			}
			//��������� ������
			if (dir == 2)
			{
				if (m_pImpl->m_y3 != 9)
				{
					m_pImpl->m_y4 = m_pImpl->m_y3 + 1;
					m_pImpl->m_x4 = m_pImpl->m_x3;
				}
				else  //m_y3 == 9
				{
					m_pImpl->m_y4 = m_pImpl->m_y3;
					m_pImpl->m_x4 = m_pImpl->m_x3;
					m_pImpl->m_y3 = m_pImpl->m_y2;
					m_pImpl->m_y2 = m_pImpl->m_y1;
					m_pImpl->m_y1 = m_pImpl->m_y1 - 1;
				}
			}
			else  // dir == 3
			{
				if (m_pImpl->m_x3 != 0)
				{
					m_pImpl->m_x4 = m_pImpl->m_x3 - 1;
					m_pImpl->m_y4 = m_pImpl->m_y3;
				}
				else  //m_x2 == 0
				{
					m_pImpl->m_x4 = m_pImpl->m_x3;
					m_pImpl->m_y4 = m_pImpl->m_y3;
					m_pImpl->m_x3 = m_pImpl->m_x2;
					m_pImpl->m_x2 = m_pImpl->m_x1;
					m_pImpl->m_x1 = m_pImpl->m_x1 + 1;
				}
			}
			m_pImpl->m_stat1 = &arr[m_pImpl->m_y1][m_pImpl->m_x1];
			m_pImpl->m_stat2 = &arr[m_pImpl->m_y2][m_pImpl->m_x2];
			m_pImpl->m_stat3 = &arr[m_pImpl->m_y3][m_pImpl->m_x3];
			m_pImpl->m_stat4 = &arr[m_pImpl->m_y4][m_pImpl->m_x4];
			*m_pImpl->m_stat1 = player;
			*m_pImpl->m_stat2 = player;
			*m_pImpl->m_stat3 = player;
			*m_pImpl->m_stat4 = player;

			m_posGraphic->x = 50 + 30 * (float(m_pImpl->m_y1 + m_pImpl->m_y4) / 2) + 15; m_posGraphic->y = 80 + 30 * (float(m_pImpl->m_x1 + m_pImpl->m_x4) / 2) + 15;
			m_body->setPosition(*m_posGraphic);
			if (m_pImpl->m_y1 == m_pImpl->m_y2)
				if (Horiz())
					Rotate();
			Zone(arr);
			return;
		}
	} while (true);
}

void Quadraple_Ship::SetMPPos(char(&arr)[ROW][COL])
{
	m_pImpl->m_stat1 = &arr[m_pImpl->m_y1][m_pImpl->m_x1];
	m_pImpl->m_stat2 = &arr[m_pImpl->m_y2][m_pImpl->m_x2];
	m_pImpl->m_stat3 = &arr[m_pImpl->m_y3][m_pImpl->m_x3];
	m_pImpl->m_stat4 = &arr[m_pImpl->m_y4][m_pImpl->m_x4];
	*m_pImpl->m_stat1 = ENEMY_ALIVE;
	*m_pImpl->m_stat2 = ENEMY_ALIVE;
	*m_pImpl->m_stat3 = ENEMY_ALIVE;
	*m_pImpl->m_stat4 = ENEMY_ALIVE;
}

void Quadraple_Ship::DrawZone(char(&arr)[ROW][COL])
{
	if (m_pImpl->m_stat1 != nullptr)
		Zone(arr, false);
	if (m_pImpl->m_stat2 != nullptr)
		Zone(arr, false);
	if (m_pImpl->m_stat3 != nullptr)
		Zone(arr, false);
	if (m_pImpl->m_stat4 != nullptr)
		Zone(arr, false);
}

void Quadraple_Ship::ClearZone(char(&arr)[ROW][COL])
{
	if (*m_disposited)
	{
		std::vector<sf::Vector2f> zone = Zone(arr, true);

		for (int i = 0; i < zone.size(); i++)
		{
			arr[(int)zone[i].x][(int)zone[i].y] = EMPTY;
		}

		*m_pImpl->m_stat1 = EMPTY;
		*m_pImpl->m_stat2 = EMPTY;
		*m_pImpl->m_stat3 = EMPTY;
		*m_pImpl->m_stat4 = EMPTY;
		m_pImpl->m_stat1 = nullptr;
		m_pImpl->m_stat2 = nullptr;
		m_pImpl->m_stat3 = nullptr;
		m_pImpl->m_stat4 = nullptr;
	}
}

std::vector<sf::Vector2f> Quadraple_Ship::Zone(char(&arr)[ROW][COL], const bool& draw) const
{
	std::vector<sf::Vector2f> places;
	auto places1 = Ship::Zone(arr, m_pImpl->m_x1, m_pImpl->m_y1, draw);
	auto places2 = Ship::Zone(arr, m_pImpl->m_x2, m_pImpl->m_y2, draw);
	auto places3 = Ship::Zone(arr, m_pImpl->m_x3, m_pImpl->m_y3, draw);
	auto places4 = Ship::Zone(arr, m_pImpl->m_x4, m_pImpl->m_y4, draw);

	places.insert(places.end(), std::make_move_iterator(places1.begin()), std::make_move_iterator(places1.end()));
	places.insert(places.end(), std::make_move_iterator(places2.begin()), std::make_move_iterator(places2.end()));
	places.insert(places.end(), std::make_move_iterator(places3.begin()), std::make_move_iterator(places3.end()));
	places.insert(places.end(), std::make_move_iterator(places4.begin()), std::make_move_iterator(places4.end()));

	return places;
}

bool Quadraple_Ship::Kill(char(&arr)[ROW][COL], const int& board)
{
	if (*m_pImpl->m_stat1 == DEAD && *m_pImpl->m_stat2 == DEAD && *m_pImpl->m_stat3 == DEAD && *m_pImpl->m_stat4 == DEAD)
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

sf::Packet& operator<<(sf::Packet& packet, Quadraple_Ship* m)
{
	return packet << m->m_pImpl->m_x1 << m->m_pImpl->m_y1 << m->m_pImpl->m_x2 << m->m_pImpl->m_y2 << m->m_pImpl->m_x3 << m->m_pImpl->m_y3 << m->m_pImpl->m_x4 << m->m_pImpl->m_y4;
}

sf::Packet& operator>>(sf::Packet& packet, Quadraple_Ship* m)
{
	return packet >> m->m_pImpl->m_x1 >> m->m_pImpl->m_y1 >> m->m_pImpl->m_x2 >> m->m_pImpl->m_y2 >> m->m_pImpl->m_x3 >> m->m_pImpl->m_y3 >> m->m_pImpl->m_x4 >> m->m_pImpl->m_y4;
}
