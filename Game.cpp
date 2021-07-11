#include "Game.h"
using namespace std;

void Game::Draw()
{
	system("cls");
	cout << "\t\t\t  ���� ����" << "\t\t\t\t\t\t" << "\b���� ����������" << endl << endl;
	cout << '\t' << "    A   B   C   D   E   F   G   H   I   J\t\t    A   B   C   D   E   F   G   H   I   J" << endl;
	cout << "\t  #########################################\t\t  #########################################" << endl;
	for (int y = 0; y < ROW; y++)
	{
		cout << "\t" << y << " | ";
		for (int x = 0; x < COL; x++)
		{
			if (m_first->m_Board[y][x] == EMPTY)
				cout << ' ';
			else
				cout << m_first->m_Board[y][x];
			cout << " | ";
		}
		cout << "\t\t";
		cout << y << " | ";
		for (int x = 0; x < COL; x++)
		{
			if (m_second->m_Board[y][x] == EMPTY)
				cout << ' ';
			else
				cout << m_second->m_Board[y][x];
			cout << " | ";
		}
		if (y != 9)
			cout << "\n\t  |---------------------------------------|\t\t  |---------------------------------------|" << endl;
		else
			cout << "\n\t  #########################################\t\t  #########################################" << endl << endl;
	}
}

char Yes_or_No()
{
	char let;
	while (true)
	{
		switch (cin >> let; let)
		{
		case 'y': case 'Y':
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return 'y';
		case 'n': case 'N':
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return 'n';
		default:
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
}

void Game::AskDisposition()
{
	while (true)
	{
		m_first->RandomShipsArrangement();
		Draw();
		cout << "�������� ����� ������������ ��������(y/n)? ";
		if (Yes_or_No() == 'y')
		{
			return;
		}
	}
}

int Game::Menu()
{
	cout << "�������� �� ������ ��� ������ �������\n"
		<< "1.��������� ����\n"
		<< "2.C������ ����\n"
		<< "3.��������� ����\n"
		<< "4.���������\n"
		<< "5.�����\n";
	while (true)
	{
		switch (_getch())
		{
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		default:
			"������������ �������\n������� ������: ";
			break;
		}
	}
}

void Game::SinglePlayer()
{
	m_first = new Human(ALIVE);
	m_second = new AI(ENEMY_ALIVE);

	AskDisposition();
	m_second->RandomShipsArrangement();
	Draw();

	if (FirstTurn() == 'F')
	{
		do
		{
			while (true)  //�����
			{
				cout << "��� �������: ";
				if (m_first->Shoot(m_second->m_Board))
				{
					m_second->SearchDead();
					Draw();
					if (m_second->Loss())
					{
						AnnounceWinner(0);
						delete m_first;
						delete m_second;
						m_first = nullptr;
						m_second = nullptr;
						return;
					}
				}
				else
				{
					Draw();
					break;
				}
			}
			while (true)  //��
			{
				((AI*)m_second)->AI::AIlogic(m_first->m_Board, *this);
				if (m_first->Loss())
				{
					AnnounceWinner(1);
					delete m_first;
					delete m_second;
					m_first = nullptr;
					m_second = nullptr;
					return;
				}
				else
					break;
			}
		} while (true);
	}
	else
	{
		do
		{
			while (true)  //��
			{
				((AI*)m_second)->AI::AIlogic(m_first->m_Board, *this);
				if (m_first->Loss())
				{
					AnnounceWinner(1);
					delete m_first;
					delete m_second;
					m_first = nullptr;
					m_second = nullptr;
					return;
				}
				else
					break;
			}
			while (true)  //�����
			{
				cout << "��� �������: ";
				if (m_first->Shoot(m_second->m_Board))
				{
					m_second->SearchDead();
					Draw();
					if (m_second->Loss())
					{
						AnnounceWinner(0);
						delete m_first;
						delete m_second;
						m_first = nullptr;
						m_second = nullptr;
						return;
					}
				}
				else
				{
					Draw();
					break;
				}
			}
		} while (true);
	}
}

char Game::FirstTurn()
{
	if (RD() % 2 == 0)
		return 'F';
	else
		return 'S';
}

void Game::AnnounceWinner(int player)
{
	if (player == 0)
	{
		cout << "\t\t\t\t\t\t    �� ��������!\n";
	}
	else
	{
		cout << "\t\t\t\t\t\t    �� ���������!\n";
	}
}
