#include "Ship.h"

void Ship::Zone(char(&arr)[ROW][COL], const int* x, const int* y)
{
	if (x != nullptr && y != nullptr)
	{
		if (*x != 9)
		{
			arr[*y][*x + 1] == EMPTY ? arr[*y][*x + 1] = MISS : NULL;
			if (*y != 9)
				arr[*y + 1][*x + 1] == EMPTY ? arr[*y + 1][*x + 1] = MISS : NULL;
			if (*y != 0)
				arr[*y - 1][*x + 1] == EMPTY ? arr[*y - 1][*x + 1] = MISS : NULL;
		}
		if (*x != 0)
		{
			arr[*y][*x - 1] == EMPTY ? arr[*y][*x - 1] = MISS : NULL;
			if (*y != 9)
				arr[*y + 1][*x - 1] == EMPTY ? arr[*y + 1][*x - 1] = MISS : NULL;
			if (*y != 0)
				arr[*y - 1][*x - 1] == EMPTY ? arr[*y - 1][*x - 1] = MISS : NULL;
		}
		if (*y != 9)
		{
			arr[*y + 1][*x] == EMPTY ? arr[*y + 1][*x] = MISS : NULL;
		}
		if (*y != 0)
		{
			arr[*y - 1][*x] == EMPTY ? arr[*y - 1][*x] = MISS : NULL;
		}
	}
}