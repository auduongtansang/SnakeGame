#include <iostream>
#include <conio.h>
#include <time.h>
#include "Console.h"
#include "Snake.h"
#include "Food.h"

using namespace std;

Snake snake;
Food food;

Buffer buffer;

void Initialize(void)
{
	SnakeInitialize(snake);

	VirtualBufferInitialize(buffer);

	DrawSnakeOnBuffer(snake, buffer); //To genrate first food
	srand((unsigned int)time(NULL));
	FoodGenerate(food, buffer);

	ChangeConsoleCursorStatus(100, FALSE);
}

void Game(void)
{
	int speed = -200;
	bool ate = 0;

	while (1)
	{
		DrawSnakeOnBuffer(snake, buffer);

		if (snake.node[0].X == food.X && snake.node[0].Y == food.Y)
		{
			ate = 1;
			if (FoodGenerate(food, buffer) == false)
			{
				break;
			}
		}
		DrawFoodOnBuffer(food, buffer);

		PrintVirtualBuffer(buffer);

		Sleep(-speed);

		if (_kbhit())
		{
			int k = _getch();
			if (k == 224) //Arrow key
			{
				k = _getch();
			}
			
			ChangeSnakeDirection(snake, k);
		}

		if (ate)
		{
			SnakeExpand(snake);
			ate = 0;
			speed += 1;
			if (speed > 0) 
				speed = 0;
		}
		else
		{
			ChangeSnakeCoodinates(snake);
		}

		if (SnakeCrash(snake))
		{
			break;
		}
	}
}

int main(void)
{
	Initialize();
	Game();
	delete[] snake.node;
	return 0;
}