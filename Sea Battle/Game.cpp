#include "Game.h"
#include "Constants.h"
#include "Ships.h"

using namespace std;

Game::Game()
{
	m_font.loadFromFile("arial.ttf");
	m_window.create(sf::VideoMode(800, 600), "Sea Battle");
}

void Game::Draw()
{
	{
		sf::RectangleShape boardFrame;
		boardFrame.setOutlineThickness(4);
		boardFrame.setOutlineColor(sf::Color::Black);
		boardFrame.setSize(sf::Vector2f(300, 300));
		boardFrame.setPosition(50, 80);

		m_window.draw(boardFrame);   //my board

		boardFrame.setPosition(450, 80);

		m_window.draw(boardFrame);   //enemyboard
	}

	sf::VertexArray line(sf::Lines, 2);
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;

	for (int i = 1; i < 10; i++)  //my board
	{
		line[0].position = sf::Vector2f(50 + i * 30, 80);
		line[1].position = sf::Vector2f(50 + i * 30, 380);
		m_window.draw(line);

		line[0].position = sf::Vector2f(50, 80 + 30 * i);
		line[1].position = sf::Vector2f(350, 80 + 30 * i);
		m_window.draw(line);
	}
	for (int i = 1; i < 10; i++)  //enemy board
	{
		line[0].position = sf::Vector2f(450 + i * 30, 80);
		line[1].position = sf::Vector2f(450 + i * 30, 380);
		m_window.draw(line);

		line[0].position = sf::Vector2f(450, 80 + 30 * i);
		line[1].position = sf::Vector2f(750, 80 + 30 * i);
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
				status.setPosition(50 + y * 30, (80 + x * 30));
				m_window.draw(status);
			}
			else if (m_first->m_Board[y][x] == MISS)
			{
				status.setFillColor(sf::Color::Color(858585));
				status.setPosition(50 + y * 30, (80 + x * 30) + 2);
				m_window.draw(status);
			}
			else if (m_first->m_Board[y][x] == DEAD)
			{
				status.setFillColor(sf::Color::Red);
				status.setPosition(450 + y * 30, 380 + x * 30);
				m_window.draw(status);
			}

			if (m_second->m_Board[y][x] == DEAD)
			{
				status.setFillColor(sf::Color::Red);
				status.setPosition(450 + y * 30, 380 + x * 30);
				m_window.draw(status);
			}
			if (m_second->m_Board[y][x] == MISS)
			{
				status.setFillColor(sf::Color::Color(858585));
				status.setPosition(450 + y * 30, 80 + x * 30);
				m_window.draw(status);
			}
		}
	}

	m_window.display();
	

	/*system("cls");
	cout << "\t\t\t  Ваше поле" << "\t\t\t\t\t\t" << "\bПоле противника" << endl << endl;
	cout << '\t' << "    A   B   C   D   E   F   G   H   I   J\t\t    A   B   C   D   E   F   G   H   I   J" << endl;
	cout << "\t  #########################################\t\t  #########################################" << endl;
	for (int y = 0; y < ROW; y++)
	{
		cout << "\t" << y << " | ";
		for (int x = 0; x < COL; x++)
		{
			if (m_first->m_Board[y][x] == EMPTY)
				cout << ' ';
			else
				cout << m_first->m_Board[y][x];
			cout << " | ";
		}
		cout << "\t\t";
		cout << y << " | ";
		for (int x = 0; x < COL; x++)
		{
			if (m_second->m_Board[y][x] == EMPTY)
				cout << ' ';
			else
				cout << m_second->m_Board[y][x];
			cout << " | ";
		}
		if (y != 9)
			cout << "\n\t  |---------------------------------------|\t\t  |---------------------------------------|" << endl;
		else
			cout << "\n\t  #########################################\t\t  #########################################" << endl << endl;
	}*/
}

char Yes_or_No()
{
	char let;
	while (true)
	{
		switch (cin >> let; let)
		{
		case 'y': case 'Y':
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return 'y';
		case 'n': case 'N':
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return 'n';
		default:
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
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
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				if (sf::IntRect(s_random.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
				{
					if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
					{
						placedShipsNum = 10;
						m_first->RandomShipsArrangement();
					}
				}
				if (sf::IntRect(s_check.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
				{
					if (placedShipsNum == 10)
						return;
					else
					{

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
			line[0].position = sf::Vector2f(50 + i * 30, 80);
			line[1].position = sf::Vector2f(50 + i * 30, 380);
			m_window.draw(line);

			line[0].position = sf::Vector2f(50, 80 + 30 * i);
			line[1].position = sf::Vector2f(350, 80 + 30 * i);
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
					status.setPosition(50 + y * 30, 80 + x * 30);
					m_window.draw(status);
				}
				else if (m_first->m_Board[y][x] == MISS)
				{
					status.setFillColor(sf::Color::Color(858585));
					status.setPosition(50 + y * 30, 80 + x * 30);
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

	/*
	while (true)
	{
		m_first->RandomShipsArrangement();
		//Draw();
		cout << "Подходит такое расположение кораблей(y/n)? ";
		if (Yes_or_No() == 'y')
		{
			return;
		}
	}*/
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
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
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
	m_first = new Human(ALIVE);
	m_second = new AI(ENEMY_ALIVE);
		
	sf::Texture t_menu;
	t_menu.loadFromFile("images/menu.png");
	sf::Sprite s_menu;
	s_menu.setTexture(t_menu);

	SetDisposition();
	m_second->RandomShipsArrangement();

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					m_window.close();
			}
		}

		m_window.clear(sf::Color::White);
		m_window.draw(s_menu);
		Draw();
	}

	/*if (FirstTurn() == 'F')
	{
		do
		{
			while (true)  //игрок
			{
				cout << "Ваш выстрел: ";
				if (m_first->Shoot(m_second->m_Board))
				{
					m_second->SearchDead();
					Draw(m_window);
					if (m_second->Loss())
					{
						AnnounceWinner(0);
						delete m_first;
						delete m_second;
						m_first = nullptr;
						m_second = nullptr;
						return;
					}
				}
				else
				{
					Draw(m_window);
					break;
				}
			}
			while (true)  //ИИ
			{
				((AI*)m_second)->AI::AIlogic(m_first->m_Board, *this, m_window);
				if (m_first->Loss())
				{
					AnnounceWinner(1);
					delete m_first;
					delete m_second;
					m_first = nullptr;
					m_second = nullptr;
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
				((AI*)m_second)->AI::AIlogic(m_first->m_Board, *this, m_window);
				if (m_first->Loss())
				{
					AnnounceWinner(1);
					delete m_first;
					delete m_second;
					m_first = nullptr;
					m_second = nullptr;
					return;
				}
				else
					break;
			}
			while (true)  //игрок
			{
				cout << "Ваш выстрел: ";
				if (m_first->Shoot(m_second->m_Board))
				{
					m_second->SearchDead();
					Draw(m_window);
					if (m_second->Loss())
					{
						AnnounceWinner(0);
						delete m_first;
						delete m_second;
						m_first = nullptr;
						m_second = nullptr;
						return;
					}
				}
				else
				{
					Draw(m_window);
					break;
				}
			}
		} while (true);
	}*/
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
	if (player == 0)
	{
		cout << "\t\t\t\t\t\t    Вы победили!\n";
	}
	else
	{
		cout << "\t\t\t\t\t\t    Вы проиграли!\n";
	}
}

void Game::Exit()
{
	sf::Text goodbye;
	m_window.clear(sf::Color::White);
	
}
