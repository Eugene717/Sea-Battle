#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <conio.h>
#include <vector>
#include <list>
#include "Players.h"
#include <SFML/Graphics.hpp>

char Yes_or_No();

class Game
{
	Player* m_first;   
	Player* m_second; 
	sf::Font m_font;

	static Game* m_game;

	char FirstTurn();
	void SetDisposition();
	void AnnounceWinner(int player);
	friend class AI;
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
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
	//void LanGame();
	//void OnlineGame();
};

#endif // !GAME_H