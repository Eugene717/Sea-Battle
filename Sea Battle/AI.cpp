#include "AI.h"

using namespace std;

AI::AI(const char& player) :Player(ENEMY_ALIVE)
{ }

void AI::AIlogic(char(&enemy)[ROW][COL], Game& game)
{
	do
	{
		if (m_FourthDeck)        //четвертая палуба
		{
			if (Shoot4Deck(enemy))
			{
				game.m_first->SearchDead();
				game.Draw();
				m_FourthDeck = false;
				delete m_four;
				delete m_three;
				delete m_two;
				delete m_one;
				m_four = nullptr;
				m_three = nullptr;
				m_two = nullptr;
				m_one = nullptr;
				if (game.m_first->Loss())
				{
					return;
				}
			}
			else
			{
				game.Draw();
				return;
			}
		}
		else if (m_ThirdDeck)   //третья палуба
		{
			if (Shoot3Deck(enemy))
			{
				game.m_first->SearchDead();
				game.Draw();
				if (SankShip(enemy))
				{
					m_ThirdDeck = false;
					delete m_three;
					delete m_two;
					delete m_one;
					m_three = nullptr;
					m_two = nullptr;
					m_one = nullptr;
					if (game.m_first->Loss())
					{
						return;
					}
				}
				else
				{
					m_ThirdDeck = false;
					m_FourthDeck = true;
				}
			}
			else
			{
				game.Draw();
				return;
			}
		}
		else if (m_SecondDeck)   //вторая палуба
		{			
			if (Shoot2Deck(enemy))  //попал
			{
				game.m_first->SearchDead();
				game.Draw();
				if (SankShip(enemy))  //убил
				{
					m_SecondDeck = false;
					delete m_two;
					delete m_one;
					m_two = nullptr;
					m_one = nullptr;
					if (game.m_first->Loss())
					{
						return;
					}
				}
				else   //ранил
				{
					m_SecondDeck = false;
					m_ThirdDeck = true;
				}
			}
			else  //мимо
			{
				game.Draw();
				return;
			}
		}
		else   //первая палуба
		{
			if (AI::Shoot(enemy, game.m_window))   //попал
			{
				game.m_first->SearchDead();
				game.Draw();
				if (SankShip(enemy))  //убил
				{		
					delete m_one;
					m_one = nullptr;
					if (game.m_first->Loss())
					{
						return;
					}
				}
				else  //ранил
				{
					m_SecondDeck = true;
				}
			}
			else   //мимо
			{
				game.Draw();
				return;
			}
		}
	} while (true);
}

bool AI::SankShip(const char(&enemy)[ROW][COL])
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
		return true;
	else
		return false;
}

bool AI::Shoot(char(&enemy)[ROW][COL], sf::RenderWindow& window)
{
	m_one = new Point;
	do
	{
		m_one->SetValues(RD() % 10, RD() % 10);
		if (enemy[m_one->GetY()][m_one->GetX()] != MISS && enemy[m_one->GetY()][m_one->GetX()] != DEAD)
		{
			if (enemy[m_one->GetY()][m_one->GetX()] == ALIVE)
			{
				enemy[m_one->GetY()][m_one->GetX()] = DEAD;
				return true;
			}
			else
			{
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
		switch (int n(RD() % 4); n)
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
			else if (enemy[m_two->GetY()][m_two->GetX()] == ALIVE)
			{
				enemy[m_two->GetY()][m_two->GetX()] = DEAD;
				return true;
			}
			else
			{
				enemy[m_two->GetY()][m_two->GetX()] = MISS;
				delete m_two;
				return false;
			}
		}
	} while (true);
}

bool AI::Shoot3Deck(char(&enemy)[ROW][COL])
{
	m_three = new Point;
	int n(RD() % 2);

	if (m_one->GetX() < m_two->GetX() || m_one->GetY() > m_two->GetY())
	{
		swap(m_one, m_two);
	}

	do
	{
		if (m_one->GetX() == m_two->GetX())  //вертикальный блять
		{
			if (n == 0) //выстрел вверх
			{
				if (m_one->GetY() != 0)
				{
					m_three->SetValues(m_one->GetX(), m_one->GetY() + UP);
					if (enemy[m_three->GetY()][m_three->GetX()] != MISS)
					{
						if (enemy[m_three->GetY()][m_three->GetX()] == ALIVE)
						{
							enemy[m_three->GetY()][m_three->GetX()] = DEAD;

							swap(m_one, m_two);    //one всегда должен быть выше
							swap(m_one, m_three);

							return true;
						}
						else
						{
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
						if (enemy[m_three->GetY()][m_three->GetX()] == ALIVE)
						{
							enemy[m_three->GetY()][m_three->GetX()] = DEAD;
							return true;
						}
						else  //промах
						{
							enemy[m_three->GetY()][m_three->GetX()] = MISS;
							delete m_three;
							return false;
						}
					}
				}
				n = 0;
			}
		}
		if (m_one->GetY() == m_two->GetY())  //горизонтальный ебать
		{
			if (n == 0)   //выстрел влево
			{
				if (m_two->GetX() != 0)
				{
					m_three->SetValues(m_two->GetX() + LEFT, m_two->GetY());
					if (enemy[m_three->GetY()][m_three->GetX()] != MISS)
					{
						if (enemy[m_three->GetY()][m_three->GetX()] == ALIVE)
						{
							enemy[m_three->GetY()][m_three->GetX()] = DEAD;
							return true;
						}
						else
						{
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
						if (enemy[m_three->GetY()][m_three->GetX()] == ALIVE)
						{
							enemy[m_three->GetY()][m_three->GetX()] = DEAD;

							swap(m_one, m_two);   //one всегда должен быть справа
							swap(m_one, m_three);

							return true;
						}
						else
						{
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
	int n = RD() % 2;

	do
	{
		if (m_one->GetX() == m_three->GetX())  //вертикальный блять
		{
			if (n == 0)  //выстрел вверх
			{
				if (m_one->GetY() != 0)
				{
					m_four->SetValues(m_one->GetX(), m_one->GetY() + UP);
					if (enemy[m_four->GetY()][m_four->GetX()] != MISS)
					{
						if (enemy[m_four->GetY()][m_four->GetX()] == ALIVE)
						{
							enemy[m_four->GetY()][m_four->GetX()] = DEAD;
							return true;
						}
						else
						{
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
						if (enemy[m_four->GetY()][m_four->GetX()] == ALIVE)
						{
							enemy[m_four->GetY()][m_four->GetX()] = DEAD;
							return true;
						}
						else
						{
							enemy[m_four->GetY()][m_four->GetX()] = MISS;
							delete m_four;
							return false;
						}
					}
				}
				n = 0;
			}
		}
		if (m_one->GetY() == m_three->GetY())  //горизонтальный ебать
		{
			if (n == 0)   //выстрел влево
			{
				if (m_three->GetX() != 0)
				{
					m_four->SetValues(m_three->GetX() + LEFT, m_three->GetY());
					if (enemy[m_four->GetY()][m_four->GetX()] != MISS)
					{
						if (enemy[m_four->GetY()][m_four->GetX()] == ALIVE)
						{
							enemy[m_four->GetY()][m_four->GetX()] = DEAD;
							return true;
						}
						else
						{
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
						if (enemy[m_four->GetY()][m_four->GetX()] == ALIVE)
						{
							enemy[m_four->GetY()][m_four->GetX()] = DEAD;
							return true;
						}
						else
						{
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
