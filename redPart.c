#include <Windows.h>
#include <math.h>
#include "redPart.h"

#define BALLCOLOR RGB(255,0,0)
#define BACKGROUNDCOLOR RGB(255,174,201)

POINT center;//平台中心坐标
float ballOffSet;//小球偏移量
UINT platformLength;//平台长度
UINT ballRadius;//小球半径
float theta;//平台角度
float thetaV;//平台角速度
float deltaV;//平台角速度改变量
float influenceFromBallToV;//小球对平台角速度的影响参数
float influenceFromThetaToBall;//平台角度对小球的影响参数
BOOL leftPress;//方向左键是否被按下
BOOL rightPress;//方向右键是否被按下

void CreateRedGame(void) {
	center.x = (redRect.left + redRect.right) / 2;
	center.y = (redRect.top + redRect.bottom) / 2;
	ballOffSet = 1;
	platformLength = (redRect.right - redRect.left) / 2;//取矩形长的一半
	ballRadius = platformLength / 20;//取平台长度的十分之一
	theta = 0;
	thetaV = 0;
	deltaV = 0.0015;
	influenceFromBallToV = -0.000005;
	influenceFromThetaToBall = -2;
	//SetTimer(hwnd, RED_TIMER_ID, 20, NULL);
}
void OnRedTimer(void) {
	if (pause) {
		return;
	}
	ballOffSet += influenceFromThetaToBall * sin(theta);
	if (abs(ballOffSet) > platformLength / 2) {
		dead = TRUE;
		return;
	}
	thetaV += ballOffSet*influenceFromBallToV;
	if (leftPress) {
		thetaV += deltaV;
	}
	if (rightPress) {
		thetaV -= deltaV;
	}
	theta += thetaV;
	if (abs(theta) >= pi / 2) {
		dead = TRUE;
		return;
	}
}
void OnRedKeyDown(DWORD vk) {
	switch (vk) {
	case VK_LEFT:
		leftPress = TRUE;
		break;
	case VK_RIGHT:
		rightPress = TRUE;
		break;
	default:
		break;
	}
}
void OnRedKeyUp(DWORD vk) {
	switch (vk) {
	case VK_LEFT:
		leftPress = FALSE;
		break;
	case VK_RIGHT:
		rightPress = FALSE;
		break;
	default:
		break;
	}
}
void RedGamePaint(void) {
	HBRUSH backGroundBrush;
	HPEN platformPen, ballPen;
	HBRUSH ballBrush;
	POINT poly[2];
	float c;
	float s;
	UINT ballX, ballY;
	c = cos(theta);
	s = sin(theta);
	ballX = ballOffSet * c + center.x - ballRadius*s;
	ballY = -ballOffSet * s + center.y - ballRadius*c;
	//创造所需画笔画刷
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	platformPen = blackPen(ballRadius/2);
	ballPen = transparentPen();
	ballBrush = CreateSolidBrush(BALLCOLOR);
	//绘制背景
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, redRect.left, redRect.top, redRect.right, redRect.bottom);
	//绘制平台
	SelectObject(hdcMem, platformPen);
	poly[0].x = redRect.left + center.x + platformLength / 2 * c;
	poly[0].y = redRect.top + center.y - platformLength / 2 * s;
	poly[1].x = redRect.left + center.x - platformLength / 2 * c;
	poly[1].y = redRect.top + center.y + platformLength / 2 * s;
	Polyline(hdcMem, poly, 2);
	//绘制小球
	SelectObject(hdcMem, ballPen);
	SelectObject(hdcMem, ballBrush);
	Ellipse(hdcMem, redRect.left+ballX - ballRadius, redRect.top+ballY - ballRadius, redRect.left + ballX + ballRadius, redRect.top + ballY + ballRadius);
	//回收资源
	DeleteObject(backGroundBrush);
	DeleteObject(platformPen);
	DeleteObject(ballPen);
	DeleteObject(ballBrush);
}