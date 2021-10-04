#include "Player.h"
#include "Constants.h"
#include "Point.h"
#include "Game.h"

Player::Player(const char& player) :m_player(player)
{
	m_Ships.push_back(std::make_unique<Quadraple_Ship>());
	m_Ships.push_back(std::make_unique<Triple_Ship>());
	m_Ships.push_back(std::make_unique<Triple_Ship>());
	m_Ships.push_back(std::make_unique<Twin_Ship>());
	m_Ships.push_back(std::make_unique<Twin_Ship>());
	m_Ships.push_back(std::make_unique<Twin_Ship>());
	m_Ships.push_back(std::make_unique<Unit_Ship>());
	m_Ships.push_back(std::make_unique<Unit_Ship>());
	m_Ships.push_back(std::make_unique<Unit_Ship>());
	m_Ships.push_back(std::make_unique<Unit_Ship>());
}

Player::~Player()
{
	m_Ships.clear();
}

bool Player::Loss() const
{
	return m_Ships.empty();
}

void Player::RandomShipsArrangement()
{
	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
			m_Board[y][x] = EMPTY;
	}

	for (size_t i = 0; i < 10; i++)
	{
		(*m_Ships[i]).RandomlyArrange(m_Board, m_player);
	}

	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			if (m_Board[y][x] == MISS)
				m_Board[y][x] = EMPTY;
		}
	}
}

void Player::SearchDead()
{
	for (size_t i = 0; i < m_Ships.size(); i++)
	{
		if ((*m_Ships[i]).Kill(m_Board))
		{
			m_Ships.erase(remove(m_Ships.begin(), m_Ships.end(), m_Ships[i]), m_Ships.end());
			return;
		}
	}
}

void Player::DrawShot(sf::Vector2f place, const sf::Color& color)
{
	Game* game = Game::GetInstance();

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
		}

		sf::RectangleShape shot;
		shot.setFillColor(color);
		shot.setPosition(place.x, place.y);

		game->m_window.clear();
		game->Draw();

		for (size_t i = 1; i < 30; i++)
		{
			shot.setSize(sf::Vector2f(i + 1, i + 1));
			shot.setOrigin(shot.getSize().x / 2, shot.getSize().y / 2);

			game->m_window.draw(shot);
			game->m_window.display();
			sf::sleep(sf::milliseconds(20));
		}
		break;
	}
}
