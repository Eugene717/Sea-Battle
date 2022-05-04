#include "Human.h"
#include "Game.h"
#include "Ships.h"

using Point = std::pair<int, int>;

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
					shot.first = (mousePos.x - MIN_S_BOARD_X) / 30; shot.second = (mousePos.y - MIN_Y) / 30;

					sf::Vector2f middleCell(MIN_S_BOARD_X + shot.first * SQUARE_SIDE_SIZE + 15, MIN_Y + shot.second * SQUARE_SIDE_SIZE + 15);

					if (enemy[shot.first][shot.second] == ENEMY_ALIVE)
					{
						game->DrawShot(middleCell, sf::Color::Red);

						enemy[shot.first][shot.second] = DEAD;
						game->Draw();

						return true;
					}
					else if (enemy[shot.first][shot.second] == EMPTY)
					{
						game->DrawShot(middleCell, sf::Color::Color(858585));

						enemy[shot.first][shot.second] = MISS;
						game->Draw();

						return false;
					}
				}
			}
		}
	}
	return false;
}

bool Human::SetDisposition()
{
	Game* game = Game::GetInstance();

	sf::Texture t_random;
	t_random.loadFromFile("images/random.png");
	sf::Sprite s_random;
	s_random.setTexture(t_random);
	s_random.setScale(-1, 1);
	s_random.setPosition(500, 390);

	sf::Texture t_check;
	t_check.loadFromFile("images/check.png");
	sf::Sprite s_check;
	s_check.setTexture(t_check);
	s_check.setPosition(700, 390);

	sf::Texture t_menu;
	t_menu.loadFromFile("images/menu.png");
	sf::Sprite s_menu;
	s_menu.setTexture(t_menu);

	sf::RectangleShape boardFrame;
	boardFrame.setOutlineThickness(4);
	boardFrame.setOutlineColor(sf::Color::Black);
	boardFrame.setSize(sf::Vector2f(300, 300));

	sf::VertexArray line(sf::Lines, 2);
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;

	Point startingPositions[10]
	{
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 5, MIN_Y + SQUARE_SIDE_SIZE * 1),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 4, MIN_Y + SQUARE_SIDE_SIZE * 3),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 8, MIN_Y + SQUARE_SIDE_SIZE * 3),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 3, MIN_Y + SQUARE_SIDE_SIZE * 5),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 6, MIN_Y + SQUARE_SIDE_SIZE * 5),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 9, MIN_Y + SQUARE_SIDE_SIZE * 5),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 2, MIN_Y + SQUARE_SIDE_SIZE * 7),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 4, MIN_Y + SQUARE_SIDE_SIZE * 7),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 6, MIN_Y + SQUARE_SIDE_SIZE * 7),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 8, MIN_Y + SQUARE_SIDE_SIZE * 7)
	};

	for (size_t i = 0; i < 10; i++)
		m_Ships[i]->setPosition(startingPositions[i].first, startingPositions[i].second);

	int placedShipsNum = 0;
	bool isMove = false, menuOpen = false;
	float dX = 0, dY = 0;
	int nShip = -1;
	sf::RectangleShape menu;
	menu.setOutlineColor(sf::Color::Black);
	menu.setOutlineThickness(2);
	menu.setPosition(50, 20);
	menu.setSize(sf::Vector2f(200, 50));
	//sf::Text txt("Return to menu", m_pImpl->m_font);
	//txt.setFillColor(sf::Color::Black);
	//txt.setPosition(57, 27);
	//txt.setCharacterSize(26);

	sf::Vector2f pos;

	while (game->m_window.isOpen())
	{
		pos = game->m_window.mapPixelToCoords(sf::Mouse::getPosition(game->m_window));
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
				if (menuOpen)   //для закрытия меню при нажатии на что-то кроме текста
					menuOpen = false;

				if (sf::IntRect(s_random.getGlobalBounds()).contains(pos.x, pos.y))
				{
					CleardBoard();
					placedShipsNum = 10;
					RandomShipsArrangement();
				}
				if (sf::IntRect(s_check.getGlobalBounds()).contains(pos.x, pos.y))
				{
					if (placedShipsNum == 10)
					{
						CleardBoard();
						game->m_window.clear(sf::Color::White);
						return true;
					}
				}
				if (sf::IntRect(s_menu.getGlobalBounds()).contains(pos.x, pos.y))
					menuOpen = true;
				/*if (sf::IntRect(txt.getGlobalBounds()).contains(pos.x, pos.y))
					return false;*/
			}

			if (game->m_event.type == sf::Event::MouseButtonPressed)
			{
				if (game->m_event.key.code == sf::Mouse::Left)
				{
					if (menuOpen)
						menuOpen = false;
					else
					{
						for (int i = 0; i < 10; i++)
						{
							/*if ([i].m_body.getGlobalBounds().contains(pos.x, pos.y))
							{
								dX = pos.x - shipsBody[i].m_body.getPosition().x;
								dY = pos.y - shipsBody[i].m_body.getPosition().y;
								isMove = true;
								nShip = i;
							}*/
						}
					}
				}
			}
			if (game->m_event.type == sf::Event::MouseButtonReleased)
			{
				if (game->m_event.key.code == sf::Mouse::Left)
				{
					if (isMove)
					{
						//shipsBody[nShip].m_body.setFillColor(sf::Color::Blue);
						sf::Vector2f firstPos, lastPos;
						/*if (shipsBody[nShip].Horiz())
						{
							firstPos.x = shipsBody[nShip].m_body.getPosition().x + 15;
							firstPos.y = shipsBody[nShip].m_body.getPosition().y + 15;
							lastPos.x = shipsBody[nShip].m_body.getPosition().x + shipsBody[nShip].m_body.getSize().x - 15;
							lastPos.y = shipsBody[nShip].m_body.getPosition().y + shipsBody[nShip].m_body.getSize().y - 15;
						}*/
						//else
						{
							/*firstPos.x = shipsBody[nShip].m_body.getPosition().y + 15;
							firstPos.y = shipsBody[nShip].m_body.getPosition().x - 15;
							lastPos.x = shipsBody[nShip].m_body.getPosition().x + shipsBody[nShip].m_body.getSize().y + 15;
							lastPos.y = shipsBody[nShip].m_body.getPosition().y + shipsBody[nShip].m_body.getSize().x - 15;
							sf::Vector2f pos(shipsBody[nShip].m_body.getSize().y, shipsBody[nShip].m_body.getSize().x);
							firstPos.x = shipsBody[nShip].m_body.getPosition().x - 15;
							firstPos.y = shipsBody[nShip].m_body.getPosition().y + 15;
							lastPos.x = shipsBody[nShip].m_body.getPosition().x + pos.x + 15;
							lastPos.y = shipsBody[nShip].m_body.getPosition().y + pos.y - 15;*/
						}

						if (boardFrame.getGlobalBounds().contains(firstPos) && boardFrame.getGlobalBounds().contains(lastPos))
						{

						}
						else
						{
							//shipsBody[nShip].m_body.setPosition(startingPositions[nShip].GetX(), startingPositions[nShip].GetY());
							/*if (!shipsBody[nShip].Horiz())
								shipsBody[nShip].Rotate();*/
						}
						isMove = false;
						nShip = -1;
					}
				}
				if (game->m_event.key.code == sf::Mouse::Right)
				{
					if (isMove)
					{
						//	shipsBody[nShip].Rotate();
					}
				}
			}


		}
		if (isMove)
		{
			//shipsBody[nShip].m_body.setPosition(pos.x - dX, pos.y - dY);
		}

		game->m_window.clear(sf::Color::White);
		game->m_window.draw(s_random);
		game->m_window.draw(s_check);
		game->m_window.draw(s_menu);

		boardFrame.setPosition(450, 80);
		game->m_window.draw(boardFrame);

		boardFrame.setPosition(50, 80);  //my board
		game->m_window.draw(boardFrame);

		sf::RectangleShape status;
		status.setSize(sf::Vector2f(SQUARE_SIDE_SIZE, SQUARE_SIDE_SIZE));

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				if (m_Board[y][x] == ALIVE)
				{
					status.setFillColor(sf::Color::Blue);
					status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
					game->m_window.draw(status);
				}
				else if (m_Board[y][x] == MISS)
				{
					status.setFillColor(sf::Color::Color(858585));
					status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
					game->m_window.draw(status);
				}
			}
		}

		for (int i = 1; i < 10; i++)  //my board
		{
			line[0].position = sf::Vector2f(50 + i * SQUARE_SIDE_SIZE, 80);
			line[1].position = sf::Vector2f(50 + i * SQUARE_SIDE_SIZE, 380);
			game->m_window.draw(line);

			line[0].position = sf::Vector2f(50, 80 + SQUARE_SIDE_SIZE * i);
			line[1].position = sf::Vector2f(350, 80 + SQUARE_SIDE_SIZE * i);
			game->m_window.draw(line);
		}

		/*for (size_t i = 0; i < 10; i++)
		{
			m_window.draw(shipsBody[i].m_body);
		}*/

		if (sf::IntRect(s_random.getGlobalBounds()).contains(pos.x, pos.y))
		{
			s_random.setColor(sf::Color::Black);
			game->m_window.draw(s_random);
		}
		if (sf::IntRect(s_check.getGlobalBounds()).contains(pos.x, pos.y))
		{
			s_check.setColor(sf::Color::Black);
			game->m_window.draw(s_check);
		}
		if (sf::IntRect(s_menu.getGlobalBounds()).contains(pos.x, pos.y))
		{
			s_menu.setColor(sf::Color::Black);
			game->m_window.draw(s_menu);
		}

		if (menuOpen)
		{
			game->m_window.draw(menu);
			//m_window.draw(txt);
		}
		game->m_window.display();
	}
	return false;
}
