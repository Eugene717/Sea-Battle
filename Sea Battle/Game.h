#pragma once
#ifndef GAME_H
#define GAME_H
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

enum class Sounds { click, select, miss, enemy, sank };

struct GameIMPL;
class Player;
struct GameDataPacket;

class Game
{
	GameIMPL* m_pImpl;
	static Game* m_game;

	Game();
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void SetNameFirstTime();
	char FirstTurn();
	char SearchGame(sf::TcpSocket& socket);
	void SendMyBoard(sf::TcpSocket& socket);
	bool ReceiveEnemyBoard(sf::TcpSocket& socket);
	void ShowRemainingShips(Player* player, const int& board);
	void ShutdownMes(const std::string& name);
	void AnnounceWinner(const int& player);
	void GameEnd();
public:
	sf::RenderWindow m_window;
	sf::Event m_event;
	std::default_random_engine m_gen;

	static Game* GetInstance();
	bool Exit();
	void Draw();
	void DrawShot(const sf::Vector2f& place, const sf::Color& color);
	void DrawShots(const std::vector<sf::Vector2f>& places, const sf::Color& color);
	GameDataPacket* GetPacket();
	sf::Sprite* GetMenuSprite() const;
	void PlaySound(const Sounds& sound) const;
	int Menu();
	void SinglePlayer();
	void OnePCGame();
	void OnlineGame();
	void Settings();
	bool MiniMenu();
};

#endif // !GAME_H