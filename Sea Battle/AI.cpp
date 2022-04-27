#include "AI.h"
#include "Game.h"

using namespace std;
Game* game = Game::GetInstance();

AI::AI(const char& player) :Player(ENEMY_ALIVE, 2)
{ }

AI::~AI()
{
	if (m_one != nullptr)
		delete m_one;
	if (m_two != nullptr)
		delete m_two;
	if (m_three != nullptr)
		delete m_three;
	if (m_four != nullptr)
		delete m_four;
}

bool AI::Shoot(char(&enemy)[ROW][COL])
{
	do
	{
		if (m_FourthDeck)        //четвертая палуба
		{
			if (Shoot4Deck(enemy))
			{
				m_FourthDeck = false;

				return true;
			}
			else
				return false;
		}
		else if (m_ThirdDeck)   //третья палуба
		{
			if (Shoot3Deck(enemy))
			{
				m_FourthDeck = true;
				m_ThirdDeck = false;

				return true;
			}
			else
				return false;
		}
		else if (m_SecondDeck)   //вторая палуба
		{			
			if (Shoot2Deck(enemy))  //попал
			{
				m_ThirdDeck = true;
				m_SecondDeck = false;

				return true;
			}
			else  //мимо
				return false;
		}
		else   //первая палуба
		{
			if (AI::Shoot1Deck(enemy))   //попал
			{
				m_SecondDeck = true;

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

	if (m_one != nullptr)
	{
		if (m_one->GetY() != 0)
			if (enemy[m_one->GetY() + LEFT][m_one->GetX()] == ALIVE)
				n++;
		if (m_one->GetY() != 9)
			if (enemy[m_one->GetY() + RIGHT][m_one->GetX()] == ALIVE)
				n++;
		if (m_one->GetX() != 0)
			if (enemy[m_one->GetY()][m_one->GetX() + UP] == ALIVE)
				n++;
		if (m_one->GetX() != 9)
			if (enemy[m_one->GetY()][m_one->GetX() + DOWN] == ALIVE)
				n++;
	}
	if (m_two != nullptr)
	{
		if (m_two->GetY() != 0)
			if (enemy[m_two->GetY() + LEFT][m_two->GetX()] == ALIVE)
				n++;
		if (m_two->GetY() != 9)
			if (enemy[m_two->GetY() + RIGHT][m_two->GetX()] == ALIVE)
				n++;
		if (m_two->GetX() != 0)
			if (enemy[m_two->GetY()][m_two->GetX() + UP] == ALIVE)
				n++;
		if (m_two->GetX() != 9)
			if (enemy[m_two->GetY()][m_two->GetX() + DOWN] == ALIVE)
				n++;
	}
	if (m_three != nullptr)
	{
		if (m_three->GetY() != 0)
			if (enemy[m_three->GetY() + LEFT][m_three->GetX()] == ALIVE)
				n++;
		if (m_three->GetY() != 9)
			if (enemy[m_three->GetY() + RIGHT][m_three->GetX()] == ALIVE)
				n++;
		if (m_three->GetX() != 0)
			if (enemy[m_three->GetY()][m_three->GetX() + UP] == ALIVE)
				n++;
		if (m_three->GetX() != 9)
			if (enemy[m_three->GetY()][m_three->GetX() + DOWN] == ALIVE)
				n++;
	}

	if (n == 0)
	{
		m_SecondDeck = false;
		m_ThirdDeck = false;
		m_FourthDeck = false;
		if (m_one != nullptr) delete m_one;
		m_one = nullptr;
		if (m_two != nullptr) delete m_two;
		m_two = nullptr;
		if (m_three != nullptr) delete m_three;
		m_three = nullptr;
		if (m_four != nullptr) delete m_four;
		m_four = nullptr;
	}
}

bool AI::Shoot1Deck(char(&enemy)[ROW][COL])
{
	m_one = new Point;
	do
	{
		m_one->SetValues(game->m_gen() % 10, game->m_gen() % 10);
		if (enemy[m_one->GetY()][m_one->GetX()] != MISS && enemy[m_one->GetY()][m_one->GetX()] != DEAD)
		{
			sf::Vector2f middleCell(MIN_F_BOARD_X + m_one->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_one->GetX() * SQUARE_SIDE_SIZE + 15);

			if (enemy[m_one->GetY()][m_one->GetX()] == ALIVE)
			{
				game->DrawShot(middleCell, sf::Color::Red);
				enemy[m_one->GetY()][m_one->GetX()] = DEAD;
				return true;
			}
			else
			{
				game->DrawShot(middleCell, sf::Color::Color(858585));
				enemy[m_one->GetY()][m_one->GetX()] = MISS;
				delete m_one;
				return false;
			}
		}
	} while (true);
}

bool AI::Shoot2Deck(char(&enemy)[ROW][COL])
{
	m_two = new Point;
	bool isFree = false;

	do
	{
		switch (int n(game->m_gen() % 4); n)
		{
		case 0:
			if (m_one->GetY() != 0)
			{
				m_two->SetValues(m_one->GetX(), m_one->GetY() + UP);
				isFree = true;
			}
			break;
		case 1:
			if (m_one->GetX() != 9)
			{
				m_two->SetValues(m_one->GetX() + RIGHT, m_one->GetY());
				isFree = true;
			}
			break;
		case 2:
			if (m_one->GetY() != 9)
			{
				m_two->SetValues(m_one->GetX(), m_one->GetY() + DOWN);
				isFree = true;
			}
			break;
		case 3:
			if (m_one->GetX() != 0)
			{
				m_two->SetValues(m_one->GetX() + LEFT, m_one->GetY());
				isFree = true;
			}
			break;
		}
		if (isFree)
		{
			if (enemy[m_two->GetY()][m_two->GetX()] == MISS)
				isFree = false;
			else
			{
				sf::Vector2f middleCell(MIN_F_BOARD_X + m_two->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_two->GetX() * SQUARE_SIDE_SIZE + 15);

				if (enemy[m_two->GetY()][m_two->GetX()] == ALIVE)
				{
					game->DrawShot(middleCell, sf::Color::Red);
					enemy[m_two->GetY()][m_two->GetX()] = DEAD;
					return true;
				}
				else
				{
					game->DrawShot(middleCell, sf::Color::Color(858585));
					enemy[m_two->GetY()][m_two->GetX()] = MISS;
					delete m_two;
					return false;
				}
			}
		}
	} while (true);
}

bool AI::Shoot3Deck(char(&enemy)[ROW][COL])
{
	m_three = new Point;
	int n(game->m_gen() % 2);

	if (m_one->GetX() < m_two->GetX() || m_one->GetY() > m_two->GetY())
	{
		swap(m_one, m_two);
	}

	do
	{
		if (m_one->GetX() == m_two->GetX())  //вертикальный 
		{
			if (n == 0) //выстрел вверх
			{
				if (m_one->GetY() != 0)
				{
					m_three->SetValues(m_one->GetX(), m_one->GetY() + UP);
					if (enemy[m_three->GetY()][m_three->GetX()] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_three->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_three->GetX() * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_three->GetY()][m_three->GetX()] == ALIVE)
						{
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_three->GetY()][m_three->GetX()] = DEAD;

							swap(m_one, m_two);    //one всегда должен быть выше
							swap(m_one, m_three);

							return true;
						}
						else
						{
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_three->GetY()][m_three->GetX()] = MISS;

							delete m_three;
							return false;
						}
					}					
				}
				n = 1;
			}
			else   //выстрел вниз
			{
				if (m_two->GetY() != 9)
				{
					m_three->SetValues(m_two->GetX(), m_two->GetY() + DOWN);
					if (enemy[m_three->GetY()][m_three->GetX()] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_three->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_three->GetX() * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_three->GetY()][m_three->GetX()] == ALIVE)
						{
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_three->GetY()][m_three->GetX()] = DEAD;

							return true;
						}
						else  //промах
						{
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_three->GetY()][m_three->GetX()] = MISS;

							delete m_three;
							return false;
						}
					}
				}
				n = 0;
			}
		}
		if (m_one->GetY() == m_two->GetY())  //горизонтальный 
		{
			if (n == 0)   //выстрел влево
			{
				if (m_two->GetX() != 0)
				{
					m_three->SetValues(m_two->GetX() + LEFT, m_two->GetY());
					if (enemy[m_three->GetY()][m_three->GetX()] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_three->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_three->GetX() * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_three->GetY()][m_three->GetX()] == ALIVE)
						{
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_three->GetY()][m_three->GetX()] = DEAD;

							return true;
						}
						else
						{
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_three->GetY()][m_three->GetX()] = MISS;

							return false;
						}
					}
				}
				n = 1;
			}
			if (n == 1)  //выстрел вправо
			{
				if (m_one->GetX() != 9)
				{
					m_three->SetValues(m_one->GetX() + RIGHT, m_one->GetY());
					if (enemy[m_three->GetY()][m_three->GetX()] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_three->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_three->GetX() * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_three->GetY()][m_three->GetX()] == ALIVE)
						{
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_three->GetY()][m_three->GetX()] = DEAD;

							swap(m_one, m_two);   //one всегда должен быть справа
							swap(m_one, m_three);

							return true;
						}
						else
						{
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_three->GetY()][m_three->GetX()] = MISS;

							delete m_three;
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
	m_four = new Point;
	int n = game->m_gen() % 2;

	do
	{
		if (m_one->GetX() == m_three->GetX())  //вертикальный 
		{
			if (n == 0)  //выстрел вверх
			{
				if (m_one->GetY() != 0)
				{
					m_four->SetValues(m_one->GetX(), m_one->GetY() + UP);
					if (enemy[m_four->GetY()][m_four->GetX()] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_four->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_four->GetX() * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_four->GetY()][m_four->GetX()] == ALIVE)
						{
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_four->GetY()][m_four->GetX()] = DEAD;

							return true;
						}
						else
						{
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_four->GetY()][m_four->GetX()] = MISS;

							delete m_four;
							return false;
						}
					}
				}
				n = 1;
			}
			if (n == 1)   //выстрел вниз
			{
				if (m_three->GetY() != 9)
				{
					m_four->SetValues(m_three->GetX(), m_three->GetY() + DOWN);
					if (enemy[m_four->GetY()][m_four->GetX()] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_four->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_four->GetX() * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_four->GetY()][m_four->GetX()] == ALIVE)
						{
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_four->GetY()][m_four->GetX()] = DEAD;

							return true;
						}
						else
						{
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_four->GetY()][m_four->GetX()] = MISS;

							delete m_four;
							return false;
						}
					}
				}
				n = 0;
			}
		}
		if (m_one->GetY() == m_three->GetY())  //горизонтальный 
		{
			if (n == 0)   //выстрел влево
			{
				if (m_three->GetX() != 0)
				{
					m_four->SetValues(m_three->GetX() + LEFT, m_three->GetY());
					if (enemy[m_four->GetY()][m_four->GetX()] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_four->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_four->GetX() * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_four->GetY()][m_four->GetX()] == ALIVE)
						{
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_four->GetY()][m_four->GetX()] = DEAD;

							return true;
						}
						else
						{
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_four->GetY()][m_four->GetX()] = MISS;

							delete m_four;
							return false;
						}
					}
				}
				n = 1;
			}
			if (n == 1)  //выстрел вправо
			{
				if (m_one->GetX() != 9)
				{
					m_four->SetValues(m_one->GetX() + RIGHT, m_one->GetY());
					if (enemy[m_four->GetY()][m_four->GetX()] != MISS)
					{
						sf::Vector2f middleCell(MIN_F_BOARD_X + m_four->GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + m_four->GetX() * SQUARE_SIDE_SIZE + 15);

						if (enemy[m_four->GetY()][m_four->GetX()] == ALIVE)
						{
							game->DrawShot(middleCell, sf::Color::Red);
							enemy[m_four->GetY()][m_four->GetX()] = DEAD;

							return true;
						}
						else
						{
							game->DrawShot(middleCell, sf::Color(858585));
							enemy[m_four->GetY()][m_four->GetX()] = MISS;

							delete m_four;
							return false;
						}
					}
				}
				n = 0;
			}
		}
	} while (true);
}
