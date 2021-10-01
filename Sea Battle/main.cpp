#include "pch.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	Game game;

	

	while (game.m_window.isOpen())
	{
		sf::Event event;
		while (game.m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game.m_window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					game.m_window.close();
			}
		}

		switch (game.Menu())
		{
		case 1:
			game.m_window.clear(sf::Color::White);
			game.SinglePlayer();
			break;
		case 2:
			cout << "Не работает блять, хули клацаешь?\n";
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "Не работает блять, хули клацаешь?\n";
			system("pause");
			system("cls");
			break;
		case 4:
			cout << "Не работает блять, хули клацаешь?\n";
			system("pause");
			system("cls");
			break;
		case 5:
			
			cout << "Goodbye!\n";
			system("pause");
			return 0;
		default:
			break;
		}
	}

	return 0;

	/*do
	{		
		switch (game.Menu(m_window))
		{
		case 1:
			game.SinglePlayer();
			system("pause");
			system("cls");
			break;
		case 2:
			cout << "Не работает блять, хули клацаешь?\n";
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "Не работает блять, хули клацаешь?\n";
			system("pause");
			system("cls");
			break;
		case 4:
			cout << "Не работает блять, хули клацаешь?\n";
			system("pause");
			system("cls");
			break;
		case 5:
			cout << "Goodbye!\n";
			system("pause");
			return 0;
		default:
			break;
		}
	} while (true);*/
}
