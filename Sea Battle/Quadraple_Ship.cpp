#include "Quadraple_Ship.h"

using namespace std;

Quadraple_Ship::Quadraple_Ship()
{
	m_x1 = new int;
	m_y1 = new int;
	m_x2 = new int;
	m_y2 = new int;
	m_x3 = new int;
	m_y3 = new int;
	m_x4 = new int;
	m_y4 = new int;
}

Quadraple_Ship::~Quadraple_Ship()
{
	delete m_x1;
	delete m_y1;
	delete m_x2;
	delete m_y2;
	delete m_x3;
	delete m_y3;
	delete m_x4;
	delete m_y4;
}

void Quadraple_Ship::RandomlyArrange(char(&arr)[ROW][COL], char player)
{
	int dir;
	bool isFree = false;
	do
	{
		*m_x1 = RD() % 10;
		*m_y1 = RD() % 10;
		//вторая палуба
		dir = RD() % 4;
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
		//третья палуба		
		if (isFree)
		{
			if (dir == 2)
			{
				if (*m_y2 != 9)
				{
					*m_y3 = *m_y2 + 1;
					*m_x3 = *m_x2;
				}
				else  //*m_y2 == 9
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
				else  //*m_x2 == 0
				{
					*m_x3 = *m_x2;
					*m_y3 = *m_y2;
					*m_x2 = *m_x1;
					*m_x1 = *m_x1 + 1;
				}
			}
			//четвертая палуба
			if (dir == 2)
			{
				if (*m_y3 != 9)
				{
					*m_y4 = *m_y3 + 1;
					*m_x4 = *m_x3;
				}
				else  //m_y3 == 9
				{
					*m_y4 = *m_y3;
					*m_x4 = *m_x3;
					*m_y3 = *m_y2;
					*m_y2 = *m_y1;
					*m_y1 = *m_y1 - 1;
				}
			}
			else  // dir == 3
			{
				if (*m_x3 != 0)
				{
					*m_x4 = *m_x3 - 1;
					*m_y4 = *m_y3;
				}
				else  //m_x2 == 0
				{
					*m_x4 = *m_x3;
					*m_y4 = *m_y3;
					*m_x3 = *m_x2;
					*m_x2 = *m_x1;
					*m_x1 = *m_x1 + 1;
				}
			}
			m_stat1 = &arr[*m_y1][*m_x1];
			m_stat2 = &arr[*m_y2][*m_x2];
			m_stat3 = &arr[*m_y3][*m_x3];
			m_stat4 = &arr[*m_y4][*m_x4];
			*m_stat1 = player;
			*m_stat2 = player;
			*m_stat3 = player;
			*m_stat4 = player;
			Zone(arr, m_x1, m_y1);
			Zone(arr, m_x2, m_y2);
			Zone(arr, m_x3, m_y3);
			Zone(arr, m_x4, m_y4);
			return;
		}
	} while (true);
}

bool Quadraple_Ship::Kill(char(&arr)[ROW][COL])
{
	if (*m_stat1 == DEAD && *m_stat2 == DEAD && *m_stat3 == DEAD && *m_stat4 == DEAD)
	{
		Zone(arr, m_x1, m_y1);
		Zone(arr, m_x2, m_y2);
		Zone(arr, m_x3, m_y3);
		Zone(arr, m_x4, m_y4);
		return true;
	}
	return false;
}
