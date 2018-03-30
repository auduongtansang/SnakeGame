#include <iostream>
#include <conio.h>
#include <vector>
#include <time.h>
#include <Windows.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//---------------------------------------------------------------------------------------------------------------------------------------

//Get console info
CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE curConsole = GetStdHandle(STD_OUTPUT_HANDLE);
BOOL getbufferinfor = GetConsoleScreenBufferInfo(curConsole, &csbi);

//Console size
#define consoleWidth csbi.srWindow.Right + 1
#define consoleHeigth csbi.srWindow.Bottom + 1

//---------------------------------------------------------------------------------------------------------------------------------------

//Snake struct

enum Status { UP, DOWN, LEFT, RIGHT };

struct Snake
{
	int length;
	COORD *node; //coordinates of the snake, 0 is its head
	Status status;
};

Snake snake;
COORD food;

//---------------------------------------------------------------------------------------------------------------------------------------

//Virtual buffer
vector< vector<char> > buffer;

//Set the current console pointer to [row][column]
void Goto(int row, int column)
{
	COORD coord;
	coord.X = row;
	coord.Y = column;
	SetConsoleCursorPosition(curConsole, coord);
}

//Initialize the snake, virtual buffer; turn off console cursor
void Initialize(void)
{
	snake.length = 1;
	snake.node = new COORD{ 1,1 };
	snake.status = RIGHT;

	buffer.resize(consoleWidth);
	for (int x = 0; x < consoleWidth; x++)
	{
		buffer[x].resize(consoleHeigth);
		for (int y = 0; y < consoleHeigth; y++)
		{
			buffer[x][y] = ' ';
		}
	}

	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = 100;
	SetConsoleCursorInfo(curConsole, &cci);
}

void Game(void)
{
	//Set game speed
	int speed = 300;

	//Main game
	while (1)
	{
		//Draw on virtual buffer
		for (int i = 0; i < snake.length; i++)
		{
			buffer[snake.node[i].X][snake.node[i].Y] = (char)(219);
		}
		//buffer[food.X][food.Y] = (char)(254);

		//Put virtual buffer to console
		Goto(0, 0);
		for (int y = 0; y < consoleHeigth; y++)
		{
			for (int x = 0; x < consoleWidth; x++)
			{
				putchar(buffer[x][y]);	//Print
				buffer[x][y] = ' ';		//Reset
			}
		}

		//Get control
		if (_kbhit()) //If there is a key pressed
		{
			int k = _getch();
			if (k == 224) //If key pressed is an arrow key
			{
				k = _getch();
			}

			//Change direction
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

		//Change snake position
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

		//Crash
		bool crash = 0;
		if (snake.node[0].X <= 0 || snake.node[0].X >= consoleWidth - 1 || snake.node[0].Y <= 0 || snake.node[0].Y >= consoleHeigth - 1)
		{
			crash = 1;
		}
		else
		{
			for (int i = 1; i < snake.length; i++)
			{
				if (snake.node[0].X == snake.node[i].X && snake.node[0].Y == snake.node[i].Y)
				{
					crash = 1;
				}
			}
		}
		if (crash)
		{
			_getch();
			break;
		}

		//Eat food
	}
}

int main(void)
{
	Initialize();
	Game();
	return 0;
}