#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <conio.h>
#include <vector>
#include <list>
#include "Players.h"
#include <SFML/Graphics.hpp>

class Game
{
	Player* m_first;   
	Player* m_second; 
	sf::Font m_font;
	static Game* m_game;

	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	char FirstTurn();
	void DragAndDrop(sf::RectangleShape& shape);
	bool SetDisposition();
	void ShowRemainingShips(Player* player, const int& board);
	void AnnounceWinner(const int& player);
	friend class AI;
public:
	sf::RenderWindow m_window;
	sf::Event m_event;

	static Game* GetInstance();
	bool Exit();
	void Draw();
	void DrawShot(const sf::Vector2f& place, const sf::Color& color);
	void DrawShots(const std::vector<sf::Vector2f>& places, const sf::Color& color);
	int Menu();
	void SinglePlayer();
	void OnlineGame();
	//void LanGame();
};

#endif // !GAME_H