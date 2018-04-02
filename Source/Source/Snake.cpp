#include "Snake.h"
#include <conio.h>

void SnakeInitialize(Snake &snake)
{
	/*snake.length = 1;
	snake.node = new COORD{ 1,1 };
	snake.status = RIGHT;*/

	snake.length = 5;
	snake.node = new COORD[5];
	snake.node[0] = { 5,1 };
	snake.node[1] = { 4,1 };
	snake.node[2] = { 3,1 };
	snake.node[3] = { 2,1 };
	snake.node[4] = { 1,1 };
	snake.status = RIGHT;
}

void DrawSnakeOnBuffer(Snake snake, Buffer &buffer)
{
	for (int i = 0; i < snake.length; i++)
	{
		buffer[snake.node[i].X][snake.node[i].Y] = (char)(219);
	}
}

void ChangeSnakeDirection(Snake &snake, int k)
{
	if (k == KEY_UP && snake.status != DOWN)
	{
		snake.status = UP;
	}
	else if (k == KEY_DOWN && snake.status != UP)
	{
		snake.status = DOWN;
	}
	else if (k == KEY_LEFT && snake.status != RIGHT)
	{
		snake.status = LEFT;
	}
	else if (k == KEY_RIGHT && snake.status != LEFT)
	{
		snake.status = RIGHT;
	}
}

void ChangeSnakeCroodinates(Snake &snake)
{
	for (int i = snake.length - 1; i > 0; i--)
	{
		snake.node[i] = snake.node[i - 1];
	}

	if (snake.status == UP)
	{
		snake.node[0].Y--;
	}
	else if (snake.status == DOWN)
	{
		snake.node[0].Y++;
	}
	else if (snake.status == LEFT)
	{
		snake.node[0].X--;
	}
	else if (snake.status == RIGHT)
	{
		snake.node[0].X++;
	}
}

int SnakeCrash(Snake snake)
{
	int crash = 0;

	for (int i = 1; i < snake.length; i++)
	{
		if (snake.node[0].X == snake.node[i].X && snake.node[0].Y == snake.node[i].Y)
		{
			crash = 1;
		}
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE curConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	BOOL getbufferinfor = GetConsoleScreenBufferInfo(curConsole, &csbi);

	if (snake.node[0].X <= 0 || snake.node[0].X >= consoleWidth / 2 - 1 ||
		snake.node[0].Y <= 0 || snake.node[0].Y >= consoleHeigth - 1)
	{
		crash = 1;
	}

	if (crash)
	{
		Goto(3 * consoleWidth / 4 - strlen("Game over. Press enter to continue...") / 2, consoleHeigth / 2);
		printf("Game over. Press enter to continue...");
		while (_getch() != 13);
	}

	return crash;
}