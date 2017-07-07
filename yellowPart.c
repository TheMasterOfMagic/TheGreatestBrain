#include <Windows.h>
#include "yellowPart.h"


#define DIAMONDCOLOR (broken ?  RGB(150,150,150) : RGB(255,255-temperature,0))
#define BACKGROUNDCOLOR RGB(255,255,180)

#define N 4//同一时间障碍个数

int temperature;
int barrierDistance;//障碍物之间的间隔距离
int barrierX;//最左侧障碍的横坐标
int barrierLength;//障碍的长度
int barrierY[N];//每个障碍上端点的纵坐标
UINT barrierDirection[N];//每个障碍的纵方向速度
UINT speed;//速度
BOOL spacePress;
int diamondX;//小菱形最右端的横坐标
int diamondY;//小菱形纵坐标
int diamondWidth;//小菱形宽度
BOOL broken;

void CreateYellowGame(void) {
	const int width = yellowRect.right - yellowRect.left;
	const int height = yellowRect.bottom - yellowRect.top;
	int i;

	temperature = 0;
	barrierDistance = width / N;//取距离区域左边缘N分之一宽度的位置
	barrierX = barrierDistance;
	barrierLength = height / 4;//取区域高度的四分之一
	for (i = 0; i < N; ++i) {
		barrierY[i] = rand() % (height - barrierLength);
		barrierDirection[i] = rand() & 1 ? 1 : -1;
	}
	speed = 1;
	spacePress = FALSE;
	diamondX = width / 6;//取距离区域左边缘六分之一宽度的位置
	diamondY = height / 2;//取区域中间的高度
	diamondWidth = width / 20;//取区域宽度的二十分之一
	broken = FALSE;
	SetTimer(hwnd, YELLOW_TIMER_ID, 20, NULL);
}
void OnYellowTimer(void) {
	int i;
	const int height = yellowRect.bottom - yellowRect.top;

	if (pause) {
		return;
	}
	//障碍物移动
	barrierX -= speed;
	if (barrierX <= 0) {
		barrierX = barrierDistance;
		for (i = 0; i < N - 1; ++i) {
			barrierY[i] = barrierY[i + 1];
			barrierDirection[i] = barrierDirection[i + 1];
		}
		barrierY[N - 1] = rand() % (height - barrierLength);
		barrierDirection[N - 1] = rand() & 1 ? 1 : -1;
	}
	for (i = 0; i < N; ++i) {
		barrierY[i] += barrierDirection[i] * speed;
		if (barrierY[i] <= 0 || barrierY[i]>=height-barrierLength) {
			barrierDirection[i] *= -1;
		}
	}
	//判断是否在无敌状态
	if (!broken && spacePress) {
		temperature += 1;
		if (temperature >= 250) {
			broken = TRUE;
		}
	}
	else {
		if (!broken && temperature > 0) {
			temperature -= 1;
		}
		//判定是否死亡
		for (i = 0; i < N; ++i) {
			if (barrierX+i*barrierDistance + diamondWidth >= diamondX && diamondX >= barrierX+i*barrierDistance) {
				if (MANHATTANDISTANCE(diamondX - diamondWidth / 2, diamondY, barrierX + i*barrierDistance, barrierY[i] + barrierLength / 2) <= diamondWidth / 2 + barrierLength / 2) {
					dead = TRUE;
					return;
				}
			}
		}
	}
}
void OnYellowKeyDown(DWORD vk) {
	switch (vk) {
	case VK_SPACE:
		spacePress = TRUE;
		break;
	default:
		break;
	}
}
void OnYellowKeyUp(DWORD vk) {
	switch (vk) {
	case VK_SPACE:
		spacePress = FALSE;
		break;
	default:
		break;
	}
}
void YellowGamePaint(void) {
	HBRUSH backGroundBrush;
	HPEN barrierPen,diamondPen;
	POINT poly[2];
	int i;
	//创造所需画笔画刷
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	barrierPen = CreatePen(PS_SOLID,diamondWidth / 4,(spacePress && !broken ? RGB(255,255,255):RGB(0,0,0)));
	diamondPen = CreatePen(PS_SOLID, 1, DIAMONDCOLOR);
	//绘制背景
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, yellowRect.left, yellowRect.top, yellowRect.right, yellowRect.bottom);
	//绘制障碍
	SelectObject(hdcMem, barrierPen);
	for (i = 0; i < N; ++i) {
		poly[0].x = poly[1].x = yellowRect.left+barrierX + i*barrierDistance;
		poly[0].y = yellowRect.top+barrierY[i];
		poly[1].y = yellowRect.top+barrierY[i] + barrierLength;
		Polyline(hdcMem, poly, 2);
	}
	//绘制小三角
	SelectObject(hdcMem, diamondPen);
	for (i = 0; i <= diamondWidth/2; ++i) {
		poly[0].y = yellowRect.top + diamondY - i;
		poly[1].y = yellowRect.top + diamondY + i;
		poly[0].x = poly[1].x = yellowRect.left + diamondX - i;
		Polyline(hdcMem, poly, 2);
		poly[0].x = poly[1].x = yellowRect.left + diamondX - diamondWidth+i;
		Polyline(hdcMem, poly, 2);
	}
	//回收资源
	DeleteObject(backGroundBrush);
	DeleteObject(barrierPen);
	DeleteObject(diamondPen);
}