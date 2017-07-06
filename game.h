#pragma once
#include <Windows.h>


typedef enum _TIMER_ID { RED_TIMER_ID = 79861, BLUE_TIMER_ID, GREEN_TIMER_ID, YELLOW_TIMER_ID } TIMER_ID;
//===========
//全局变量
//===========
HWND hwnd;
RECT rect, redRect, blueRect, yellowRect, greenRect;

void CreateGame(void);
void OnTimer(TIMER_ID);
void OnKeyDown(DWORD);
void OnKeyUp(DWORD);
void GamePaint(void);
void Resize(void);