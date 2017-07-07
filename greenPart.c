#include <Windows.h>
#include <math.h>
#include "greenPart.h"

#define RECTANGLECOLOR RGB(34,177,76)
#define BACKGROUNDCOLOR RGB(145,234,171)
#define ENEMYBRUSH RGB(0,0,0)

#define GREENN 3

POINT rectanglePosition;//小正方形的位置
UINT rectangleSize;//小正方形边长
UINT rectangleSpeed;//小正方形移动速度
UINT enemySize;//敌人的大小
float enemySpeed;//敌人的移动速度
POINT enemyPosition[GREENN];//每个敌人的位置
POINT enemyDirection[GREENN];//每个敌人的方向

//按键是否被按下
BOOL wPress;
BOOL sPress;
BOOL aPress;
BOOL dPress;

void CreateGreenGame(void) {
	const int width = greenRect.right - greenRect.left;
	const int height = greenRect.bottom - greenRect.top;
	int i;
	rectanglePosition.x = width / 2;
	rectanglePosition.y = height / 2;
	rectangleSize = width / 20;
	rectangleSpeed = rectangleSize/4;
	enemySize = rectangleSize;
	enemySpeed = rectangleSpeed/5 ;
	for (i = 0; i < GREENN; ++i) {
		do {
			enemyPosition[i].x = rand() % width;
			enemyPosition[i].y = rand() % height;
		} while (MANHATTANDISTANCE(enemyPosition[i].x,enemyPosition[i].y,rectanglePosition.x,rectanglePosition.y) < rectangleSpeed*20);
		enemyDirection[i].x = rand() & 1 ? 1 : -1;
		enemyDirection[i].y = rand() & 1 ? 1 : -1;
	}

	SetTimer(hwnd, GREEN_TIMER_ID, 20, NULL);
}
void OnGreenTimer(void) {
	int i;
	const int width = greenRect.right - greenRect.left, height = greenRect.bottom - greenRect.top;

	if (pause) {
		return;
	}
	//判定是否相撞
	for (i = 0; i < GREENN; ++i) {
		if (abs(enemyPosition[i].x - rectanglePosition.x) < (enemySize + rectangleSize) / 2-2 &&
			abs(enemyPosition[i].y - rectanglePosition.y) < (enemySize + rectangleSize) / 2-2) {
			dead = TRUE;
			return;
		}
	}
	//移动小正方形
	if (wPress && rectanglePosition.y > rectangleSize / 2) {
		rectanglePosition.y -= rectangleSpeed;
	}
	if (sPress && rectanglePosition.y < height - rectangleSize / 2) {
		rectanglePosition.y += rectangleSpeed;
	}
	if (aPress && rectanglePosition.x > rectangleSize / 2) {
		rectanglePosition.x -= rectangleSpeed;
	}
	if (dPress && rectanglePosition.x < width - rectangleSize / 2) {
		rectanglePosition.x += rectangleSpeed;
	}

	//移动敌人
	for (i = 0; i < GREENN; ++i) {
		enemyPosition[i].x += enemyDirection[i].x*enemySpeed;
		if (enemyPosition[i].x >= width - enemySize / 2) {
			enemyDirection[i].x = -1;
		}
		else if (enemyPosition[i].x <= enemySize / 2) {
			enemyDirection[i].x = 1;
		}
		enemyPosition[i].y += enemyDirection[i].y*enemySpeed;
		if (enemyPosition[i].y >= height - enemySize / 2) {
			enemyDirection[i].y = -1;
		}
		else if (enemyPosition[i].y <= enemySize / 2) {
			enemyDirection[i].y = 1;
		}
	}

}
void OnGreenKeyDown(DWORD vk) {
	switch (vk) {
	case 'W':
		wPress = TRUE;
		break;
	case 'S':
		sPress = TRUE;
		break;
	case 'A':
		aPress = TRUE;
		break;
	case 'D':
		dPress = TRUE;
		break;
	default:
		break;
	}
}
void OnGreenKeyUp(DWORD vk) {
	switch (vk) {
	case 'W':
		wPress = FALSE;
		break;
	case 'S':
		sPress = FALSE;
		break;
	case 'A':
		aPress = FALSE;
		break;
	case 'D':
		dPress = FALSE;
		break;
	default:
		break;
	}
}
void GreenGamePaint(void) {
	HBRUSH backGroundBrush, rectangleBrush,enemyBrush;
	int i;
	//创造所需画笔画刷
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	rectangleBrush = CreateSolidBrush(RECTANGLECOLOR);
	enemyBrush = CreateSolidBrush(ENEMYBRUSH);
	//绘制背景
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, greenRect.left, greenRect.top, greenRect.right, greenRect.bottom);
	//绘制敌人
	SelectObject(hdcMem, enemyBrush);
	for (i = 0; i < GREENN; ++i) {
		Rectangle(
			hdcMem,
			greenRect.left + enemyPosition[i].x - enemySize / 2,
			greenRect.top + enemyPosition[i].y - enemySize / 2,
			greenRect.left + enemyPosition[i].x + enemySize / 2,
			greenRect.top + enemyPosition[i].y + enemySize / 2
		);
	}
	//绘制小正方形
	SelectObject(hdcMem, rectangleBrush);
	Rectangle(
		hdcMem,
		greenRect.left + rectanglePosition.x - rectangleSize / 2,
		greenRect.top + rectanglePosition.y - rectangleSize / 2,
		greenRect.left + rectanglePosition.x + rectangleSize / 2,
		greenRect.top + rectanglePosition.y + rectangleSize / 2
	);
	//回收资源
	DeleteObject(backGroundBrush);
	DeleteObject(rectangleBrush);
	DeleteObject(enemyBrush);
}