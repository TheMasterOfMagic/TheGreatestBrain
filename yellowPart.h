#pragma once
#include <Windows.h>
#include "game.h"


void CreateYellowGame(void);
void OnYellowTimer(void);
void OnYellowKeyDown(DWORD);
void OnYellowKeyUp(DWORD);
void YellowGamePaint(void);