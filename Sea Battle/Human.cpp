#include "Human.h"
#include "Point.h"

Human::Human(const char& player) :Player(player)
{ }

bool Human::Shoot(char(&enemy)[ROW][COL], sf::RenderWindow& window)
{
	Point shot;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				if (sf::IntRect(MIN_S_BOARD_X, MIN_Y, SQUARE_SIDE_SIZE * 10, SQUARE_SIDE_SIZE * 10).contains(sf::Mouse::getPosition(window)))
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					shot.SetValues((mousePos.y - MIN_Y) / 30, (mousePos.x - MIN_S_BOARD_X) / 30);

					if (enemy[shot.GetY()][shot.GetX()] == ENEMY_ALIVE)
					{
						enemy[shot.GetY()][shot.GetX()] = DEAD;

						sf::Vector2f middleCell(MIN_S_BOARD_X + shot.GetY() * SQUARE_SIDE_SIZE, MIN_Y + shot.GetX() * SQUARE_SIDE_SIZE);
						DrawShot(window, middleCell, sf::Color::Red);

						return true;
					}
					else if (enemy[shot.GetY()][shot.GetX()] == EMPTY)
					{
						enemy[shot.GetY()][shot.GetX()] = MISS;

						sf::Vector2f middleCell(MIN_S_BOARD_X + shot.GetY() * SQUARE_SIDE_SIZE, MIN_Y + shot.GetX() * SQUARE_SIDE_SIZE);
						DrawShot(window, middleCell, sf::Color::Color(858585));

						return false;
					}
				}
			}
		}
	}
}
