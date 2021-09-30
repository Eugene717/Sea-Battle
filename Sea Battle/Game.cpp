#include "Game.h"
#include "Constants.h"
#include "Ships.h"

using namespace std;

Game::Game()
{
	m_font.loadFromFile("arial.ttf");
}

void Game::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	
	sf::Text abc("\t\t\tA B C D E F G H I J          A B C D E F G H I J", m_font);
	abc.setFillColor(sf::Color::Black);

	window.draw(abc);

	sf::RectangleShape boardFrame;
	boardFrame.setOutlineThickness(4);
	boardFrame.setOutlineColor(sf::Color::Black);
	boardFrame.setSize(sf::Vector2f(300, 300));
	boardFrame.setPosition(50, 80);

	window.draw(boardFrame);   //my board

	boardFrame.setPosition(450, 80);

	window.draw(boardFrame);   //enemyboard

	sf::VertexArray line(sf::Lines, 2);
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;

	for (int i = 1; i < 10; i++)  //my board
	{
		line[0].position = sf::Vector2f(50 + i * 30, 80);
		line[1].position = sf::Vector2f(50 + i * 30, 380);
		window.draw(line);

		line[0].position = sf::Vector2f(50, 80 + 30 * i);
		line[1].position = sf::Vector2f(350, 80 + 30 * i);
		window.draw(line);
	}
	for (int i = 1; i < 10; i++)  //enemy board
	{
		line[0].position = sf::Vector2f(450 + i * 30, 80);
		line[1].position = sf::Vector2f(450 + i * 30, 380);
		window.draw(line);

		line[0].position = sf::Vector2f(450, 80 + 30 * i);
		line[1].position = sf::Vector2f(750, 80 + 30 * i);
		window.draw(line);
	}

	sf::RectangleShape status;
	status.setSize(sf::Vector2f(25, 25));

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (m_first->m_Board[y][x] == ALIVE)
			{
				status.setFillColor(sf::Color::Blue);
				status.setPosition((50 + y * 30) + 3, (80 + x * 30) + 2);
				window.draw(status);
			}
			else if (m_first->m_Board[y][x] == MISS)
			{
				status.setFillColor(sf::Color::Color(858585));
				status.setPosition((50 + y * 30) + 3, (80 + x * 30) + 2);
				window.draw(status);
			}

			if (m_second->m_Board[y][x] == DEAD)
			{
				status.setFillColor(sf::Color::Red);
				status.setPosition((450 + y * 30) + 3, (380 + x * 30) + 2);
				window.draw(status);
			}
			if (m_second->m_Board[y][x] == MISS)
			{
				status.setFillColor(sf::Color::Color(858585));
				status.setPosition((450 + y * 30) + 3, (80 + x * 30) + 2);
				window.draw(status);
			}
		}
	}

	window.display();
	

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

void Game::AskDisposition()
{
	while (true)
	{
		m_first->RandomShipsArrangement();
		//Draw();
		cout << "Подходит такое расположение кораблей(y/n)? ";
		if (Yes_or_No() == 'y')
		{
			return;
		}
	}
}

int Game::Menu(sf::RenderWindow& window)
{
	float centerPos = window.getSize().x / 2;

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
		}

		menuNum = 0;

		header.setFillColor(sf::Color::Black);
		singleplayer.setFillColor(sf::Color::Black);
		multiplayer.setFillColor(sf::Color::Black);
		LANgame.setFillColor(sf::Color::Black);
		settings.setFillColor(sf::Color::Black);
		exit.setFillColor(sf::Color::Black);

		if (sf::IntRect(singleplayer.getGlobalBounds()).contains(sf::Mouse::getPosition(window)))
		{
			singleplayer.setFillColor(sf::Color::Blue);
			menuNum = 1;
		}
		if (sf::IntRect(multiplayer.getGlobalBounds()).contains(sf::Mouse::getPosition(window)))
		{
			multiplayer.setFillColor(sf::Color::Blue);
			menuNum = 2;
		}
		if (sf::IntRect(LANgame.getGlobalBounds()).contains(sf::Mouse::getPosition(window)))
		{
			LANgame.setFillColor(sf::Color::Blue);
			menuNum = 3;
		}
		if (sf::IntRect(settings.getGlobalBounds()).contains(sf::Mouse::getPosition(window)))
		{
			settings.setFillColor(sf::Color::Blue);
			menuNum = 4;
		}
		if (sf::IntRect(exit.getGlobalBounds()).contains(sf::Mouse::getPosition(window)))
		{
			exit.setFillColor(sf::Color::Blue);
			menuNum = 5;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuNum > 0)
		{
			return menuNum;
		}

		window.clear(sf::Color::White);
		window.draw(header);
		window.draw(singleplayer);
		window.draw(multiplayer);
		window.draw(LANgame);
		window.draw(settings);
		window.draw(exit);
		window.display();
	}
	return -1;
}

void Game::SinglePlayer(sf::RenderWindow& window)
{
	m_first = new Human(ALIVE);
	m_second = new AI(ENEMY_ALIVE);

	m_first->RandomShipsArrangement();

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
		}
		Draw(window);
	}

	AskDisposition();
	m_second->RandomShipsArrangement();
	Draw(window);

	if (FirstTurn() == 'F')
	{
		do
		{
			while (true)  //игрок
			{
				cout << "Ваш выстрел: ";
				if (m_first->Shoot(m_second->m_Board))
				{
					m_second->SearchDead();
					Draw(window);
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
					Draw(window);
					break;
				}
			}
			while (true)  //ИИ
			{
				((AI*)m_second)->AI::AIlogic(m_first->m_Board, *this, window);
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
				((AI*)m_second)->AI::AIlogic(m_first->m_Board, *this, window);
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
					Draw(window);
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
					Draw(window);
					break;
				}
			}
		} while (true);
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
	if (player == 0)
	{
		cout << "\t\t\t\t\t\t    Вы победили!\n";
	}
	else
	{
		cout << "\t\t\t\t\t\t    Вы проиграли!\n";
	}
}
