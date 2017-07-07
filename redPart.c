#include <Windows.h>
#include <math.h>
#include "redPart.h"

#define BALLCOLOR RGB(255,0,0)
#define BACKGROUNDCOLOR RGB(255,174,201)

POINT center;//ƽ̨��������
float ballOffSet;//С��ƫ����
UINT platformLength;//ƽ̨����
UINT ballRadius;//С��뾶
float theta;//ƽ̨�Ƕ�
float thetaV;//ƽ̨���ٶ�
float deltaV;//ƽ̨���ٶȸı���
float influenceFromBallToV;//С���ƽ̨���ٶȵ�Ӱ�����
float influenceFromThetaToBall;//ƽ̨�Ƕȶ�С���Ӱ�����
BOOL leftPress;//��������Ƿ񱻰���
BOOL rightPress;//�����Ҽ��Ƿ񱻰���

void CreateRedGame(void) {
	center.x = (redRect.left + redRect.right) / 2;
	center.y = (redRect.top + redRect.bottom) / 2;
	ballOffSet = 1;
	platformLength = (redRect.right - redRect.left) / 2;//ȡ���γ���һ��
	ballRadius = platformLength / 20;//ȡƽ̨���ȵ�ʮ��֮һ
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
	//�������軭�ʻ�ˢ
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	platformPen = blackPen(ballRadius/2);
	ballPen = transparentPen();
	ballBrush = CreateSolidBrush(BALLCOLOR);
	//���Ʊ���
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, redRect.left, redRect.top, redRect.right, redRect.bottom);
	//����ƽ̨
	SelectObject(hdcMem, platformPen);
	poly[0].x = redRect.left + center.x + platformLength / 2 * c;
	poly[0].y = redRect.top + center.y - platformLength / 2 * s;
	poly[1].x = redRect.left + center.x - platformLength / 2 * c;
	poly[1].y = redRect.top + center.y + platformLength / 2 * s;
	Polyline(hdcMem, poly, 2);
	//����С��
	SelectObject(hdcMem, ballPen);
	SelectObject(hdcMem, ballBrush);
	Ellipse(hdcMem, redRect.left+ballX - ballRadius, redRect.top+ballY - ballRadius, redRect.left + ballX + ballRadius, redRect.top + ballY + ballRadius);
	//������Դ
	DeleteObject(backGroundBrush);
	DeleteObject(platformPen);
	DeleteObject(ballPen);
	DeleteObject(ballBrush);
}