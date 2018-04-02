#ifndef _snake_h_
#define _snake_h_

#include "Console.h"

enum Status { UP, DOWN, LEFT, RIGHT };

struct Snake
{
	int length;
	COORD *node;
	Status status;
};

void SnakeInitialize(Snake &snake);
void DrawSnakeOnBuffer(Snake snake, Buffer &buffer);
void ChangeSnakeDirection(Snake &snake, int k);
void ChangeSnakeCoodinates(Snake &snake);
int SnakeCrash(Snake snake);
void SnakeExpand(Snake &snake);

#endif 
