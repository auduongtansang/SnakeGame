#ifndef _food_h_
#define _food_h_

#include "Console.h"

typedef COORD Food;

bool FoodGenerate(Food &food, Buffer buffer);
void DrawFoodOnBuffer(Food food, Buffer &buffer);

#endif
