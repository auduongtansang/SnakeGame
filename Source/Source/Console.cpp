#include "Console.h"

CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE curConsole = GetStdHandle(STD_OUTPUT_HANDLE);
BOOL getbufferinfor = GetConsoleScreenBufferInfo(curConsole, &csbi);

void Goto(int row, int column)
{
	COORD coord;
	coord.X = row;
	coord.Y = column;
	SetConsoleCursorPosition(curConsole, coord);
}

void ChangeConsoleCursorStatus(DWORD dwSize, BOOL bVisible)
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = bVisible;
	cci.dwSize = dwSize;
	SetConsoleCursorInfo(curConsole, &cci);
}

void VirtualBufferInitialize(Buffer &buffer)
{
	buffer.resize(consoleWidth);
	for (int x = 0; x < consoleWidth; x++)
	{
		buffer[x].resize(consoleHeigth);
		for (int y = 0; y < consoleHeigth; y++)
		{
			buffer[x][y] = ' ';
		}
	}
}

void PrintVirtualBuffer(Buffer &buffer)
{
	Goto(0, 0);
	for (int y = 0; y < consoleHeigth; y++)
	{
		for (int x = 0; x < consoleWidth - 1; x++)
		{
			putchar(buffer[x][y]);	//Print
			buffer[x][y] = ' ';		//Reset
		}
		if (y < consoleHeigth - 1)
			putchar('\n');
	}
}
