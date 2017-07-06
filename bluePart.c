#include <Windows.h>
#include <time.h>
#include "bluePart.h"

#define TRIANGLECOLOR RGB(0,162,232)
#define BACKGROUNDCOLOR RGB(153,217,234)

short triangleOffSet;//小三角偏移量(-1,0,1)
UINT triangleWidth;//小三角宽度
UINT wallLength;//墙的长度
UINT triangleX;//小三角的横坐标
UINT wallX;//最右侧墙的位置
UINT wallDistance;//墙间距
BOOL walls[3][3] = { 1,1,1,1,1,1,1,1,1 };
UINT speed;//移动速度

void CreateBlueGame(void) {
	const int width = blueRect.right - blueRect.left;
	const int height = blueRect.bottom - blueRect.top;
	triangleOffSet = 0;
	triangleWidth = width / 20;//取区域宽度的二十分之一
	wallLength = height / 3;//取区域高度的三分之一
	triangleX = width * 5 / 6;//距离区域右边缘六分之一宽度的位置
	wallX = width * 2 / 3;//最右侧墙的横坐标，距离区域右边缘三分之一宽度的位置
	wallDistance = width / 3;//取区域宽度的三分之一
	srand(time(0) + rand());
	//每一层墙有一个缺口
	walls[0][rand() % 3] = FALSE;
	walls[1][rand() % 3] = FALSE;
	walls[2][rand() % 3] = FALSE;
	speed = 1;
	SetTimer(hwnd, BLUE_TIMER_ID, 20, NULL);
}
void OnBlueTimer(void) {
	BOOL hasWall;
	int i,j;
	const int width = blueRect.right - blueRect.left;

	hasWall = walls[0][1 + triangleOffSet];
	wallX += speed;

	if (hasWall && triangleX <= wallX && triangleX + triangleWidth >= wallX) {
		dead = TRUE;
		return;
	}

	if (wallX >= width) {
		wallX = width*2/3+2*speed;
		for (i = 0; i < 2; ++i) {
			for (j = 0; j < 3; ++j) {
				walls[i][j] = walls[i + 1][j];
			}
		}
		for (j = 0; j < 3; ++j) {
			walls[2][j] = TRUE;
		}
		walls[2][rand() % 3] = FALSE;
	}
}
void OnBlueKeyDown(DWORD vk) {
	switch (vk) {
	case VK_UP:
		if (triangleOffSet >= 0) {
			triangleOffSet -= 1;
		}
		break;
	case VK_DOWN:
		if (triangleOffSet <= 0) {
			triangleOffSet += 1;
		}
		break;
	default:
		break;
	}
}
void OnBlueKeyUp(DWORD vk) {
	//NOTHING TO DO
}
void BlueGamePaint(void) {
	HBRUSH backGroundBrush;
	HPEN wallPen,trianglePen;
	POINT poly[2];
	int i, j;
	const int width = blueRect.right - blueRect.left, height = blueRect.bottom - blueRect.top;
	//创造所需画笔画刷
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	wallPen = blackPen(triangleWidth / 4);
	trianglePen = CreatePen(PS_SOLID, 1, TRIANGLECOLOR);
	//绘制背景
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, blueRect.left, blueRect.top, blueRect.right, blueRect.bottom);
	//绘制墙壁
	SelectObject(hdcMem, wallPen);
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			//从右往左第i列，从上往下第j个
			if (walls[i][j]) {
				poly[0].x = poly[1].x = blueRect.left + wallX - i*wallDistance;
				poly[0].y = blueRect.top + j*wallLength;
				poly[1].y = blueRect.top + (j + 1)*wallLength;
				Polyline(hdcMem, poly, 2);
			}
		}
	}
	//绘制小三角
	SelectObject(hdcMem, trianglePen);
	for (j = 0; j < triangleWidth; ++j) {
		poly[0].x = poly[1].x = blueRect.left + triangleX + j;
		poly[0].y = blueRect.top+triangleOffSet*wallLength + height / 2 + j*0.65;
		poly[1].y = blueRect.top+triangleOffSet*wallLength + height / 2 - j*0.65;
		Polyline(hdcMem, poly, 2);
	}
	//回收资源
	DeleteObject(backGroundBrush);
	DeleteObject(wallPen);
	DeleteObject(trianglePen);
}