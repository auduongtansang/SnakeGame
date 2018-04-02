#ifndef _console_h_
#define _console_h_

#include <Windows.h>
#include <vector>

using namespace std;

#define consoleWidth (csbi.srWindow.Right + 1)
#define consoleHeigth (csbi.srWindow.Bottom + 1)

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

typedef vector< vector<char> > Buffer;

void Goto(int row, int column);
void ChangeConsoleCursorStatus(DWORD dwSize, BOOL bVisible);
void VirtualBufferInitialize(Buffer &buffer);
void PrintVirtualBuffer(Buffer &buffer);

#endif