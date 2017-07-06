#pragma once
#include <Windows.h>
#include "game.h"


void CreateBlueGame(void);
void OnBlueTimer(void);
void OnBlueKeyDown(DWORD);
void OnBlueKeyUp(DWORD);
void BlueGamePaint(void);