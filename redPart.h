#pragma once
#include <Windows.h>
#include "game.h"


void CreateRedGame(void);
void OnRedTimer(void);
void OnRedKeyDown(DWORD);
void OnRedKeyUp(DWORD);
void RedGamePaint(void);