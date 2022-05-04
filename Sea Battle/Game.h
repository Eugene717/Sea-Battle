#pragma once
#ifndef GAME_H
#define GAME_H
#include <random>
#include <SFML/Graphics.hpp>

struct GameIMPL;
class Player;

class Game
{
	GameIMPL* m_pImpl;
	static Game* m_game;

	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	char FirstTurn();
	void ShowRemainingShips(Player* player, const int& board);
	void AnnounceWinner(const int& player);
public:
	sf::RenderWindow m_window;
	sf::Event m_event;
	std::default_random_engine m_gen;

	static Game* GetInstance();
	bool Exit();
	void Draw();
	void DrawShot(const sf::Vector2f& place, const sf::Color& color);
	void DrawShots(const std::vector<sf::Vector2f>& places, const sf::Color& color);
	int Menu();
	void SinglePlayer();
	void OnlineGame();
	void OnePCGame();
};

#endif // !GAME_H