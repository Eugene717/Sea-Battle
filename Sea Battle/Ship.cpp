#include "Ship.h"

Ship::Ship(const int& decksNumber)
{
	m_horiz = new bool;
	*m_horiz = true;
	m_disposited = new bool;
	*m_disposited = false;
	m_body = new sf::RectangleShape;
	m_posGraphic = new sf::Vector2f;
	m_body->setFillColor(sf::Color::Blue);
	m_body->setSize(sf::Vector2f(30 * decksNumber, 30));
	m_body->setOrigin(m_body->getGlobalBounds().width / 2, m_body->getGlobalBounds().height / 2);
}

std::vector<sf::Vector2f> Ship::Zone(char(&arr)[ROW][COL], const int x, const int y, const bool& draw) const
{
	std::vector<sf::Vector2f> places;
	if (draw)
	{
		places.reserve(sizeof(sf::Vector2f) * 8);
	}

	if (x != 9)
	{
		if (draw)
		{
			if (arr[y][x + 1] != DEAD)
				places.push_back(sf::Vector2f(y, x + 1));
		}
		else if (arr[y][x + 1] == EMPTY)
		{
			arr[y][x + 1] = MISS;
		}

		if (y != 9)
			if (draw)
				places.push_back(sf::Vector2f(y + 1, x + 1));
			else if (arr[y + 1][x + 1] == EMPTY)
				arr[y + 1][x + 1] = MISS;

		if (y != 0)
			if (draw)
				places.push_back(sf::Vector2f(y - 1, x + 1));
			else if (arr[y - 1][x + 1] == EMPTY)
				arr[y - 1][x + 1] = MISS;
	}
	if (x != 0)
	{
		if (draw)
		{
			if (arr[y][x - 1] != DEAD)
				places.push_back(sf::Vector2f(y, x - 1));
		}
		else if (arr[y][x - 1] == EMPTY)
			arr[y][x - 1] = MISS;

		if (y != 9)
			if (draw)
				places.push_back(sf::Vector2f(y + 1, x - 1));
			else if (arr[y + 1][x - 1] == EMPTY)
				arr[y + 1][x - 1] = MISS;

		if (y != 0)
			if (draw)
				places.push_back(sf::Vector2f(y - 1, x - 1));
			else if (arr[y - 1][x - 1] == EMPTY)
				arr[y - 1][x - 1] = MISS;
	}
	if (y != 9)
	{
		if (draw)
		{
			if (arr[y + 1][x] != DEAD)
				places.push_back(sf::Vector2f(y + 1, x));
		}
		else if (arr[y + 1][x] == EMPTY)
			arr[y + 1][x] = MISS;
	}
	if (y != 0)
	{
		if (draw)
		{
			if (arr[y - 1][x] != DEAD)
				places.push_back(sf::Vector2f(y - 1, x));
		}
		else if (arr[y - 1][x] == EMPTY)
			arr[y - 1][x] = MISS;
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

void Ship::replace()
{
	m_posGraphic->x = m_body->getPosition().x;
	m_posGraphic->y = m_body->getPosition().y;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_body);
}

bool Ship::Horiz()
{
	return *m_horiz;
}

void Ship::Desposited()
{
	*m_disposited = false;
}

bool Ship::Disposition()
{
	return *m_disposited;
}

void Ship::Rotate()
{
	if (*m_horiz)
	{
		m_body->rotate(90);
		*m_horiz = false;
	}
	else
	{
		m_body->rotate(-90);
		*m_horiz = true;
	}
}

void Ship::EndArrange()
{
	delete m_body;
	delete m_posGraphic;
	delete m_horiz;
	delete m_disposited;
}
