#pragma once
#include <Windows.h>

#define abs(x) ((x)>0?(x):-(x))
#define pi 3.1415926535
#define MANHATTANDISTANCE(x1,y1,x2,y2) (abs((x1)-(x2))+abs((y1)-(y2)))

typedef enum _TIMER_ID {
	RED_TIMER_ID = 79861, 
	BLUE_TIMER_ID, 
	GREEN_TIMER_ID, 
	YELLOW_TIMER_ID,
	PAINTER_TIMER_ID
}TIMER_ID;
//===========
//全局变量
//===========
HWND hwnd;
HDC hdc, hdcMem;
RECT rect, redRect, blueRect, yellowRect, greenRect;
BOOL dead, pause;

void CreateGame(void);
void OnTimer(TIMER_ID);
void OnKeyDown(DWORD);
void OnKeyUp(DWORD);
void GamePaint(void);
void Resize(void);
void KillAllTimer(void);

HPEN blackPen(int);
HPEN transparentPen(void);