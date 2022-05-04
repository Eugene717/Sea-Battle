#include "Ship.h"

Ship::Ship(const int& decksNumber)
{
	m_horiz = true;
	m_body = new sf::RectangleShape;
	m_body->setFillColor(sf::Color::Blue);
	m_body->setSize(sf::Vector2f(30 * decksNumber, 30));
}

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

sf::FloatRect Ship::getGlobalBounds() const
{
	return m_body->getGlobalBounds();
}

void Ship::setPosition(const float& x, const float& y)
{
	m_body->setPosition(x, y);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_body);
}

bool Ship::Horiz()
{
	return m_horiz;
}

void Ship::Rotate()
{
	if (m_horiz)
	{
		m_body->rotate(90);
		m_horiz = false;
	}
	else
	{
		m_body->rotate(-90);
		m_horiz = true;
	}
}