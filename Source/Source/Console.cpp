#include "Console.h"

CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE curConsole = GetStdHandle(STD_OUTPUT_HANDLE);
BOOL getbufferinfor = GetConsoleScreenBufferInfo(curConsole, &csbi);

#define consoleWidth (csbi.srWindow.Right + 1)
#define consoleHeigth (csbi.srWindow.Bottom + 1)

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

	buffer[0][0] = (char)(201);
	buffer[consoleWidth / 2 - 1][0] = (char)(187);
	buffer[0][consoleHeigth - 1] = (char)(200);
	buffer[consoleWidth / 2 - 1][consoleHeigth - 1] = (char)(188);
	for (int y = 1; y < consoleHeigth - 1; y++)
	{
		buffer[0][y] = buffer[consoleWidth / 2 - 1][y] = (char)(186);
	}
	for (int x = 1; x < consoleWidth / 2 - 1; x++)
	{
		buffer[x][0] = buffer[x][consoleHeigth - 1] = (char)(205);
	}
}

void PrintVirtualBuffer(Buffer &buffer)
{
	Goto(0, 0);
	for (int y = 0; y < consoleHeigth; y++)
	{
		for (int x = 0; x < consoleWidth / 2; x++)
		{
			putchar(buffer[x][y]);	//Print
			if (x != 0 && x != consoleWidth / 2 - 1 && y != 0 && y != consoleHeigth - 1)
				buffer[x][y] = ' ';		//Reset
		}
		if (y < consoleHeigth - 1)
			putchar('\n');
	}
}
