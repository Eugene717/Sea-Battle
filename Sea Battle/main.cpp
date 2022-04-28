#include "pch.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

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

		switch (game->Menu())
		{
		case 1:
			game->m_window.clear(sf::Color::White);
			game->SinglePlayer();
			break;
		case 2:
			//cout << "Не работает блять, хули клацаешь?\n";
			//system("pause");
			//system("cls");
			break;
		case 3:
			//cout << "Не работает блять, хули клацаешь?\n";
			//system("pause");
			//system("cls");
			break;
		case 4:
			//cout << "Не работает блять, хули клацаешь?\n";
			//system("pause");
			//system("cls");
			break;
		case 5:
			if (game->Exit())
				return 0;
		default:
			break;
		}
	}

	return 0;
}
