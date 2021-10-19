#include "Human.h"
#include "Point.h"
#include "Game.h"

Human::Human(const char& player, const int& board_number) :Player(player, board_number)
{ }

bool Human::Shoot(char(&enemy)[ROW][COL])
{
	Game* game = Game::GetInstance();

	Point shot;
	while (game->m_window.isOpen())
	{
		while (game->m_window.pollEvent(game->m_event))
		{
			if (game->m_event.type == sf::Event::Closed)
				game->m_window.close();
			if (game->m_event.type == sf::Event::KeyPressed)
			{
				if (game->m_event.key.code == sf::Keyboard::Escape)
					game->m_window.close();
			}
			if (game->m_event.type == game->m_event.MouseButtonReleased && game->m_event.mouseButton.button == sf::Mouse::Left)
			{
				if (sf::IntRect(MIN_S_BOARD_X, MIN_Y, SQUARE_SIDE_SIZE * 10, SQUARE_SIDE_SIZE * 10).contains(sf::Mouse::getPosition(game->m_window)))
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(game->m_window);
					shot.SetValues((mousePos.y - MIN_Y) / 30, (mousePos.x - MIN_S_BOARD_X) / 30);

					sf::Vector2f middleCell(MIN_S_BOARD_X + shot.GetY() * SQUARE_SIDE_SIZE + 15, MIN_Y + shot.GetX() * SQUARE_SIDE_SIZE + 15);

					if (enemy[shot.GetY()][shot.GetX()] == ENEMY_ALIVE)
					{
						game->DrawShot(middleCell, sf::Color::Red);

						enemy[shot.GetY()][shot.GetX()] = DEAD;
						game->Draw();

						return true;
					}
					else if (enemy[shot.GetY()][shot.GetX()] == EMPTY)
					{
						game->DrawShot(middleCell, sf::Color::Color(858585));

						enemy[shot.GetY()][shot.GetX()] = MISS;
						game->Draw();

						return false;
					}
				}
			}
		}
	}
	return false;
}
