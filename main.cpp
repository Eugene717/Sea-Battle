/*23.10.2020 доделал наконец морской бой, делал две недели, так как Дима постоянно отсутствовал, а потом сказал делать самому*/
/*05.04.2021 переделал почти полностью программу*/
#include "pch.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	Game game;

	do
	{		
		switch (game.Menu())
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
	} while (true);
}
