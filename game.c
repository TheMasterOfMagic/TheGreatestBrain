#include <Windows.h>
#include "game.h"
#include "redPart.h"
#include "bluePart.h"
#include "yellowPart.h"
#include "greenPart.h"

void CreateGame(void) {
	Resize();
	CreateRedGame();
	CreateBlueGame();
	CreateYellowGame();
	CreateGreenGame();
}
void OnTimer(TIMER_ID timerID) {
	switch (timerID) {
	case RED_TIMER_ID:
		OnRedTimer();
		break;
	case BLUE_TIMER_ID:
		OnBlueTimer();
		break;
	case GREEN_TIMER_ID:
		OnGreenTimer();
		break;
	case YELLOW_TIMER_ID:
		OnYellowTimer();
		break;
	default:
		break;
	}
}
void OnKeyDown(DWORD vk) {
	switch (vk) {
	case VK_LEFT:
	case VK_RIGHT:
		OnRedKeyDown(vk);
		break;
	case VK_UP:
	case VK_DOWN:
		OnBlueKeyDown(vk);
		break;
	case VK_SPACE:
		OnYellowKeyDown(vk);
		break;
	case 'W':
	case 'S':
	case 'A':
	case 'D':
		OnGreenKeyDown(vk);
		break;
	default:
		break;
	}
}
void OnKeyUp(DWORD vk) {
	switch (vk) {
	case VK_LEFT:
	case VK_RIGHT:
		OnRedKeyUp(vk);
		break;
	case VK_UP:
	case VK_DOWN:
		OnBlueKeyUp(vk);
		break;
	case VK_SPACE:
		OnYellowKeyUp(vk);
		break;
	case 'W':
	case 'S':
	case 'A':
	case 'D':
		OnGreenKeyUp(vk);
		break;
	default:
		break;
	}
}
void GamePaint(void) {
	RedGamePaint();
	BlueGamePaint();
	YellowGamePaint();
	GreenGamePaint();
}
void Resize(void) {
	short left, top, right, bottom, midX, midY;
	GetClientRect(hwnd, &rect);

	left = rect.left;
	top = rect.top;
	right = rect.right;
	bottom = rect.bottom;
	midX = (left + right) / 2;
	midY = (top + bottom) / 2;
	//红色部分在左上角
	redRect.left = left;
	redRect.top = top;
	redRect.right = midX;
	redRect.bottom = midY;
	//蓝色部分在右上角
	blueRect.left = midX;
	blueRect.top = top;
	blueRect.right = right;
	blueRect.bottom = midY;
	//黄色部分在左下角
	yellowRect.left = left;
	yellowRect.top = midY;
	yellowRect.right = midX;
	yellowRect.bottom = bottom;
	//绿色部分在右下角
	greenRect.left = midX;
	greenRect.top = midY;
	greenRect.right = right;
	greenRect.bottom = bottom;
}