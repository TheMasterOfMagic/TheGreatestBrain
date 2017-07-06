#pragma once
#include <Windows.h>

typedef enum _bool { false, true }bool;

void CreateGame(HWND);
void OnTimer(HWND, DWORD);
void OnKeyDown(DWORD);
void OnKeyUp(DWORD);
void GamePaint(HWND);