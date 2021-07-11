#include "Human.h"

Human::Human(const char& player) :Player(player)
{ }

bool Human::Shoot(char(&enemy)[ROW][COL])
{
	Point shot;
	do
	{
		std::cin >> shot;
		if (enemy[shot.GetY()][shot.GetX()] == MISS || enemy[shot.GetY()][shot.GetX()] == DEAD)
		{
			std::cout << "Вы уже стреляли в эту ячейку!\n";
		}
		else if (enemy[shot.GetY()][shot.GetX()] == ENEMY_ALIVE)
		{
			enemy[shot.GetY()][shot.GetX()] = DEAD;
			return true;
		}
		else
		{
			enemy[shot.GetY()][shot.GetX()] = MISS;
			return false;
		}
	} while (true);
}
