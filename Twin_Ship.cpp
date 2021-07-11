#include "Twin_Ship.h"

using namespace std;

Twin_Ship::Twin_Ship()
{
	m_x1 = new short;
	m_y1 = new short;
	m_x2 = new short;
	m_y2 = new short;
}

Twin_Ship::~Twin_Ship()
{
	delete m_x1;
	delete m_y1;
	delete m_x2;
	delete m_y2;
}

void Twin_Ship::RandomlyArrange(char(&arr)[ROW][COL], char player)
{
	bool isFree = false;
	do
	{
		*m_x1 = RD() % 10;
		*m_y1 = RD() % 10;
		if (arr[*m_y1][*m_x1] != MISS && arr[*m_y1][*m_x1] != player)
		{
			switch (int dir(RD() % 4); dir)
			{
			case 0:
				if (*m_y1 != 0)
				{
					*m_y2 = *m_y1 - 1;
					*m_x2 = *m_x1;
					swap(*m_y1, *m_y2);
					isFree = true;
				}
				break;
			case 1:
				if (*m_x1 != 9)
				{
					*m_y2 = *m_y1;
					*m_x2 = *m_x1 + 1;
					swap(*m_x1, *m_x2);
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
				if (arr[*m_y1][*m_x1] != MISS && arr[*m_y2][*m_x2] != MISS)
				{
					m_stat1 = &arr[*m_y1][*m_x1];
					m_stat2 = &arr[*m_y2][*m_x2];
					*m_stat1 = player;
					*m_stat2 = player;
					Zone(arr);
					return;
				}
			}
		}
	} while (true);
}

void Twin_Ship::Zone(char(&arr)[ROW][COL])
{
	if (*m_x1 == *m_x2)  //вертикальный блять
	{
		if (*m_x1 != 9)
		{
			arr[*m_y1][*m_x1 + 1] = MISS;
			arr[*m_y2][*m_x2 + 1] = MISS;
		}
		if (*m_x1 != 0)
		{
			arr[*m_y1][*m_x1 - 1] = MISS;
			arr[*m_y2][*m_x2 - 1] = MISS;
		}

		if (*m_y2 != 9)
		{
			arr[*m_y2 + 1][*m_x2] = MISS;
			if (*m_x2 != 9)
				arr[*m_y2 + 1][*m_x2 + 1] = MISS;
			if (*m_x2 != 0)
				arr[*m_y2 + 1][*m_x2 - 1] = MISS;
		}
		if (*m_y1 != 0)
		{
			arr[*m_y1 - 1][*m_x1] = MISS;
			if (*m_x1 != 9)
				arr[*m_y1 - 1][*m_x1 + 1] = MISS;
			if (*m_x1 != 0)
				arr[*m_y1 - 1][*m_x1 - 1] = MISS;
		}
	}
	if (*m_y1 == *m_y2)   //горизонтальный ебать
	{
		if (*m_y1 != 0)
		{
			arr[*m_y1 - 1][*m_x1] = MISS;
			arr[*m_y2 - 1][*m_x2] = MISS;
		}
		if (*m_y1 != 9)
		{
			arr[*m_y1 + 1][*m_x1] = MISS;
			arr[*m_y2 + 1][*m_x2] = MISS;
		}
		if (*m_x1 != 9)
		{
			arr[*m_y1][*m_x1 + 1] = MISS;
			if (*m_y1 != 9)
				arr[*m_y1 + 1][*m_x1 + 1] = MISS;
			if (*m_y1 != 0)
				arr[*m_y1 - 1][*m_x1 + 1] = MISS;
		}
		if (*m_x2 != 0)
		{
			arr[*m_y2][*m_x2 - 1] = MISS;
			if (*m_y2 != 9)
				arr[*m_y2 + 1][*m_x2 - 1] = MISS;
			if (*m_y2 != 0)
				arr[*m_y2 - 1][*m_x2 - 1] = MISS;
		}
	}
}

bool Twin_Ship::Kill(char(&arr)[ROW][COL])
{
	if (*m_stat1 == DEAD && *m_stat2 == DEAD)
	{
		Zone(arr);
		return true;
	}
	return false;
}
