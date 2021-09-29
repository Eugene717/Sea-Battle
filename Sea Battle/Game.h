#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <conio.h>
#include "Players.h"
#include <SFML/Graphics.hpp>

char Yes_or_No();

class Game
{
	Player* m_first;   
	Player* m_second; 
	sf::Font m_font;

	char FirstTurn();
	void AskDisposition();
	void AnnounceWinner(int player);
	friend class AI;	
public:
	Game();
	void Draw();
	int Menu(sf::RenderWindow& window);
	void SinglePlayer();
	//void LanGame();
	//void OnlineGame();
};

#endif // !GAME_H