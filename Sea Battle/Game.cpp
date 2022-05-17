#include "Game.h"
#include "Constants.h"
#include "Ships.h"
#include "Players.h"
#include <memory>

using namespace std;

Game* Game::m_game = nullptr;

struct GameIMPL
{
	Player* m_first;
	Player* m_second;
	sf::Font m_font;
};

Game::Game()
{
	m_pImpl = new GameIMPL();
	std::random_device rd;
	m_gen.seed(rd());

	m_pImpl->m_font.loadFromFile("arial.ttf");
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

	sf::RectangleShape status;
	status.setSize(sf::Vector2f(30, 30));

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (m_pImpl->m_first->m_Board[y][x] == ALIVE)
			{
				status.setFillColor(sf::Color::Blue);
				status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
			else if (m_pImpl->m_first->m_Board[y][x] == MISS)
			{
				status.setFillColor(sf::Color::Color(858585));
				status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
			else if (m_pImpl->m_first->m_Board[y][x] == DEAD)
			{
				status.setFillColor(sf::Color::Red);
				status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
			else if (m_pImpl->m_first->m_Board[y][x] == SURVIVING_SHIP)
			{
				status.setFillColor(sf::Color::Color(sf::Color::Green));
				status.setPosition(50 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}

			if (m_pImpl->m_second->m_Board[y][x] == DEAD)
			{
				status.setFillColor(sf::Color::Red);
				status.setPosition(450 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
			else if (m_pImpl->m_second->m_Board[y][x] == MISS)
			{
				status.setFillColor(sf::Color::Color(858585));
				status.setPosition(450 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
			else if (m_pImpl->m_second->m_Board[y][x] == SURVIVING_SHIP)
			{
				status.setFillColor(sf::Color::Color(sf::Color::Green));
				status.setPosition(450 + y * SQUARE_SIDE_SIZE, 80 + x * SQUARE_SIDE_SIZE);
				m_window.draw(status);
			}
		}
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

		m_window.clear(sf::Color::White);
		Draw();

		for (size_t i = 1; i < 29; i++)
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

		m_window.clear(sf::Color::White);
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

int Game::Menu()
{
	float centerPos = m_window.getSize().x / 2;

	sf::Text header("Sea Battle", m_pImpl->m_font);
	header.setCharacterSize(72);
	header.setStyle(sf::Text::Bold);
	header.setPosition(centerPos - header.getGlobalBounds().width / 2, 0);

	sf::Text singleplayer("Singlelayer", m_pImpl->m_font);
	singleplayer.setPosition(centerPos - singleplayer.getGlobalBounds().width / 2, header.getPosition().y + 150);

	sf::Text multiplayer("One PC", m_pImpl->m_font);
	multiplayer.setPosition(centerPos - multiplayer.getGlobalBounds().width / 2, singleplayer.getPosition().y + 70);

	sf::Text LANgame("Multiplayer", m_pImpl->m_font);
	LANgame.setPosition(centerPos - LANgame.getGlobalBounds().width / 2, multiplayer.getPosition().y + 70);

	sf::Text settings("Settings", m_pImpl->m_font);
	settings.setPosition(centerPos - settings.getGlobalBounds().width / 2, LANgame.getPosition().y + 70);

	sf::Text exit("Exit", m_pImpl->m_font);
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
	m_pImpl->m_first = new Human(ALIVE, 1);
	
	if (!dynamic_cast<Human*>(m_pImpl->m_first)->SetDisposition())
	{
		delete m_pImpl->m_first;
		return;
	}

	m_pImpl->m_second = new AI;
	m_pImpl->m_second->RandomShipsArrangement();
	m_pImpl->m_second->CleardBoard();

	Draw();

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

		if (FirstTurn() == 'F')
		{
			do
			{
				while (true)  //игрок
				{
					if (m_pImpl->m_first->Shoot(m_pImpl->m_second->m_Board))
					{
						m_pImpl->m_second->SearchDead();
						Draw();
						if (m_pImpl->m_second->Loss())
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
					if (m_pImpl->m_second->Shoot(m_pImpl->m_first->m_Board))
					{
						m_pImpl->m_first->SearchDead();
						dynamic_cast<AI*>(m_pImpl->m_second)->SankShip(m_pImpl->m_first->m_Board);

						Draw();
						if (m_pImpl->m_first->Loss())
						{
							AnnounceWinner(1);
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
		else
		{
			do
			{
				while (true)  //ИИ
				{
					if (m_pImpl->m_second->Shoot(m_pImpl->m_first->m_Board))
					{
						m_pImpl->m_first->SearchDead();
						dynamic_cast<AI*>(m_pImpl->m_second)->SankShip(m_pImpl->m_first->m_Board);

						Draw();
						if (m_pImpl->m_first->Loss())
						{
							AnnounceWinner(1);
							return;
						}
					}
					else
					{
						Draw();
						break;
					}
				}
				while (true)  //игрок
				{
					if (m_pImpl->m_first->Shoot(m_pImpl->m_second->m_Board))
					{
						m_pImpl->m_second->SearchDead();
						Draw();
						if (m_pImpl->m_second->Loss())
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

void Game::OnePCGame()
{
	m_pImpl->m_first = new Human(ENEMY_ALIVE, 1);

	if (!dynamic_cast<Human*>(m_pImpl->m_first)->SetDisposition())
	{
		delete m_pImpl->m_first;
		return;
	}

	m_pImpl->m_second = new Human(ENEMY_ALIVE, 2);

	if (!dynamic_cast<Human*>(m_pImpl->m_second)->SetDisposition())
	{
		delete m_pImpl->m_second;
		return;
	}

	Draw();

	if (FirstTurn() == 'F')
	{
		do
		{
			while (true)  //игрок
			{
				if (m_pImpl->m_first->Shoot(m_pImpl->m_second->m_Board))
				{
					m_pImpl->m_second->SearchDead();
					Draw();
					if (m_pImpl->m_second->Loss())
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
			while (true)  //2 игрок
			{
				if (m_pImpl->m_second->Shoot(m_pImpl->m_first->m_Board))
				{
					m_pImpl->m_first->SearchDead();
					Draw();
					if (m_pImpl->m_first->Loss())
					{
						AnnounceWinner(1);
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
	else
	{
		do
		{
			while (true)  //2 игрок
			{
				if (m_pImpl->m_second->Shoot(m_pImpl->m_first->m_Board))
				{
					m_pImpl->m_first->SearchDead();
					Draw();
					if (m_pImpl->m_first->Loss())
					{
						AnnounceWinner(1);
						return;
					}
				}
				else
				{
					Draw();
					break;
				}
			}
			while (true)  //игрок
			{
				if (m_pImpl->m_first->Shoot(m_pImpl->m_second->m_Board))
				{
					m_pImpl->m_second->SearchDead();
					Draw();
					if (m_pImpl->m_second->Loss())
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

void Game::OnlineGame()
{

}

char Game::FirstTurn()
{
	if (m_gen() % 2 == 0)
		return 'F';
	else
		return 'S';
}

void Game::ShowRemainingShips(Player* player, const int& board)
{
	int min_board_x;

	if (board == 0)
		min_board_x = MIN_F_BOARD_X;
	else
		min_board_x = MIN_S_BOARD_X;

	std::vector<sf::Vector2f> places;
	places.reserve(sizeof(sf::Vector2f) * 20);

	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			if (player->m_Board[y][x] == ALIVE || player->m_Board[y][x] == ENEMY_ALIVE)
			{
				places.push_back(sf::Vector2f(y, x));
				(--places.end())->x = min_board_x + y * SQUARE_SIDE_SIZE + 15;
				(--places.end())->y = MIN_Y + x * SQUARE_SIDE_SIZE + 15;
			}
		}
	}
	places.shrink_to_fit();

	m_window.clear(sf::Color::White);
	DrawShots(places, sf::Color::Green);

	for (size_t y = 0; y < ROW; y++)
	{
		for (size_t x = 0; x < COL; x++)
		{
			if (player->m_Board[y][x] == ALIVE || player->m_Board[y][x] == ENEMY_ALIVE)
				player->m_Board[y][x] = SURVIVING_SHIP;
		}
	}

	Draw();
}

void Game::AnnounceWinner(const int& player)
{
	sf::sleep(sf::seconds(1));
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2);

	sf::Text announce("", m_pImpl->m_font);
	announce.setFillColor(sf::Color::Black);
	announce.setCharacterSize(30);
	announce.setStyle(sf::Text::Style::Bold);

	if (player == 0)
	{
		ShowRemainingShips(m_pImpl->m_first, player);
		 
		announce.setString("YOU WIN!");
		announce.setPosition(centerPos.x - announce.getGlobalBounds().width / 2, centerPos.y - announce.getGlobalBounds().height / 2 - 100);
	}
	else
	{
		ShowRemainingShips(m_pImpl->m_second, player);

		announce.setString("YOU LOSE!");
		announce.setPosition(centerPos.x - announce.getGlobalBounds().width / 2, centerPos.y - announce.getGlobalBounds().height / 2 - 100);
	}

	sf::sleep(sf::seconds(2));
	m_window.clear(sf::Color::White);
	m_window.draw(announce);
	m_window.display();
	sf::sleep(sf::seconds(3));

	delete m_pImpl->m_first;
	delete m_pImpl->m_second;
	m_pImpl->m_first = nullptr;
	m_pImpl->m_second = nullptr;
}

bool Game::Exit()
{
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 - 100);

	sf::Text exit("Are you sure about that?", m_pImpl->m_font);
	exit.setFillColor(sf::Color::Black);
	exit.setCharacterSize(30);
	exit.setStyle(sf::Text::Style::Bold);
	exit.setPosition(centerPos.x - exit.getGlobalBounds().width / 2, centerPos.y - exit.getGlobalBounds().height);

	sf::Text yes("Yes", m_pImpl->m_font);
	sf::Text no("No", m_pImpl->m_font);
	
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
