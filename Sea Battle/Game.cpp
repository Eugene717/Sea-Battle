#include "Game.h"
#include "Constants.h"
#include "Ships.h"

using namespace std;

Game* Game::m_game = nullptr;

Game::Game()
{
	m_font.loadFromFile("arial.ttf");
	m_window.create(sf::VideoMode(800, 600), "Sea Battle");
}

Game* Game::GetInstance()
{
	if (m_game == nullptr)
		m_game = new Game();
	return m_game;
}

void Game::Draw()
{
	sf::Texture t_menu;
	t_menu.loadFromFile("images/menu.png");
	sf::Sprite s_menu(t_menu);

	m_window.clear(sf::Color::White);

	m_window.draw(s_menu);

	{
		sf::RectangleShape boardFrame;
		boardFrame.setOutlineThickness(4);
		boardFrame.setOutlineColor(sf::Color::Black);
		boardFrame.setSize(sf::Vector2f(300, 300));
		boardFrame.setPosition(MIN_F_BOARD_X, MIN_Y);

		m_window.draw(boardFrame);   //my board

		boardFrame.setPosition(MIN_S_BOARD_X, MIN_Y);

		m_window.draw(boardFrame);   //enemyboard
	}

	sf::VertexArray line(sf::Lines, 2);
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;

	for (int i = 1; i < 10; i++)  //my board
	{
		line[0].position = sf::Vector2f(50 + i * SQUARE_SIDE_SIZE, 80);
		line[1].position = sf::Vector2f(50 + i * SQUARE_SIDE_SIZE, 380);
		m_window.draw(line);

		line[0].position = sf::Vector2f(50, 80 + SQUARE_SIDE_SIZE * i);
		line[1].position = sf::Vector2f(350, 80 + SQUARE_SIDE_SIZE * i);
		m_window.draw(line);
	}
	for (int i = 1; i < 10; i++)  //enemy board
	{
		line[0].position = sf::Vector2f(450 + i * SQUARE_SIDE_SIZE, 80);
		line[1].position = sf::Vector2f(450 + i * SQUARE_SIDE_SIZE, 380);
		m_window.draw(line);

		line[0].position = sf::Vector2f(450, 80 + SQUARE_SIDE_SIZE * i);
		line[1].position = sf::Vector2f(750, 80 + SQUARE_SIDE_SIZE * i);
		m_window.draw(line);
	}

	sf::RectangleShape status;
	status.setSize(sf::Vector2f(30, 30));

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (m_first->m_Board[y][x] == ALIVE)
			{
				status.setFillColor(sf::Color::Blue);
				status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
			else if (m_first->m_Board[y][x] == MISS)
			{
				status.setFillColor(sf::Color::Color(858585));
				status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
			else if (m_first->m_Board[y][x] == DEAD)
			{
				status.setFillColor(sf::Color::Red);
				status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}

			if (m_second->m_Board[y][x] == DEAD)
			{
				status.setFillColor(sf::Color::Red);
				status.setPosition(450 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
			if (m_second->m_Board[y][x] == MISS)
			{
				status.setFillColor(sf::Color::Color(858585));
				status.setPosition(450 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
		}
	}

	m_window.display();
}

void Game::DrawShot(const sf::Vector2f& place, const sf::Color& color)
{
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
		}

		sf::RectangleShape shot;
		shot.setFillColor(color);
		shot.setPosition(place.x, place.y);

		m_window.clear();
		Draw();

		for (size_t i = 1; i < 30; i++)
		{
			shot.setSize(sf::Vector2f(i + 1, i + 1));
			shot.setOrigin(shot.getSize().x / 2, shot.getSize().y / 2);

			m_window.draw(shot);
			m_window.display();
			sf::sleep(sf::milliseconds(20));
		}
		break;
	}
}

void Game::DrawShots(const std::vector<sf::Vector2f>& places, const sf::Color& color)
{
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
		}

		m_window.clear();
		Draw();

		vector<sf::RectangleShape> shots;
		shots.resize(places.size());

		for (size_t i = 0; i < places.size(); i++)
		{
			shots[i].setFillColor(color);
			shots[i].setPosition(places[i].x, places[i].y);
		}
		for (size_t i = 1; i < 30; i++)
		{
			for (size_t j = 0; j < shots.size(); j++)
			{
				shots[j].setSize(sf::Vector2f(i + 1, i + 1));
				shots[j].setOrigin(shots[j].getSize().x / 2, shots[j].getSize().y / 2);

				m_window.draw(shots[j]);
			}
			m_window.display();
			sf::sleep(sf::milliseconds(20));
		}

		break;
	}
}

void Game::SetDisposition()
{	
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

	/*sf::RectangleShape shipsBody[10];

	shipsBody[0].setSize(sf::Vector2f(30 * 4, 30));
	shipsBody[1].setSize(sf::Vector2f(30 * 3, 30));
	shipsBody[2].setSize(sf::Vector2f(30 * 3, 30));
	shipsBody[3].setSize(sf::Vector2f(30 * 2, 30));
	shipsBody[4].setSize(sf::Vector2f(30 * 2, 30));
	shipsBody[5].setSize(sf::Vector2f(30 * 2, 30));
	shipsBody[6].setSize(sf::Vector2f(30, 30));
	shipsBody[7].setSize(sf::Vector2f(30, 30));
	shipsBody[8].setSize(sf::Vector2f(30, 30));
	shipsBody[9].setSize(sf::Vector2f(30, 30));

	shipsBody[0].setPosition(750 - 30 * 5, 80 + 30 * 1);
	shipsBody[1].setPosition(750 - 30 * 4, 80 + 30 * 3);
	shipsBody[2].setPosition(750 - 30 * 8, 80 + 30 * 3);
	shipsBody[3].setPosition(750 - 30 * 3, 80 + 30 * 5);
	shipsBody[4].setPosition(750 - 30 * 6, 80 + 30 * 5);
	shipsBody[5].setPosition(750 - 30 * 9, 80 + 30 * 5);
	shipsBody[6].setPosition(750 - 30 * 2, 80 + 30 * 7);
	shipsBody[7].setPosition(750 - 30 * 4, 80 + 30 * 7);
	shipsBody[8].setPosition(750 - 30 * 6, 80 + 30 * 7);
	shipsBody[9].setPosition(750 - 30 * 8, 80 + 30 * 7);

	for (auto& i : shipsBody)
	{
		i.setFillColor(sf::Color::Blue);
	}*/

	int placedShipsNum = 0;
	
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
			if (m_event.type == m_event.MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Left)
			{
				if (sf::IntRect(s_random.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
				{
					if (m_event.type == m_event.MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Left)
					{
						placedShipsNum = 10;
						m_first->RandomShipsArrangement();
					}
				}
				if (sf::IntRect(s_check.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
				{
					if (placedShipsNum == 10)
					{
						m_window.clear(sf::Color::White);
						return;
					}
				}
			}
		}

		m_window.clear(sf::Color::White);
		m_window.draw(s_random);
		m_window.draw(s_check);
		m_window.draw(s_menu);

		boardFrame.setPosition(50, 80);
		m_window.draw(boardFrame);   //my board

		boardFrame.setPosition(450, 80);
		m_window.draw(boardFrame);

		for (int i = 1; i < 10; i++)  //my board
		{
			line[0].position = sf::Vector2f(50 + i * SQUARE_SIDE_SIZE, 80);
			line[1].position = sf::Vector2f(50 + i * SQUARE_SIDE_SIZE, 380);
			m_window.draw(line);

			line[0].position = sf::Vector2f(50, 80 + SQUARE_SIDE_SIZE * i);
			line[1].position = sf::Vector2f(350, 80 + SQUARE_SIDE_SIZE * i);
			m_window.draw(line);
		}

		sf::RectangleShape status;
		status.setSize(sf::Vector2f(SQUARE_SIDE_SIZE, SQUARE_SIDE_SIZE));

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				if (m_first->m_Board[y][x] == ALIVE)
				{
					status.setFillColor(sf::Color::Blue);
					status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
					m_window.draw(status);
				}
				else if (m_first->m_Board[y][x] == MISS)
				{
					status.setFillColor(sf::Color::Color(858585));
					status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
					m_window.draw(status);
				}
			}
		}

		if (sf::IntRect(s_random.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			s_random.setColor(sf::Color::Black);
			m_window.draw(s_random);
		}
		if (sf::IntRect(s_check.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			s_check.setColor(sf::Color::Black);
			m_window.draw(s_check);
		}

		m_window.display();
	}
}

int Game::Menu()
{
	float centerPos = m_window.getSize().x / 2;

	sf::Text header("Sea Battle", m_font);
	header.setCharacterSize(72);
	header.setStyle(sf::Text::Bold);
	header.setPosition(centerPos - header.getGlobalBounds().width / 2, 0);

	sf::Text singleplayer("Singlelayer", m_font);
	singleplayer.setPosition(centerPos - singleplayer.getGlobalBounds().width / 2, header.getPosition().y + 150);

	sf::Text multiplayer("Multiplayer", m_font);
	multiplayer.setPosition(centerPos - multiplayer.getGlobalBounds().width / 2, singleplayer.getPosition().y + 70);

	sf::Text LANgame("LAN game", m_font);
	LANgame.setPosition(centerPos - LANgame.getGlobalBounds().width / 2, multiplayer.getPosition().y + 70);

	sf::Text settings("Settings", m_font);
	settings.setPosition(centerPos - settings.getGlobalBounds().width / 2, LANgame.getPosition().y + 70);

	sf::Text exit("Exit", m_font);
	exit.setPosition(centerPos - exit.getGlobalBounds().width / 2, settings.getPosition().y + 70);

	int menuNum;

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
		}

		menuNum = 0;

		header.setFillColor(sf::Color::Black);
		singleplayer.setFillColor(sf::Color::Black);
		multiplayer.setFillColor(sf::Color::Black);
		LANgame.setFillColor(sf::Color::Black);
		settings.setFillColor(sf::Color::Black);
		exit.setFillColor(sf::Color::Black);

		if (sf::IntRect(singleplayer.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			singleplayer.setFillColor(sf::Color::Blue);
			menuNum = 1;
		}
		if (sf::IntRect(multiplayer.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			multiplayer.setFillColor(sf::Color::Blue);
			menuNum = 2;
		}
		if (sf::IntRect(LANgame.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			LANgame.setFillColor(sf::Color::Blue);
			menuNum = 3;
		}
		if (sf::IntRect(settings.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			settings.setFillColor(sf::Color::Blue);
			menuNum = 4;
		}
		if (sf::IntRect(exit.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			exit.setFillColor(sf::Color::Blue);
			menuNum = 5;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuNum > 0)
		{
			m_window.clear(sf::Color::White);
			return menuNum;
		}

		m_window.clear(sf::Color::White);
		m_window.draw(header);
		m_window.draw(singleplayer);
		m_window.draw(multiplayer);
		m_window.draw(LANgame);
		m_window.draw(settings);
		m_window.draw(exit);
		m_window.display();
	}
	return -1;
}

void Game::SinglePlayer()
{
	m_first = new Human(ALIVE, 1);
	m_second = new AI;

	SetDisposition();
	m_second->RandomShipsArrangement();

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
		}

		Draw();

		if (FirstTurn() == 'F')
		{
			do
			{
				while (true)  //игрок
				{
					if (m_first->Shoot(m_second->m_Board))
					{
						m_second->SearchDead();
						Draw();
						if (m_second->Loss())
						{
							AnnounceWinner(0);
							return;
						}
					}
					else
					{
						Draw();
						break;
					}
				}
				while (true)  //ИИ
				{
					m_second->Shoot(m_first->m_Board);
					if (m_first->Loss())
					{
						AnnounceWinner(1);
						return;
					}
					else
						break;
				}
			} while (true);
		}
		else
		{
			do
			{
				while (true)  //ИИ
				{
					m_second->Shoot(m_first->m_Board);
					if (m_first->Loss())
					{
						AnnounceWinner(1);
						return;
					}
					else
						break;
				}
				while (true)  //игрок
				{
					if (m_first->Shoot(m_second->m_Board))
					{
						m_second->SearchDead();
						Draw();
						if (m_second->Loss())
						{
							AnnounceWinner(0);
							return;
						}
					}
					else
					{
						Draw();
						break;
					}
				}
			} while (true);
		}
	}
}

char Game::FirstTurn()
{
	if (RD() % 2 == 0)
		return 'F';
	else
		return 'S';
}

void Game::AnnounceWinner(int player)
{
	delete m_first;
	delete m_second;
	m_first = nullptr;
	m_second = nullptr;

	if (player == 0)
	{
		//cout << "\t\t\t\t\t\t    Вы победили!\n";
		sf::Text announce("YOU WIN!", m_font);
		

		m_window.clear(sf::Color::White);

	}
	else
	{
		//cout << "\t\t\t\t\t\t    Вы проиграли!\n";
		m_window.clear(sf::Color::White);
	}
}

bool Game::Exit()
{
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 - 100);

	sf::Text exit("Are you sure about that?", m_font);
	exit.setFillColor(sf::Color::Black);
	exit.setCharacterSize(30);
	exit.setStyle(sf::Text::Style::Bold);
	exit.setPosition(centerPos.x - exit.getGlobalBounds().width / 2, centerPos.y - exit.getGlobalBounds().height);

	sf::Text yes("Yes", m_font);
	sf::Text no("No", m_font);
	
	yes.setPosition(centerPos.x - yes.getGlobalBounds().width / 2 - 50, centerPos.y - yes.getGlobalBounds().height / 2 + 50);
	no.setPosition(centerPos.x - no.getGlobalBounds().width / 2 + 50, centerPos.y - no.getGlobalBounds().height / 2 + 50);

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
				m_window.close();
			if (m_event.type == sf::Event::KeyPressed)
			{
				if (m_event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
			if (m_event.type == m_event.MouseButtonReleased && m_event.mouseButton.button == sf::Mouse::Left)
			{
				if (sf::IntRect(yes.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
					return true;
				if (sf::IntRect(no.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
				{
					m_window.clear(sf::Color::White);
					return false;
				}
			}
		}
		 
		yes.setFillColor(sf::Color::Black);
		no.setFillColor(sf::Color::Black);

		if (sf::IntRect(yes.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			yes.setFillColor(sf::Color::Blue);
		}
		if (sf::IntRect(no.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			no.setFillColor(sf::Color::Blue);
		}

		m_window.clear(sf::Color::White);
		m_window.draw(exit);
		m_window.draw(yes);
		m_window.draw(no);
		m_window.display();
	}
	return true;
}
