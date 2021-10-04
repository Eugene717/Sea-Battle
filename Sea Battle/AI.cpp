#include "AI.h"
#include "Game.h"

using namespace std;

Game* game = Game::GetInstance();

AI::AI(const char& player) :Player(ENEMY_ALIVE)
{ }

bool AI::Shoot(char(&enemy)[ROW][COL])
{
	do
	{
		if (m_FourthDeck)        //��������� ������
		{
			if (Shoot4Deck(enemy))
			{
				game->m_first->SearchDead();
				game->Draw();
				m_FourthDeck = false;
				delete m_four;
				delete m_three;
				delete m_two;
				delete m_one;
				m_four = nullptr;
				m_three = nullptr;
				m_two = nullptr;
				m_one = nullptr;
				if (game->m_first->Loss())
				{
					return true;
				}
			}
			else
			{
				game->Draw();
				return true;
			}
		}
		else if (m_ThirdDeck)   //������ ������
		{
			if (Shoot3Deck(enemy))
			{
				game->m_first->SearchDead();
				game->Draw();
				if (SankShip(enemy))
				{
					m_ThirdDeck = false;
					delete m_three;
					delete m_two;
					delete m_one;
					m_three = nullptr;
					m_two = nullptr;
					m_one = nullptr;
					if (game->m_first->Loss())
					{
						return true;
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
				game->Draw();
				return true;
			}
		}
		else if (m_SecondDeck)   //������ ������
		{			
			if (Shoot2Deck(enemy))  //�����
			{
				game->m_first->SearchDead();
				game->Draw();
				if (SankShip(enemy))  //����
				{
					m_SecondDeck = false;
					delete m_two;
					delete m_one;
					m_two = nullptr;
					m_one = nullptr;
					if (game->m_first->Loss())
					{
						return true;
					}
				}
				else   //�����
				{
					m_SecondDeck = false;
					m_ThirdDeck = true;
				}
			}
			else  //����
			{
				game->Draw();
				return true;
			}
		}
		else   //������ ������
		{
			if (AI::Shoot1Deck(enemy))   //�����
			{
				game->m_first->SearchDead();
				game->Draw();
				if (SankShip(enemy))  //����
				{		
					delete m_one;
					m_one = nullptr;
					if (game->m_first->Loss())
					{
						return true;
					}
				}
				else  //�����
				{
					m_SecondDeck = true;
				}
			}
			else   //����
			{
				game->Draw();
				return true;
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

bool AI::Shoot1Deck(char(&enemy)[ROW][COL])
{
	m_one = new Point;
	do
	{
		m_one->SetValues(RD() % 10, RD() % 10);
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
	int n(RD() % 2);

	if (m_one->GetX() < m_two->GetX() || m_one->GetY() > m_two->GetY())
	{
		swap(m_one, m_two);
	}

	do
	{
		if (m_one->GetX() == m_two->GetX())  //������������ 
		{
			if (n == 0) //������� �����
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

							swap(m_one, m_two);    //one ������ ������ ���� ����
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
			else   //������� ����
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
						else  //������
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
		if (m_one->GetY() == m_two->GetY())  //�������������� 
		{
			if (n == 0)   //������� �����
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
			if (n == 1)  //������� ������
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

							swap(m_one, m_two);   //one ������ ������ ���� ������
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
	int n = RD() % 2;

	do
	{
		if (m_one->GetX() == m_three->GetX())  //������������ 
		{
			if (n == 0)  //������� �����
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
			if (n == 1)   //������� ����
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
		if (m_one->GetY() == m_three->GetY())  //�������������� 
		{
			if (n == 0)   //������� �����
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
			if (n == 1)  //������� ������
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
