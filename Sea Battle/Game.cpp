#include "Game.h"
#include "Constants.h"
#include "Ships.h"
#include "Players.h"
#include <memory>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

Game* Game::m_game = nullptr;
struct Settings
{
	bool Music;
	bool Sound;
	std::string Name;
};

struct GameIMPL
{
	sf::Music m_music;
	std::vector<std::pair<sf::SoundBuffer, sf::Sound>> m_sounds;

	bool m_menuReturn;
	Player* m_first;
	Player* m_second;
	sf::Font m_font;
	Settings m_settings;
	sf::Texture m_t_menu;
	sf::Sprite m_s_menu;
};

Game::Game()
{
	m_pImpl = new GameIMPL();
	std::random_device rd;
	m_gen.seed(rd());

	m_pImpl->m_settings.Sound = true;
	m_pImpl->m_settings.Music = true;
	m_pImpl->m_menuReturn = false;

	m_pImpl->m_font.loadFromFile("resourses/arial.ttf");
	m_window.create(sf::VideoMode(800, 600), "Sea Battle");

	m_pImpl->m_music.setLoop(true);
	m_pImpl->m_music.openFromFile("sounds/menu_music.wav");
	m_pImpl->m_music.setVolume(50);

	m_pImpl->m_t_menu.loadFromFile("images/menu.png");
	m_pImpl->m_s_menu.setTexture(m_pImpl->m_t_menu);

	sf::SoundBuffer buf;

	buf.loadFromFile("sounds/click.wav");
	m_pImpl->m_sounds.push_back(std::make_pair<sf::SoundBuffer, sf::Sound>(sf::SoundBuffer(buf), sf::Sound()));

	buf.loadFromFile("sounds/click_select.wav");
	m_pImpl->m_sounds.push_back(std::make_pair<sf::SoundBuffer, sf::Sound>(sf::SoundBuffer(buf), sf::Sound()));

	buf.loadFromFile("sounds/click_miss_pos.wav");
	m_pImpl->m_sounds.push_back(std::make_pair<sf::SoundBuffer, sf::Sound>(sf::SoundBuffer(buf), sf::Sound()));

	buf.loadFromFile("sounds/click_enemy_pos.wav");
	m_pImpl->m_sounds.push_back(std::make_pair<sf::SoundBuffer, sf::Sound>(sf::SoundBuffer(buf), sf::Sound()));

	buf.loadFromFile("sounds/sank_ship.wav");
	m_pImpl->m_sounds.push_back(std::make_pair<sf::SoundBuffer, sf::Sound>(sf::SoundBuffer(buf), sf::Sound()));

	for (int i = 0; i < m_pImpl->m_sounds.size(); i++)
		m_pImpl->m_sounds[i].second.setBuffer(m_pImpl->m_sounds[i].first);

	std::ifstream fin("resourses/settings.txt");
	if (fin.is_open())
		fin >> m_pImpl->m_settings.Name;

	if (m_pImpl->m_settings.Name == "")
		SetNameFirstTime();

	m_pImpl->m_music.play();
}

Game::~Game()
{		
	delete m_pImpl;
	delete m_game;
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

	m_window.draw(m_pImpl->m_s_menu);

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

		std::vector<sf::RectangleShape> shots;
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

sf::Sprite* Game::GetMenuSprite() const
{
	return &m_pImpl->m_s_menu;
}

void Game::PlaySound(const Sounds& sound) const
{
	if (m_pImpl->m_settings.Sound)
		m_pImpl->m_sounds[(int)sound].second.play();
}

int Game::Menu()
{
	float centerPos = m_window.getSize().x / 2;

	sf::Text header("Sea Battle", m_pImpl->m_font);
	header.setCharacterSize(72);
	header.setStyle(sf::Text::Bold);
	header.setPosition(centerPos - header.getGlobalBounds().width / 2, 0);
	header.setFillColor(sf::Color::Black);

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

	int menuNum = -1;
	bool sound = false;

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

		if (sf::IntRect(singleplayer.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			singleplayer.setFillColor(sf::Color::Blue);			
			menuNum = 1;
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(multiplayer.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			multiplayer.setFillColor(sf::Color::Blue);
			menuNum = 2;
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(LANgame.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			LANgame.setFillColor(sf::Color::Blue);
			menuNum = 3;
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(settings.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			settings.setFillColor(sf::Color::Blue);
			menuNum = 4;
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(exit.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			exit.setFillColor(sf::Color::Blue);
			menuNum = 5;
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else
		{
			menuNum = 0;
			sound = false;
			singleplayer.setFillColor(sf::Color::Black);
			multiplayer.setFillColor(sf::Color::Black);
			LANgame.setFillColor(sf::Color::Black);
			settings.setFillColor(sf::Color::Black);
			exit.setFillColor(sf::Color::Black);
		}

		if (m_event.type == sf::Event::MouseButtonReleased && m_event.key.code == sf::Mouse::Left && menuNum > 0)
		{
			m_window.clear(sf::Color::White);
			PlaySound(Sounds::select);
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

	m_pImpl->m_music.stop();
	m_pImpl->m_music.openFromFile("sounds/game_music.wav");
	if (m_pImpl->m_settings.Music)
		m_pImpl->m_music.play();

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
					sf::sleep(sf::milliseconds(300));
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
				if (!m_window.isOpen())
					return;
				else if (m_pImpl->m_menuReturn)
				{
					GameEnd();
					return;
				}
				while (true)  //ИИ
				{
					sf::sleep(sf::milliseconds(300));
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
					sf::sleep(sf::milliseconds(300));
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
					sf::sleep(sf::milliseconds(300));
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
				if (!m_window.isOpen())
					return;
				else if (m_pImpl->m_menuReturn)
				{
					GameEnd();
					return;
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
	
	m_pImpl->m_music.stop();
	m_pImpl->m_music.openFromFile("sounds/game_music.wav");
	if (m_pImpl->m_settings.Music)
		m_pImpl->m_music.play();

	if (FirstTurn() == 'F')
	{
		do
		{
			while (true)  //игрок
			{
				sf::sleep(sf::milliseconds(300));
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
			if (!m_window.isOpen())
				return;
			else if (m_pImpl->m_menuReturn)
			{
				GameEnd();
				return;
			}
			while (true)  //2 игрок
			{
				sf::sleep(sf::milliseconds(300));
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
			if (!m_window.isOpen())
				return;
			else if (m_pImpl->m_menuReturn)
			{
				GameEnd();
				return;
			}
		} while (true);
	}
	else
	{
		do
		{
			while (true)  //2 игрок
			{
				sf::sleep(sf::milliseconds(300));
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
			if (!m_window.isOpen())
				return;
			else if (m_pImpl->m_menuReturn)
			{
				GameEnd();
				return;
			}
			while (true)  //игрок
			{
				sf::sleep(sf::milliseconds(300));
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
			if (!m_window.isOpen())
				return;
			else if (m_pImpl->m_menuReturn)
			{
				GameEnd();
				return;
			}
		} while (true);
	}
}

void Game::OnlineGame()
{
//	sf::Packet packet;


}

bool Game::SearchGame(sf::TcpSocket& socket)
{
	//sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 - 40);

	//sf::Text loading("   Loading . . .", m_pImpl->m_font);
	//loading.setFillColor(sf::Color::Black);
	//loading.setCharacterSize(30);
	//loading.setStyle(sf::Text::Style::Bold);
	//loading.setPosition(centerPos.x - loading.getGlobalBounds().width / 2, centerPos.y - loading.getGlobalBounds().height);

	//m_window.clear(sf::Color::White);
	//m_window.draw(loading);
	//m_window.display();

	//if (socket.connect("localhost", 55055, sf::seconds(3)) != sf::Socket::Status::Done)   //192.168.0.105 для примера
	//{
	//	loading.setString("       Failed connection\nCheck Ethernet connection");
	//	loading.setCharacterSize(24);
	//	loading.setPosition(centerPos.x - loading.getGlobalBounds().width / 2, centerPos.y - loading.getGlobalBounds().height);

	//	m_window.clear(sf::Color::White);
	//	m_window.draw(loading);
	//	m_window.display();
	//	sf::sleep(sf::seconds(3));

	//	return '\0';
	//}

	//sf::Packet packet;
	//std::string turn, enemyName;

	//socket.setBlocking(false);

	//loading.setString("  Searching . . .");
	//sf::Text back("Back", m_pImpl->m_font);
	//back.setFillColor(sf::Color::Black);
	//back.setCharacterSize(24);
	//back.setPosition(35 - back.getGlobalBounds().width / 2, 475 - back.getGlobalBounds().height);

	//while (m_window.isOpen())
	//{
	//	if (m_window.pollEvent(m_event))
	//	{
	//		if (m_event.type == sf::Event::Closed)
	//			m_window.close();
	//		if (m_event.type == sf::Event::KeyReleased)
	//		{
	//			if (m_event.key.code == sf::Keyboard::Escape)
	//			{
	//				if (DrawMenu())
	//				{
	//					socket.disconnect();
	//					return '\0';
	//				}
	//			}
	//		}
	//		if (m_event.type == sf::Event::MouseButtonReleased && m_event.key.code == sf::Mouse::Left)
	//		{
	//			if (sf::IntRect(back.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
	//			{
	//				m_window.clear(sf::Color::White);
	//				socket.setBlocking(true);
	//				socket.disconnect();
	//				return '\1';
	//			}
	//		}
	//	}

	//	if (socket.receive(packet) == sf::Socket::Done)
	//	{
	//		packet >> turn;
	//		packet.clear();

	//		packet << myName;
	//		socket.send(packet);
	//		packet.clear();

	//		socket.setBlocking(true);

	//		if (socket.receive(packet) == sf::Socket::Done)
	//		{
	//			packet >> enemyName;
	//			packet.clear();
	//		}

	//		if (turn == "f")
	//		{
	//			m_pImpl->m_first = new Human('w');
	//			m_pImpl->m_second = new Human('b');
	//		}
	//		else
	//		{
	//			m_pImpl->m_first = new Human('b');
	//			m_pImpl->m_second = new Human('w');
	//		}

	//		m_pImpl->m_first->SetName(myName);
	//		m_pImpl->m_second->SetName(enemyName);

	//		socket.setBlocking(false);

	//		m_pImpl->m_MP = true;

	//		loading.setString("Start Game");
	//		m_window.clear(sf::Color::White);
	//		m_window.draw(loading);
	//		m_window.display();
	//		sf::sleep(sf::seconds(1));

	//		ShowPlayersNames();
	//		m_dataPacket.m_finishGame = false;

	//		return turn[0];
	//	}

	//	back.setFillColor(sf::Color::Black);
	//	if (sf::IntRect(back.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
	//	{
	//		back.setFillColor(sf::Color::Blue);
	//	}

	//	m_window.clear(sf::Color::White);
	//	m_window.draw(loading);
	//	m_window.draw(back);
	//	m_window.display();
	//}
	return false;
}

void Game::Settings()
{
	m_window.clear(sf::Color::White);
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 - 100);

	sf::Texture t_sound_on;
	t_sound_on.loadFromFile("images/sound_on.png");
	sf::Texture t_sound_off;
	t_sound_off.loadFromFile("images/sound_off.png");

	sf::Texture t_music_on;
	t_music_on.loadFromFile("images/music_on.png");
	sf::Texture t_music_off;
	t_music_off.loadFromFile("images/music_off.png");

	sf::Sprite s_sound;
	sf::Sprite s_music;

	if (m_pImpl->m_settings.Sound)
		s_sound.setTexture(t_sound_on);
	else
		s_sound.setTexture(t_sound_off);

	if (m_pImpl->m_settings.Music)
		s_music.setTexture(t_music_on);
	else
		s_music.setTexture(t_music_off);

	s_sound.setOrigin(24, 24);
	s_music.setOrigin(24, 24);

	s_sound.setPosition(324, 324);
	s_music.setPosition(494, 324);

	sf::Texture t_back;
	t_back.loadFromFile("images/back.png");
	sf::Sprite s_back;
	s_back.setTexture(t_back);
	s_back.setOrigin(24, 24);
	s_back.setPosition(25, 575);

	sf::Texture t_check;
	t_check.loadFromFile("images/check.png");
	sf::Sprite s_check;
	s_check.setTexture(t_check);
	s_check.setOrigin(15, 15);
	s_check.setPosition(m_window.getSize().x / 2 + 175, m_window.getSize().y / 2 - 60);

	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(2);
	shape.setSize(sf::Vector2f(300, 50));
	shape.setOrigin(150, 75);
	shape.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);

	std::string str = m_pImpl->m_settings.Name;
	sf::Text name(m_pImpl->m_settings.Name, m_pImpl->m_font, 28);
	name.setFillColor(sf::Color::Black);
	name.setOrigin(name.getGlobalBounds().width / 2, 10);
	name.setPosition(centerPos.x, centerPos.y + 40);

	sf::RectangleShape input;
	input.setFillColor(sf::Color::Black);
	input.setSize(sf::Vector2f(2, 46));
	input.setOrigin(1, 23);
	input.setPosition(name.getPosition().x + name.getGlobalBounds().width / 2 + 5, name.getPosition().y + 10);

	sf::RectangleShape volumeBar;
	volumeBar.setFillColor(sf::Color::Black);
	volumeBar.setSize(sf::Vector2f(5, 100));
	volumeBar.setOrigin(3, 50);
	volumeBar.setPosition(-100, -100);

	sf::CircleShape volumeCircle;
	volumeCircle.setFillColor(sf::Color::Black);
	volumeCircle.setRadius(10);
	volumeCircle.setOrigin(10, 10);
	volumeCircle.setPosition(-100, 454 - m_pImpl->m_music.getVolume());

	bool isPassEnter = false;
	sf::Clock clock, clock2;
	bool blink = true, barClick = false;
	bool sound = false;

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
			if (m_event.type == sf::Event::MouseButtonReleased && m_event.key.code == sf::Mouse::Left)
			{
				if (barClick)  //set volume
				{
					barClick = false;
					if (m_pImpl->m_music.getVolume() == 0)
						m_pImpl->m_settings.Music = false;
					else
						m_pImpl->m_settings.Music = true;

					PlaySound(Sounds::select);
				}
				if (sf::IntRect(s_check.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //set name
				{
					if (str.size() > 0)
					{
						m_pImpl->m_settings.Name = str;

						std::FILE* file = fopen("resourses/settings.txt", "w");
						fclose(file);

						std::fstream fout("resourses/settings.txt");
						fout << m_pImpl->m_settings.Name;

						PlaySound(Sounds::select);
					}
				}
				if (sf::IntRect(shape.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //cnange name
				{
					PlaySound(Sounds::select);
					isPassEnter = true;
				}
				else if (isPassEnter)  //cancel name set
				{
					PlaySound(Sounds::select);
					name.setString(m_pImpl->m_settings.Name);
					str = m_pImpl->m_settings.Name;
					isPassEnter = false;
					name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
					name.setPosition(centerPos.x, centerPos.y + 40);
					input.setPosition(name.getPosition().x + name.getGlobalBounds().width / 2 + 5, input.getPosition().y);
				}
				if (sf::IntRect(s_back.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //return to main menu
				{
					PlaySound(Sounds::select);
					return;
				}
			}
			if (m_event.type == sf::Event::MouseButtonPressed && m_event.key.code == sf::Mouse::Left)
			{
				if (sf::IntRect(s_sound.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //play sound or not
				{
					if (m_pImpl->m_settings.Sound)
					{
						m_pImpl->m_settings.Sound = false;
						s_sound.setTexture(t_sound_off);
					}
					else
					{
						m_pImpl->m_settings.Sound = true;
						s_sound.setTexture(t_sound_on);
					}
					PlaySound(Sounds::select);
				}
				if (sf::IntRect(s_music.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //play music or not
				{
					if (m_pImpl->m_settings.Music)
					{
						m_pImpl->m_settings.Music = false;
						m_pImpl->m_music.pause();
						s_music.setTexture(t_music_off);
						volumeCircle.setPosition(s_music.getPosition().x, 454);
					}
					else
					{
						m_pImpl->m_settings.Music = true;
						m_pImpl->m_music.play();
						s_music.setTexture(t_music_on);
						volumeCircle.setPosition(s_music.getPosition().x, 454 - m_pImpl->m_music.getVolume());
					}
					PlaySound(Sounds::select);
				}
				if (sf::IntRect(volumeCircle.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window))) //volume settings
				{
					barClick = true;
					PlaySound(Sounds::select);
				}
			}
			if (m_event.type == sf::Event::TextEntered && isPassEnter)
			{
				PlaySound(Sounds::click);
				if (m_event.text.unicode == '\b')
				{
					if (str.size() > 0)
					{
						str.pop_back();
						name.setString(str);
						name.setOrigin(name.getGlobalBounds().width / 2, 10);
						name.setPosition(centerPos.x, centerPos.y + 40);
						if (str.size() == 0)
							input.setPosition(name.getGlobalBounds().left + 10, input.getPosition().y);
						else
							input.setPosition(name.getPosition().x + name.getGlobalBounds().width / 2 + 5, input.getPosition().y);
					}
				}
				else if (m_event.text.unicode < 128)
				{
					if (str.size() < 10)
					{
						str += static_cast<char>(m_event.text.unicode);
						name.setString(str);
						name.setOrigin(name.getGlobalBounds().width / 2, 10);
						name.setPosition(centerPos.x, centerPos.y + 40);
						input.setPosition(name.getPosition().x + name.getGlobalBounds().width / 2 + 5, input.getPosition().y);
					}
				}
			}
		}
		if (barClick)
		{
			if (sf::Mouse::getPosition(m_window).y >= 354 && sf::Mouse::getPosition(m_window).y <= 454)
				volumeCircle.setPosition(volumeBar.getPosition().x, sf::Mouse::getPosition(m_window).y);
			else if (sf::Mouse::getPosition(m_window).y <= 354)
				volumeCircle.setPosition(volumeBar.getPosition().x, 354);
			else if (sf::Mouse::getPosition(m_window).y >= 454)
				volumeCircle.setPosition(volumeBar.getPosition().x, 454);

			m_pImpl->m_music.setVolume(abs(volumeCircle.getPosition().y - 454));
			if (m_pImpl->m_music.getVolume() == 0)
			{
				s_music.setTexture(t_music_off);
			}
			else
			{
				s_music.setTexture(t_music_on);
				if (m_pImpl->m_music.getStatus() == sf::Music::Status::Paused)
					m_pImpl->m_music.play();
			}
		}

		m_window.clear(sf::Color::White);

		s_check.setScale(1, 1);
		s_sound.setScale(1, 1);
		s_back.setScale(1, 1);

		if (sf::IntRect(s_check.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			s_check.setScale(1.10, 1.10);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(s_back.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			s_back.setScale(1.10, 1.10);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(s_sound.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			s_sound.setScale(1.10, 1.10);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if ((sf::IntRect(s_music.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)) || sf::IntRect(volumeBar.getGlobalBounds().left - 25, volumeBar.getGlobalBounds().top - 25,
			volumeBar.getGlobalBounds().width + 50, volumeBar.getGlobalBounds().height + 50).contains(sf::Mouse::getPosition(m_window))) && !barClick)
			{
				s_music.setScale(1.10, 1.10);
				if (!sound)
				{
					PlaySound(Sounds::click);
					sound = true;
				}
				if (!barClick)
				{
					volumeBar.setPosition(s_music.getPosition().x - 5, s_music.getPosition().y + 80);
					volumeCircle.setPosition(volumeBar.getPosition().x, volumeCircle.getPosition().y);
				}
			}
		else if (!barClick)
		{
			s_music.setScale(1, 1);
			volumeBar.setPosition(-100, -100);
			volumeCircle.setPosition(-100, volumeCircle.getPosition().y);
			sound = false;
		}

		m_window.draw(volumeBar);
		m_window.draw(volumeCircle);
		m_window.draw(s_back);
		m_window.draw(s_sound);
		m_window.draw(s_music);
		if (isPassEnter)
		{
			m_window.draw(shape);
			m_window.draw(s_check);
			if (blink)
			{
				if (clock2.getElapsedTime().asSeconds() >= 1)
				{
					blink = false;
					clock2.restart();
					clock.restart();
				}
				m_window.draw(input);
			}
			else if (clock.getElapsedTime().asSeconds() >= 1)
			{
				blink = true;
				clock.restart();
				clock2.restart();
			}
		}
		m_window.draw(name);
		m_window.display();
	}
}

bool Game::MiniMenu()
{
	m_window.clear(sf::Color::White);
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 - 100);

	sf::Texture t_sound_on;
	t_sound_on.loadFromFile("images/sound_on.png");
	sf::Texture t_sound_off;
	t_sound_off.loadFromFile("images/sound_off.png");

	sf::Texture t_music_on;
	t_music_on.loadFromFile("images/music_on.png");
	sf::Texture t_music_off;
	t_music_off.loadFromFile("images/music_off.png");

	sf::Sprite s_sound;
	sf::Sprite s_music;

	if (m_pImpl->m_settings.Sound)
		s_sound.setTexture(t_sound_on);
	else
		s_sound.setTexture(t_sound_off);

	if (m_pImpl->m_settings.Music)
		s_music.setTexture(t_music_on);
	else
		s_music.setTexture(t_music_off);

	s_sound.setOrigin(24, 24);
	s_music.setOrigin(24, 24);

	s_sound.setPosition(324, 324);
	s_music.setPosition(494, 324);

	sf::Text tcontinue("continue", m_pImpl->m_font, 28);
	tcontinue.setFillColor(sf::Color::Black);
	tcontinue.setOrigin(tcontinue.getGlobalBounds().width / 2, 10);
	tcontinue.setPosition(centerPos.x, centerPos.y - 40);

	sf::Text menu("Return to main menu", m_pImpl->m_font, 28);
	menu.setFillColor(sf::Color::Black);
	menu.setOrigin(menu.getGlobalBounds().width / 2, 10);
	menu.setPosition(centerPos.x, centerPos.y);

	sf::Text exit("Exit to desctop", m_pImpl->m_font, 28);
	exit.setFillColor(sf::Color::Black);
	exit.setOrigin(exit.getGlobalBounds().width / 2, 10);
	exit.setPosition(centerPos.x, centerPos.y + 50);	

	sf::RectangleShape volumeBar;
	volumeBar.setFillColor(sf::Color::Black);
	volumeBar.setSize(sf::Vector2f(5, 100));
	volumeBar.setOrigin(3, 50);
	volumeBar.setPosition(-100, -100);

	sf::CircleShape volumeCircle;
	volumeCircle.setFillColor(sf::Color::Black);
	volumeCircle.setRadius(10);
	volumeCircle.setOrigin(10, 10);
	volumeCircle.setPosition(-100, 454 - m_pImpl->m_music.getVolume());

	bool sound = false, barClick = false;;

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
			if (m_event.type == sf::Event::MouseButtonReleased && m_event.key.code == sf::Mouse::Left)
			{		
				if (barClick)  //set volume
				{
					barClick = false;
					if (m_pImpl->m_music.getVolume() == 0)
						m_pImpl->m_settings.Music = false;
					else
						m_pImpl->m_settings.Music = true;

					PlaySound(Sounds::select);
				}
				if (sf::IntRect(tcontinue.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //return to game
				{
					PlaySound(Sounds::select);
					m_window.clear(sf::Color::White);
					return true;;
				}
				if (sf::IntRect(menu.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //return to game
				{
					PlaySound(Sounds::select);
					m_window.clear(sf::Color::White);
					m_pImpl->m_menuReturn = true;
					return false;
				}
				if (sf::IntRect(exit.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //return to game
				{
					PlaySound(Sounds::select);
					sf::sleep(sf::milliseconds(300));
					m_window.clear(sf::Color::White);
					m_window.close();
					return false;
				}
			}
			if (m_event.type == sf::Event::MouseButtonPressed && m_event.key.code == sf::Mouse::Left)
			{
				if (sf::IntRect(s_sound.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //play sound or not
				{
					if (m_pImpl->m_settings.Sound)
					{
						m_pImpl->m_settings.Sound = false;
						s_sound.setTexture(t_sound_off);
					}
					else
					{
						m_pImpl->m_settings.Sound = true;
						s_sound.setTexture(t_sound_on);
					}
					PlaySound(Sounds::select);
				}
				if (sf::IntRect(s_music.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))  //play music or not
				{
					if (m_pImpl->m_settings.Music)
					{
						m_pImpl->m_settings.Music = false;
						m_pImpl->m_music.pause();
						s_music.setTexture(t_music_off);
						volumeCircle.setPosition(s_music.getPosition().x, 454);
					}
					else
					{
						m_pImpl->m_settings.Music = true;
						m_pImpl->m_music.play();
						s_music.setTexture(t_music_on);
						volumeCircle.setPosition(s_music.getPosition().x, 454 - m_pImpl->m_music.getVolume());
					}
					PlaySound(Sounds::select);
				}
				if (sf::IntRect(volumeCircle.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window))) //volume settings
				{
					barClick = true;
					PlaySound(Sounds::select);
				}
			}			
		}
		if (barClick)
		{
			if (sf::Mouse::getPosition(m_window).y >= 354 && sf::Mouse::getPosition(m_window).y <= 454)
				volumeCircle.setPosition(volumeBar.getPosition().x, sf::Mouse::getPosition(m_window).y);
			else if (sf::Mouse::getPosition(m_window).y <= 354)
				volumeCircle.setPosition(volumeBar.getPosition().x, 354);
			else if (sf::Mouse::getPosition(m_window).y >= 454)
				volumeCircle.setPosition(volumeBar.getPosition().x, 454);

			m_pImpl->m_music.setVolume(abs(volumeCircle.getPosition().y - 454));
			if (m_pImpl->m_music.getVolume() == 0)
			{
				s_music.setTexture(t_music_off);
			}
			else
			{
				s_music.setTexture(t_music_on);
				if (m_pImpl->m_music.getStatus() == sf::Music::Status::Paused)
					m_pImpl->m_music.play();
			}
		}

		m_window.clear(sf::Color::White);

		s_sound.setScale(1, 1);
		tcontinue.setFillColor(sf::Color::Black);
		menu.setFillColor(sf::Color::Black);
		exit.setFillColor(sf::Color::Black);

		if (sf::IntRect(tcontinue.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			tcontinue.setScale(1.10, 1.10);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if(sf::IntRect(menu.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			menu.setFillColor(sf::Color::Blue);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if(sf::IntRect(exit.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			exit.setFillColor(sf::Color::Blue);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(s_sound.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			s_sound.setScale(1.10, 1.10);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if ((sf::IntRect(s_music.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)) || sf::IntRect(volumeBar.getGlobalBounds().left - 25, volumeBar.getGlobalBounds().top - 25,
			volumeBar.getGlobalBounds().width + 50, volumeBar.getGlobalBounds().height + 50).contains(sf::Mouse::getPosition(m_window))) && !barClick)
		{
			s_music.setScale(1.10, 1.10);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
			if (!barClick)
			{
				volumeBar.setPosition(s_music.getPosition().x - 5, s_music.getPosition().y + 80);
				volumeCircle.setPosition(volumeBar.getPosition().x, volumeCircle.getPosition().y);
			}
		}
		else if (!barClick)
		{
			s_music.setScale(1, 1);
			volumeBar.setPosition(-100, -100);
			volumeCircle.setPosition(-100, volumeCircle.getPosition().y);
			sound = false;
		}

		m_window.draw(volumeBar);
		m_window.draw(volumeCircle);
		m_window.draw(s_sound);
		m_window.draw(s_music);
		m_window.draw(tcontinue);
		m_window.draw(menu);
		m_window.draw(exit);
		m_window.display();
	}
}

void Game::SetNameFirstTime()
{
	m_window.clear(sf::Color::White);
	sf::Vector2f centerPos = sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2 - 100);

	sf::Text enter("Enter your name", m_pImpl->m_font);
	enter.setFillColor(sf::Color::Black);
	enter.setCharacterSize(30);
	enter.setPosition(centerPos.x - enter.getGlobalBounds().width / 2, centerPos.y - enter.getGlobalBounds().height);

	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(2);
	shape.setSize(sf::Vector2f(300, 50));
	shape.setOrigin(150, 75);
	shape.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);

	sf::Texture t_next;
	t_next.loadFromFile("images/next.png");
	sf::Sprite s_next;
	s_next.setTexture(t_next);
	s_next.setOrigin(15, 15);
	s_next.setPosition(m_window.getSize().x / 2 + 175, m_window.getSize().y / 2 - 50);

	std::string str;
	sf::Text name("", m_pImpl->m_font, 28);
	name.setFillColor(sf::Color::Black);
	name.setPosition(centerPos.x, centerPos.y + 40);

	sf::RectangleShape input;
	input.setFillColor(sf::Color::Black);
	input.setSize(sf::Vector2f(2, 46));
	input.setOrigin(1, 23);
	input.setPosition(name.getPosition().x + name.getGlobalBounds().width / 2 + 5, name.getPosition().y + 10);

	bool isPassEnter = true;
	sf::Clock clock, clock2;
	bool blink = true, sound = false;

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
			if (m_event.type == sf::Event::MouseButtonReleased && m_event.key.code == sf::Mouse::Left)
			{
				if (sf::IntRect(s_next.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
				{
					PlaySound(Sounds::select);
					if (str.size() > 0)
					{
						m_pImpl->m_settings.Name = str;

						std::FILE* file = fopen("resourses/settings.txt", "w");
						fclose(file);

						std::fstream fout("resourses/settings.txt");
						fout << m_pImpl->m_settings.Name;
						return;
					}
				}
				if (sf::IntRect(shape.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
					isPassEnter = true;
				else
					isPassEnter = false;
			}
			if (m_event.type == sf::Event::TextEntered && isPassEnter)
			{
				PlaySound(Sounds::click);
				if (m_event.text.unicode == '\b')
				{
					if (str.size() > 0)
					{
						str.pop_back();
						name.setString(str);
						name.setOrigin(name.getGlobalBounds().width / 2, 10);
						name.setPosition(centerPos.x, centerPos.y + 40);
						if (str.size() == 0)
							input.setPosition(name.getGlobalBounds().left + 10, input.getPosition().y);
						else
							input.setPosition(name.getPosition().x + name.getGlobalBounds().width / 2 + 5, input.getPosition().y);
					}
				}
				else if (m_event.text.unicode < 128)
				{
					if (str.size() < 10)
					{
						str += static_cast<char>(m_event.text.unicode);
						name.setString(str);
						name.setOrigin(name.getGlobalBounds().width / 2, 10);
						name.setPosition(centerPos.x, centerPos.y + 40);
						input.setPosition(name.getPosition().x + name.getGlobalBounds().width / 2 + 5, input.getPosition().y);
					}
				}
			}
		}

		s_next.setScale(1, 1);
		if (sf::IntRect(s_next.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			s_next.setScale(1.10, 1.10);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else
			sound = false;

		m_window.clear(sf::Color::White);
		m_window.draw(enter);
		m_window.draw(shape);
		m_window.draw(name);
		m_window.draw(s_next);
		if (isPassEnter)
		{
			if (blink)
			{
				if (clock2.getElapsedTime().asSeconds() >= 1)
				{
					blink = false;
					clock2.restart();
					clock.restart();
				}
				m_window.draw(input);
			}
			else if (clock.getElapsedTime().asSeconds() >= 1)
			{
				blink = true;
				clock.restart();
				clock2.restart();
			}
		}
		m_window.display();
	}
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

	GameEnd();
}

void Game::GameEnd()
{
	m_pImpl->m_music.stop();
	m_pImpl->m_music.openFromFile("sounds/menu_music.wav");

	m_pImpl->m_music.play();

	m_pImpl->m_menuReturn = false;

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

	bool sound = false;

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
				{
					PlaySound(Sounds::select);
					m_pImpl->m_music.stop();
					sf::sleep(sf::seconds(1));
					return true;
				}
				if (sf::IntRect(no.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
				{
					m_window.clear(sf::Color::White);
					PlaySound(Sounds::select);
					return false;
				}
			}
		}
		 
		yes.setFillColor(sf::Color::Black);
		no.setFillColor(sf::Color::Black);

		if (sf::IntRect(yes.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			yes.setFillColor(sf::Color::Blue);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else if (sf::IntRect(no.getGlobalBounds()).contains(sf::Mouse::getPosition(m_window)))
		{
			no.setFillColor(sf::Color::Blue);
			if (!sound)
			{
				PlaySound(Sounds::click);
				sound = true;
			}
		}
		else
			sound = false;

		m_window.clear(sf::Color::White);
		m_window.draw(exit);
		m_window.draw(yes);
		m_window.draw(no);
		m_window.display();
	}
	return true;
}
