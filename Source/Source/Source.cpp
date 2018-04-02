#include <iostream>
#include <conio.h>
#include "Console.h"
#include "Snake.h"

using namespace std;

Snake snake;
COORD food;

Buffer buffer;

void Initialize(void)
{
	SnakeInitialize(snake);
	VirtualBufferInitialize(buffer);
	ChangeConsoleCursorStatus(100, FALSE);
}

void Game(void)
{
	int speed = 50;

	while (1)
	{
		DrawSnakeOnBuffer(snake, buffer);
		PrintVirtualBuffer(buffer);

		if (_kbhit()) //If there is a key pressed
		{
			int k = _getch();
			if (k == 224) //Arrow key
			{
				k = _getch();
			}
			ChangeSnakeDirection(snake, k);
		}

		ChangeSnakeCroodinates(snake);

		//Sleep(speed);
	}
}

int main(void)
{
	Initialize();
	Game();
	return 0;
}