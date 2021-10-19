#include "Ship.h"

std::vector<sf::Vector2f> Ship::Zone(char(&arr)[ROW][COL], const int* x, const int* y, const bool& draw) const
{
	std::vector<sf::Vector2f> places;
	if (draw)
	{
		places.reserve(sizeof(sf::Vector2f) * 8);
	}

	if (x != nullptr && y != nullptr)
	{
		if (*x != 9)
		{
			if (arr[*y][*x + 1] == EMPTY)
			{
				if (draw)
					places.push_back(sf::Vector2f(*y, *x + 1));
				else
					arr[*y][*x + 1] = MISS;
			}
			if (*y != 9)
				if (arr[*y + 1][*x + 1] == EMPTY)
				{
					if (draw)
						places.push_back(sf::Vector2f(*y + 1, *x + 1));
					else
						arr[*y + 1][*x + 1] = MISS;
				}
			if (*y != 0)
				if (arr[*y - 1][*x + 1] == EMPTY)
				{
					if (draw)
						places.push_back(sf::Vector2f(*y - 1, *x + 1));
					else
						arr[*y - 1][*x + 1] = MISS;
				}
		}
		if (*x != 0)
		{
			if (arr[*y][*x - 1] == EMPTY)
			{
				if (draw)
					places.push_back(sf::Vector2f(*y, *x - 1));
				else
					arr[*y][*x - 1] = MISS;
			}
			if (*y != 9)
				if (arr[*y + 1][*x - 1] == EMPTY)
				{
					if (draw)
						places.push_back(sf::Vector2f(*y + 1, *x - 1));
					else
						arr[*y + 1][*x - 1] = MISS;
				}
			if (*y != 0)
				if (arr[*y - 1][*x - 1] == EMPTY)
				{
					if (draw)
						places.push_back(sf::Vector2f(*y - 1, *x - 1));
					else
						arr[*y - 1][*x - 1] = MISS;
				}
		}
		if (*y != 9)
		{
			if (arr[*y + 1][*x] == EMPTY)
			{
				if (draw)
					places.push_back(sf::Vector2f(*y + 1, *x));
				else
					arr[*y + 1][*x] = MISS;
			}
		}
		if (*y != 0)
		{
			if (arr[*y - 1][*x] == EMPTY)
			{
				if (draw)
					places.push_back(sf::Vector2f(*y - 1, *x));
				else
					arr[*y - 1][*x] = MISS;
			}
		}

	}
	places.shrink_to_fit();

	return places;
}
