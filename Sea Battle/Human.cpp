#include "Human.h"
#include "Game.h"
#include "Ships.h"

using Point = std::pair<int, int>;

Human::Human(const char& player, const int& board_number) :Player(player, board_number)
{ }

bool Human::Shoot(char(&enemy)[ROW][COL])
{
	Game* game = Game::GetInstance();

	int min_board_x;
	if (m_board_number == 1)
		min_board_x = MIN_S_BOARD_X;
	else
		min_board_x = MIN_F_BOARD_X;

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
				if (sf::IntRect(min_board_x, MIN_Y, SQUARE_SIDE_SIZE * 10, SQUARE_SIDE_SIZE * 10).contains(sf::Mouse::getPosition(game->m_window)))
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(game->m_window);
					shot.first = (mousePos.x - min_board_x) / 30; shot.second = (mousePos.y - MIN_Y) / 30;

					sf::Vector2f middleCell(min_board_x + shot.first * SQUARE_SIDE_SIZE + 15, MIN_Y + shot.second * SQUARE_SIDE_SIZE + 15);

					if (enemy[shot.first][shot.second] == ENEMY_ALIVE)
					{
						game->PlaySound(Sounds::enemy);
						game->DrawShot(middleCell, sf::Color::Red);

						enemy[shot.first][shot.second] = DEAD;
						game->Draw();

						return true;
					}
					else if (enemy[shot.first][shot.second] == EMPTY)
					{
						game->PlaySound(Sounds::miss);
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

	sf::Texture t_back;
	t_back.loadFromFile("images/back.png");
	sf::Sprite s_back;
	s_back.setTexture(t_back);
	s_back.setPosition(2, 390);

	sf::RectangleShape boardFrame;
	boardFrame.setOutlineThickness(4);
	boardFrame.setOutlineColor(sf::Color::Black);
	boardFrame.setSize(sf::Vector2f(300, 300));

	sf::VertexArray line(sf::Lines, 2);
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;

	Point startingPositions[10]
	{
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 2.5, MIN_Y + SQUARE_SIDE_SIZE * 1),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 2, MIN_Y + SQUARE_SIDE_SIZE * 3),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 6, MIN_Y + SQUARE_SIDE_SIZE * 3),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 1.5, MIN_Y + SQUARE_SIDE_SIZE * 5),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 4.5, MIN_Y + SQUARE_SIDE_SIZE * 5),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 7.5, MIN_Y + SQUARE_SIDE_SIZE * 5),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 1, MIN_Y + SQUARE_SIDE_SIZE * 7),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 3, MIN_Y + SQUARE_SIDE_SIZE * 7),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 5, MIN_Y + SQUARE_SIDE_SIZE * 7),
		Point(MIN_S_BOARD_X + 300 - SQUARE_SIDE_SIZE * 7, MIN_Y + SQUARE_SIDE_SIZE * 7)
	};

	for (size_t i = 0; i < 10; i++)
	{
		m_Ships[i]->setPosition(startingPositions[i].first, startingPositions[i].second);
		m_Ships[i]->replace();
	}

	bool isMove = false, sound = false;
	int nShip = -1;

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
			if (game->m_event.type == game->m_event.MouseButtonReleased && game->m_event.mouseButton.button == sf::Mouse::Left)  //обработка нажатия
			{
				if (sf::IntRect(s_random.getGlobalBounds()).contains(pos.x, pos.y))  //рандом
				{
					game->PlaySound(Sounds::select);
					CleardBoard();
					RandomShipsArrangement();
				}
				if (sf::IntRect(s_check.getGlobalBounds()).contains(pos.x, pos.y))  //конец расстановки
				{
					bool canStart = true;

					for (int i = 0; i < 10; i++)
						if (!m_Ships[i]->Disposition())
						{
							canStart = false;
							break;
						}

					if (canStart)
					{
						CleardBoard();
						game->m_window.clear(sf::Color::White);
						for (int i = 0; i < 10; i++)
							m_Ships[i]->EndArrange();

						game->PlaySound(Sounds::select);

						return true;
					}
				}
				if (sf::IntRect(s_back.getGlobalBounds()).contains(pos.x, pos.y))  //назад
				{
					game->PlaySound(Sounds::select);
					return false;
				}
			}

			if (game->m_event.type == sf::Event::MouseButtonPressed)  //обработка нажатия по кораблю
			{
				if (game->m_event.key.code == sf::Mouse::Left)
				{
					for (int i = 0; i < 10; i++)
					{
						if (m_Ships[i]->getGlobalBounds().contains(pos.x, pos.y))
						{
							isMove = true;
							nShip = i;
							m_Ships[i]->ClearZone(m_Board);
							game->PlaySound(Sounds::select);
						}
					}
					for (int i = 0; i < 10; i++)
					{
						if (i != nShip)
							m_Ships[i]->DrawZone(m_Board);
					}
				}
			}
			if (game->m_event.type == sf::Event::MouseButtonReleased)
			{
				if (game->m_event.key.code == sf::Mouse::Left)
				{
					if (isMove)
					{
						game->PlaySound(Sounds::select);

						sf::Vector2f firstPos, lastPos;
						if (m_Ships[nShip]->Horiz())
						{
							firstPos.x = m_Ships[nShip]->getGlobalBounds().left + 5;
							lastPos.x = m_Ships[nShip]->getGlobalBounds().left + m_Ships[nShip]->getGlobalBounds().width - 5;
							firstPos.y = m_Ships[nShip]->getGlobalBounds().top + 5;
							lastPos.y = m_Ships[nShip]->getGlobalBounds().top + 25;
						}
						else
						{
							firstPos.x = m_Ships[nShip]->getGlobalBounds().left + 5;
							lastPos.x = m_Ships[nShip]->getGlobalBounds().left + 25;
							firstPos.y = m_Ships[nShip]->getGlobalBounds().top + 5;
							lastPos.y = m_Ships[nShip]->getGlobalBounds().top + m_Ships[nShip]->getGlobalBounds().height - 5;
						}

						if (boardFrame.getGlobalBounds().contains(firstPos) && boardFrame.getGlobalBounds().contains(lastPos))  //внутри доски
						{
							firstPos.x -= 40;  //центр первой палубы
							firstPos.y -= 70;

							int x = firstPos.x / 30, y = firstPos.y / 30;
							m_Ships[nShip]->SetPos(y, x, m_Board, ALIVE);
						}
						else
						{
							m_Ships[nShip]->setPosition(startingPositions[nShip].first, startingPositions[nShip].second);
							m_Ships[nShip]->replace();
							m_Ships[nShip]->Desposited();
							if (!m_Ships[nShip]->Horiz())
								m_Ships[nShip]->Rotate();
						}
						isMove = false;
						nShip = -1;
					}
				}
				if (game->m_event.key.code == sf::Mouse::Right)
				{
					if (isMove)
					{
						m_Ships[nShip]->Rotate();
					}
				}
			}


		}
		if (isMove)
		{
			m_Ships[nShip]->setPosition(pos.x, pos.y);
		}

		game->m_window.clear(sf::Color::White);
		game->m_window.draw(s_random);
		game->m_window.draw(s_check);
		game->m_window.draw(s_back);

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

		for (size_t i = 0; i < 10; i++)
		{
			if (nShip != i)
				game->m_window.draw(*m_Ships[i]);
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

		if (nShip > -1)
			game->m_window.draw(*m_Ships[nShip]);

		if (sf::IntRect(s_random.getGlobalBounds()).contains(pos.x, pos.y))
		{
			s_random.setColor(sf::Color::Black);
			game->m_window.draw(s_random);
			if (!sound)
			{
				game->PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(s_check.getGlobalBounds()).contains(pos.x, pos.y))
		{
			s_check.setColor(sf::Color::Black);
			game->m_window.draw(s_check);
			if (!sound)
			{
				game->PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(s_back.getGlobalBounds()).contains(pos.x, pos.y))
		{
			s_back.setColor(sf::Color::Black);
			game->m_window.draw(s_back);
			if (!sound)
			{
				game->PlaySound(Sounds::click);
				sound = true;
			}
		}
		else
			sound = false;

		game->m_window.display();
	}
	return false;
}
