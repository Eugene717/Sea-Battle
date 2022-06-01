#include "AI.h"
#include "Game.h"

using namespace std;
Game* game = Game::GetInstance();
using Point = std::pair<int, int>;

struct AI_IMPL
{
	Point* m_one;
	Point* m_two;
	Point* m_three;
	Point* m_four;
	bool m_SecondDeck = false;
	bool m_ThirdDeck = false;
	bool m_FourthDeck = false;
};

AI::AI(const char& player) :Player(ENEMY_ALIVE, 2)
{
	m_pImpl = new AI_IMPL;
	m_pImpl->m_one = nullptr;
	m_pImpl->m_two = nullptr;
	m_pImpl->m_three = nullptr;
	m_pImpl->m_four = nullptr;
}

AI::~AI()
{
	if (m_pImpl->m_one != nullptr)
		delete m_pImpl->m_one;
	if (m_pImpl->m_two != nullptr)
		delete m_pImpl->m_two;
	if (m_pImpl->m_three != nullptr)
		delete m_pImpl->m_three;
	if (m_pImpl->m_four != nullptr)
		delete m_pImpl->m_four;
	delete m_pImpl;
}

bool AI::Shoot(char(&enemy)[ROW][COL])
{
	do
	{
		if (m_pImpl->m_FourthDeck)        //четвертая палуба
		{
			if (Shoot4Deck(enemy))
			{
				m_pImpl->m_FourthDeck = false;

				return true;
			}
			else
				return false;
		}
		else if (m_pImpl->m_ThirdDeck)   //третья палуба
		{
			if (Shoot3Deck(enemy))
			{
				m_pImpl->m_FourthDeck = true;
				m_pImpl->m_ThirdDeck = false;

				return true;
			}
			else
				return false;
		}
		else if (m_pImpl->m_SecondDeck)   //вторая палуба
		{			
			if (Shoot2Deck(enemy))  //попал
			{
				m_pImpl->m_ThirdDeck = true;
				m_pImpl->m_SecondDeck = false;

				return true;
			}
			else  //мимо
				return false;
		}
		else   //первая палуба
		{
			if (AI::Shoot1Deck(enemy))   //попал
			{
				m_pImpl->m_SecondDeck = true;

				return true;
			}
			else   //мимо
				return false;
		}
	} while (true);
}

void AI::SankShip(const char(&enemy)[ROW][COL])
{
	int n = 0;

	if (m_pImpl->m_one != nullptr)
	{
		if (m_pImpl->m_one->second != 0)
			if (enemy[m_pImpl->m_one->second - 1][m_pImpl->m_one->first] == ALIVE)
				n++;
		if (m_pImpl->m_one->second != 9)
			if (enemy[m_pImpl->m_one->second + 1][m_pImpl->m_one->first] == ALIVE)
				n++;
		if (m_pImpl->m_one->first != 0)
			if (enemy[m_pImpl->m_one->second][m_pImpl->m_one->first - 1] == ALIVE)
				n++;
		if (m_pImpl->m_one->first != 9)
			if (enemy[m_pImpl->m_one->second][m_pImpl->m_one->first + 1] == ALIVE)
				n++;
	}
	if (m_pImpl->m_two != nullptr)
	{
		if (m_pImpl->m_two->second != 0)
			if (enemy[m_pImpl->m_two->second - 1][m_pImpl->m_two->first] == ALIVE)
				n++;
		if (m_pImpl->m_two->second != 9)
			if (enemy[m_pImpl->m_two->second + 1][m_pImpl->m_two->first] == ALIVE)
				n++;
		if (m_pImpl->m_two->first != 0)
			if (enemy[m_pImpl->m_two->second][m_pImpl->m_two->first - 1] == ALIVE)
				n++;
		if (m_pImpl->m_two->first != 9)
			if (enemy[m_pImpl->m_two->second][m_pImpl->m_two->first + 1] == ALIVE)
				n++;
	}
	if (m_pImpl->m_three != nullptr)
	{
		if (m_pImpl->m_three->second != 0)
			if (enemy[m_pImpl->m_three->second - 1][m_pImpl->m_three->first] == ALIVE)
				n++;
		if (m_pImpl->m_three->second != 9)
			if (enemy[m_pImpl->m_three->second + 1][m_pImpl->m_three->first] == ALIVE)
				n++;
		if (m_pImpl->m_three->first != 0)
			if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first - 1] == ALIVE)
				n++;
		if (m_pImpl->m_three->first != 9)
			if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first + 1] == ALIVE)
				n++;
	}

	if (n == 0)
	{
		m_pImpl->m_SecondDeck = false;
		m_pImpl->m_ThirdDeck = false;
		m_pImpl->m_FourthDeck = false;
		if (m_pImpl->m_one != nullptr) delete m_pImpl->m_one;
		m_pImpl->m_one = nullptr;
		if (m_pImpl->m_two != nullptr) delete m_pImpl->m_two;
		m_pImpl->m_two = nullptr;
		if (m_pImpl->m_three != nullptr) delete m_pImpl->m_three;
		m_pImpl->m_three = nullptr;
		if (m_pImpl->m_four != nullptr) delete m_pImpl->m_four;
		m_pImpl->m_four = nullptr;
	}
}

bool AI::Shoot1Deck(char(&enemy)[ROW][COL])
{
	m_pImpl->m_one = new Point;
	do
	{
		m_pImpl->m_one->first = game->m_gen() % 10; m_pImpl->m_one->second = game->m_gen() % 10;
		if (enemy[m_pImpl->m_one->second][m_pImpl->m_one->first] != MISS && enemy[m_pImpl->m_one->second][m_pImpl->m_one->first] != DEAD)
		{
			sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_one->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_one->first * SQUARE_SIDE_SIZE + 15);

			if (enemy[m_pImpl->m_one->second][m_pImpl->m_one->first] == ALIVE)
			{
				game->PlaySound(Sounds::enemy);
				game->DrawShot(middleCell, sf::Color::Red);
				enemy[m_pImpl->m_one->second][m_pImpl->m_one->first] = DEAD;
				return true;
			}
			else
			{
				game->PlaySound(Sounds::miss);
				game->DrawShot(middleCell, sf::Color::Color(858585));
				enemy[m_pImpl->m_one->second][m_pImpl->m_one->first] = MISS;
				delete m_pImpl->m_one;
				return false;
			}
		}
	} while (true);
}

bool AI::Shoot2Deck(char(&enemy)[ROW][COL])
{
	m_pImpl->m_two = new Point;
	bool isFree = false;

	do
	{
		switch (int n(game->m_gen() % 4); n)
		{
		case 0:
			if (m_pImpl->m_one->second != 0)
			{
				m_pImpl->m_two->first = m_pImpl->m_one->first; m_pImpl->m_two->second = m_pImpl->m_one->second - 1;
				isFree = true;
			}
			break;
		case 1:
			if (m_pImpl->m_one->first != 9)
			{
				m_pImpl->m_two->first = m_pImpl->m_one->first + 1; m_pImpl->m_two->second = m_pImpl->m_one->second;
				isFree = true;
			}
			break;
		case 2:
			if (m_pImpl->m_one->second != 9)
			{
				m_pImpl->m_two->first = m_pImpl->m_one->first; m_pImpl->m_two->second = m_pImpl->m_one->second + 1;
				isFree = true;
			}
			break;
		case 3:
			if (m_pImpl->m_one->first != 0)
			{
				m_pImpl->m_two->first = m_pImpl->m_one->first - 1; m_pImpl->m_two->second = m_pImpl->m_one->second;
				isFree = true;
			}
			break;
		}
		if (isFree)
		{
			if (enemy[m_pImpl->m_two->second][m_pImpl->m_two->first] == MISS)
				isFree = false;
			else
			{
				sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_two->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_two->first * SQUARE_SIDE_SIZE + 15);

				if (enemy[m_pImpl->m_two->second][m_pImpl->m_two->first] == ALIVE)
				{
					game->PlaySound(Sounds::enemy);
					game->DrawShot(middleCell, sf::Color::Red);
					enemy[m_pImpl->m_two->second][m_pImpl->m_two->first] = DEAD;
					return true;
				}
				else
				{
					game->PlaySound(Sounds::miss);
					game->DrawShot(middleCell, sf::Color::Color(858585));
					enemy[m_pImpl->m_two->second][m_pImpl->m_two->first] = MISS;
					delete m_pImpl->m_two;
					return false;
				}
			}
		}
	} while (true);
}

bool AI::Shoot3Deck(char(&enemy)[ROW][COL])
{
	m_pImpl->m_three = new Point;
	int n(game->m_gen() % 2);

	if (m_pImpl->m_one->first < m_pImpl->m_two->first || m_pImpl->m_one->second > m_pImpl->m_two->second)
	{
		swap(m_pImpl->m_one, m_pImpl->m_two);
	}

	do
	{
		if (m_pImpl->m_one->first == m_pImpl->m_two->first)  //вертикальный 
		{
			if (n == 0) //выстрел вверх
			{
				if (m_pImpl->m_one->second != 0)
				{
					m_pImpl->m_three->first = m_pImpl->m_one->first; m_pImpl->m_three->second = m_pImpl->m_one->second - 1;
					if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_three->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_three->first * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] = DEAD;

							swap(m_pImpl->m_one, m_pImpl->m_two);    //one всегда должен быть выше
							swap(m_pImpl->m_one, m_pImpl->m_three);

							return true;
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] = MISS;

							delete m_pImpl->m_three;
							return false;
						}
					}					
				}
				n = 1;
			}
			else   //выстрел вниз
			{
				if (m_pImpl->m_two->second != 9)
				{
					m_pImpl->m_three->first = m_pImpl->m_two->first; m_pImpl->m_three->second = m_pImpl->m_two->second + 1;
					if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_three->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_three->first * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] = DEAD;

							return true;
						}
						else  //промах
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] = MISS;

							delete m_pImpl->m_three;
							return false;
						}
					}
				}
				n = 0;
			}
		}
		if (m_pImpl->m_one->second == m_pImpl->m_two->second)  //горизонтальный 
		{
			if (n == 0)   //выстрел влево
			{
				if (m_pImpl->m_two->first != 0)
				{
					m_pImpl->m_three->first = m_pImpl->m_two->first - 1; m_pImpl->m_three->second = m_pImpl->m_two->second;
					if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_three->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_three->first * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] = DEAD;

							return true;
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] = MISS;

							return false;
						}
					}
				}
				n = 1;
			}
			if (n == 1)  //выстрел вправо
			{
				if (m_pImpl->m_one->first != 9)
				{
					m_pImpl->m_three->first = m_pImpl->m_one->first + 1; m_pImpl->m_three->second = m_pImpl->m_one->second;
					if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_three->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_three->first * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] = DEAD;

							swap(m_pImpl->m_one, m_pImpl->m_two);   //one всегда должен быть справа
							swap(m_pImpl->m_one, m_pImpl->m_three);

							return true;
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_pImpl->m_three->second][m_pImpl->m_three->first] = MISS;

							delete m_pImpl->m_three;
							return false;
						}
					}
				}
				n = 0;
			}
		}
	} while (true);
}

bool AI::Shoot4Deck(char(&enemy)[ROW][COL])
{
	m_pImpl->m_four = new Point;
	int n = game->m_gen() % 2;

	do
	{
		if (m_pImpl->m_one->first == m_pImpl->m_three->first)  //вертикальный 
		{
			if (n == 0)  //выстрел вверх
			{
				if (m_pImpl->m_one->second != 0)
				{
					m_pImpl->m_four->first = m_pImpl->m_one->first; m_pImpl->m_four->second = m_pImpl->m_one->second - 1;
					if (enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_four->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_four->first * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] = DEAD;

							return true;
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] = MISS;

							delete m_pImpl->m_four;
							return false;
						}
					}
				}
				n = 1;
			}
			if (n == 1)   //выстрел вниз
			{
				if (m_pImpl->m_three->second != 9)
				{
					m_pImpl->m_four->first = m_pImpl->m_three->first; m_pImpl->m_four->second = m_pImpl->m_three->second + 1;
					if (enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_four->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_four->first * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] = DEAD;

							return true;
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] = MISS;

							delete m_pImpl->m_four;
							return false;
						}
					}
				}
				n = 0;
			}
		}
		if (m_pImpl->m_one->second == m_pImpl->m_three->second)  //горизонтальный 
		{
			if (n == 0)   //выстрел влево
			{
				if (m_pImpl->m_three->first != 0)
				{
					m_pImpl->m_four->first = m_pImpl->m_three->first - 1; m_pImpl->m_four->second = m_pImpl->m_three->second;
					if (enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_four->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_four->first * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] = DEAD;

							return true;
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] = MISS;

							delete m_pImpl->m_four;
							return false;
						}
					}
				}
				n = 1;
			}
			if (n == 1)  //выстрел вправо
			{
				if (m_pImpl->m_one->first != 9)
				{
					m_pImpl->m_four->first = m_pImpl->m_one->first + 1; m_pImpl->m_four->second = m_pImpl->m_one->second;
					if (enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_pImpl->m_four->second * SQUARE_SIDE_SIZE + 15, MIN_Y + m_pImpl->m_four->first * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] == ALIVE)
						{
							game->PlaySound(Sounds::enemy);
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] = DEAD;

							return true;
						}
						else
						{
							game->PlaySound(Sounds::miss);
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_pImpl->m_four->second][m_pImpl->m_four->first] = MISS;

							delete m_pImpl->m_four;
							return false;
						}
					}
				}
				n = 0;
			}
		}
	} while (true);
}
