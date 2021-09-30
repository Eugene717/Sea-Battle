#include "pch.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	Game game;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Sea Battle");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		switch (game.Menu(window))
		{
		case 1:
			window.clear(sf::Color::White);
			game.SinglePlayer(window);
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
		switch (game.Menu(window))
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
