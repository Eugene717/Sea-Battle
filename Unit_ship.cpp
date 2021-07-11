#include "Unit_ship.h"

using namespace std;

Unit_Ship::Unit_Ship()
{
	m_x1 = new short;
	m_y1 = new short;
}

Unit_Ship::~Unit_Ship()
{
	delete m_x1;
	delete m_y1;
}

void Unit_Ship::RandomlyArrange(char(&arr)[ROW][COL], char player)
{
	do
	{
		*m_y1 = RD() % 10;
	    *m_x1 = RD() % 10;
		if (arr[*m_y1][*m_x1] != MISS && arr[*m_y1][*m_x1] != player)
		{
			m_stat1 = &arr[*m_y1][*m_x1];
			*m_stat1 = player;
			Zone(arr);
			return;
		}
	} while (true);
}

void Unit_Ship::Zone(char(&arr)[ROW][COL])
{
	if (*m_x1 != 9)
	{
		arr[*m_y1][*m_x1 + 1] = MISS;
		if (*m_y1 != 9)
			arr[*m_y1 + 1][*m_x1 + 1] = MISS;
		if (*m_y1 != 0)
			arr[*m_y1 - 1][*m_x1 + 1] = MISS;
	}
	if (*m_x1 != 0)
	{
		arr[*m_y1][*m_x1 - 1] = MISS;
		if (*m_y1 != 9)
			arr[*m_y1 + 1][*m_x1 - 1] = MISS;
		if (*m_y1 != 0)
			arr[*m_y1 - 1][*m_x1 - 1] = MISS;
	}
	if (*m_y1 != 9)
	{
		arr[*m_y1 + 1][*m_x1] = MISS;
	}
	if (*m_y1 != 0)
	{
		arr[*m_y1 - 1][*m_x1] = MISS;
	}
}

bool Unit_Ship::Kill(char(&arr)[ROW][COL])
{
	if (*m_stat1 == DEAD)
	{
		Zone(arr);
		return true;
	}
	return false;
}
