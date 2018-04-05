#include <time.h>
#include <conio.h>
#include "Food.h"

bool FoodGenerate(Food &food, Buffer buffer)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE curConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	BOOL getbufferinfor = GetConsoleScreenBufferInfo(curConsole, &csbi);

	Food *BufferBlank = NULL;
	int nBlank = 0;
	for (int x = 1; x < consoleWidth / 2 - 1; x++)
	{
		for (int y = 1; y < consoleHeigth - 1; y++)
		{
			if (buffer[x][y] == ' ')
			{
				Food *newBufferBlank = new Food[++nBlank];
				for (int i = 0; i < nBlank - 1; i++)
				{
					newBufferBlank[i] = BufferBlank[i];
				}
				newBufferBlank[nBlank - 1].X = x;
				newBufferBlank[nBlank - 1].Y = y;
				BufferBlank = newBufferBlank;
			}
		}
	}
	if (nBlank)
	{
		food = BufferBlank[rand() % nBlank];
	}
	else
	{
		Goto(3 * consoleWidth / 4 - (int)strlen("End game. Press enter to continue...") / 2, consoleHeigth / 2);
		printf("End game. Press enter to continue...");
		while (_getch() != KEY_ENTER);
	}
	return nBlank;
}

void DrawFoodOnBuffer(Food food, Buffer &buffer)
{
	buffer[food.X][food.Y] = '*';
}