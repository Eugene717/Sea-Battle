#include "AIState.h"
#include "Game.h"

using Point = std::pair<int, int>;
static std::vector<Point> m_points;

AIState* FirstDeckState::ShootDeck(char(&enemy)[ROW][COL])
{
	Game* game = Game::GetInstance();
	Point one;

	do
	{
		one.first = game->m_gen() % 10; one.second = game->m_gen() % 10;
		if (enemy[one.second][one.first] != MISS && enemy[one.second][one.first] != DEAD)
		{
			sf::Vector2f middleCell(MIN_F_BOARD_X + one.second * SQUARE_SIDE_SIZE + 15, MIN_Y + one.first * SQUARE_SIDE_SIZE + 15);

			if (enemy[one.second][one.first] == ALIVE)
			{
				game->PlaySound(Sounds::enemy);
				game->DrawShot(middleCell, sf::Color::Red);
				enemy[one.second][one.first] = DEAD;
				m_points.push_back(one);
				return new SecondDeckState();
			}
			else
			{
				game->PlaySound(Sounds::miss);
				game->DrawShot(middleCell, sf::Color::Color(858585));
				enemy[one.second][one.first] = MISS;
				return nullptr;
			}
		}
	} while (true);
}

AIState* SecondDeckState::ShootDeck(char(&enemy)[ROW][COL])
{
	Game* game = Game::GetInstance();
	bool isFree = false;
	Point two;

	do
	{
		switch (int n(game->m_gen() % 4); n)
		{
		case 0:
			if (m_points[0].second != 0)
			{
				two.first = m_points[0].first; two.second = m_points[0].second - 1;
				isFree = true;
			}
			break;
		case 1:
			if (m_points[0].first != 9)
			{
				two.first = m_points[0].first + 1; two.second = m_points[0].second;
				isFree = true;
			}
			break;
		case 2:
			if (m_points[0].second != 9)
			{
				two.first = m_points[0].first; two.second = m_points[0].second + 1;
				isFree = true;
			}
			break;
		case 3:
			if (m_points[0].first != 0)
			{
				two.first = m_points[0].first - 1; two.second = m_points[0].second;
				isFree = true;
			}
			break;
		}
		if (isFree)
		{
			if (enemy[two.second][two.first] == MISS)
				isFree = false;
			else
			{
				sf::Vector2f middleCell(MIN_F_BOARD_X + two.second * SQUARE_SIDE_SIZE + 15, MIN_Y + two.first * SQUARE_SIDE_SIZE + 15);

				if (enemy[two.second][two.first] == ALIVE)
				{
					game->PlaySound(Sounds::enemy);
					game->DrawShot(middleCell, sf::Color::Red);
					enemy[two.second][two.first] = DEAD;
					m_points.push_back(two);

					if (m_points[0].first < two.first || m_points[0].second > two.second)
						std::swap(m_points[0], m_points[1]);

					return new ThirdDeckState();
				}
				else
				{
					game->PlaySound(Sounds::miss);
					game->DrawShot(middleCell, sf::Color::Color(858585));
					enemy[two.second][two.first] = MISS;

					return nullptr;
				}
			}
		}
	} while (true);
}

AIState* ThirdDeckState::ShootDeck(char(&enemy)[ROW][COL])
{
	Game* game = Game::GetInstance();
	Point three;
	int n(game->m_gen() % 2);

	do
	{
		if (m_points[0].first == m_points[1].first)  //вертикальный 
		{
			if (n == 0) //выстрел вверх
			{
				if (m_points[0].second != 0)
				{
					three.first = m_points[0].first; three.second = m_points[0].second - 1;
					if (enemy[three.second][three.first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + three.second * SQUARE_SIDE_SIZE + 15, MIN_Y + three.first * SQUARE_SIDE_SIZE + 15);

						if (enemy[three.second][three.first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[three.second][three.first] = DEAD;
							m_points.push_back(three);

							std::swap(m_points[0], m_points[1]);    //one всегда должен быть выше
							std::swap(m_points[0], m_points[2]);

							return new FourDeckState();
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[three.second][three.first] = MISS;

							return nullptr;
						}
					}
				}
				n = 1;
			}
			else   //выстрел вниз
			{
				if (m_points[1].second != 9)
				{
					three.first = m_points[1].first; three.second = m_points[1].second + 1;
					if (enemy[three.second][three.first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + three.second * SQUARE_SIDE_SIZE + 15, MIN_Y + three.first * SQUARE_SIDE_SIZE + 15);

						if (enemy[three.second][three.first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[three.second][three.first] = DEAD;
							m_points.push_back(three);

							return new FourDeckState();
						}
						else  //промах
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[three.second][three.first] = MISS;

							return nullptr;;
						}
					}
				}
				n = 0;
			}
		}
		if (m_points[0].second == m_points[1].second)  //горизонтальный 
		{
			if (n == 0)   //выстрел влево
			{
				if (m_points[1].first != 0)
				{
					three.first = m_points[1].first - 1; three.second = m_points[1].second;
					if (enemy[three.second][three.first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + three.second * SQUARE_SIDE_SIZE + 15, MIN_Y + three.first * SQUARE_SIDE_SIZE + 15);

						if (enemy[three.second][three.first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[three.second][three.first] = DEAD;
							m_points.push_back(three);

							return new FourDeckState();
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[three.second][three.first] = MISS;

							return nullptr;
						}
					}
				}
				n = 1;
			}
			if (n == 1)  //выстрел вправо
			{
				if (m_points[0].first != 9)
				{
					three.first = m_points[0].first + 1; three.second = m_points[0].second;
					if (enemy[three.second][three.first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + three.second * SQUARE_SIDE_SIZE + 15, MIN_Y + three.first * SQUARE_SIDE_SIZE + 15);

						if (enemy[three.second][three.first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[three.second][three.first] = DEAD;
							m_points.push_back(three);

							std::swap(m_points[0], m_points[1]);   //one всегда должен быть справа
							std::swap(m_points[0], m_points[2]);

							return new FourDeckState();
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[three.second][three.first] = MISS;

							return nullptr;
						}
					}
				}
				n = 0;
			}
		}
	} while (true);
}

AIState* FourDeckState::ShootDeck(char(&enemy)[ROW][COL])
{
	Game* game = Game::GetInstance();
	Point four;
	int n = game->m_gen() % 2;

	do
	{
		if (m_points[0].first == m_points[2].first)  //вертикальный 
		{
			if (n == 0)  //выстрел вверх
			{
				if (m_points[0].second != 0)
				{
					four.first = m_points[0].first; four.second = m_points[0].second - 1;
					if (enemy[four.second][four.first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + four.second * SQUARE_SIDE_SIZE + 15, MIN_Y + four.first * SQUARE_SIDE_SIZE + 15);

						if (enemy[four.second][four.first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[four.second][four.first] = DEAD;

							return new FirstDeckState();
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[four.second][four.first] = MISS;

							return nullptr;
						}
					}
				}
				n = 1;
			}
			if (n == 1)   //выстрел вниз
			{
				if (m_points[2].second != 9)
				{
					four.first = m_points[2].first; four.second = m_points[2].second + 1;
					if (enemy[four.second][four.first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + four.second * SQUARE_SIDE_SIZE + 15, MIN_Y + four.first * SQUARE_SIDE_SIZE + 15);

						if (enemy[four.second][four.first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[four.second][four.first] = DEAD;

							return new FirstDeckState();
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[four.second][four.first] = MISS;

							return nullptr;
						}
					}
				}
				n = 0;
			}
		}
		if (m_points[0].second == m_points[2].second)  //горизонтальный 
		{
			if (n == 0)   //выстрел влево
			{
				if (m_points[2].first != 0)
				{
					four.first = m_points[2].first - 1; four.second = m_points[2].second;
					if (enemy[four.second][four.first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + four.second * SQUARE_SIDE_SIZE + 15, MIN_Y + four.first * SQUARE_SIDE_SIZE + 15);

						if (enemy[four.second][four.first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[four.second][four.first] = DEAD;

							return new FirstDeckState();
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[four.second][four.first] = MISS;

							return nullptr;
						}
					}
				}
				n = 1;
			}
			if (n == 1)  //выстрел вправо
			{
				if (m_points[0].first != 9)
				{
					four.first = m_points[0].first + 1; four.second = m_points[0].second;
					if (enemy[four.second][four.first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + four.second * SQUARE_SIDE_SIZE + 15, MIN_Y + four.first * SQUARE_SIDE_SIZE + 15);

						if (enemy[four.second][four.first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[four.second][four.first] = DEAD;

							return new FirstDeckState();
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[four.second][four.first] = MISS;

							return nullptr;
						}
					}
				}
				n = 0;
			}
		}
	} while (true);
	return nullptr;
}

bool AIState::SankShip(const char(&enemy)[ROW][COL])
{
	bool sank = true;

	for (int i = 0; i < m_points.size(); i++)
	{
		if (m_points[i].second != 0)
			if (enemy[m_points[i].second - 1][m_points[i].first] == ALIVE)
			{
				sank = false;
				return false;
			}
		if (m_points[i].second != 9)
			if (enemy[m_points[i].second + 1][m_points[i].first] == ALIVE)
			{
				sank = false;
				return false;
			}
		if (m_points[i].first != 0)
			if (enemy[m_points[i].second][m_points[i].first - 1] == ALIVE)
			{
				sank = false;
				return false;
			}
		if (m_points[i].first != 9)
			if (enemy[m_points[i].second][m_points[i].first + 1] == ALIVE)
			{
				sank = false;
				return false;
			}
	}
	
	if (sank)
	{
		m_points.clear();
		return true;
	}
}
