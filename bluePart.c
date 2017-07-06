#include <Windows.h>
#include <time.h>
#include "bluePart.h"

#define TRIANGLECOLOR RGB(0,162,232)
#define BACKGROUNDCOLOR RGB(153,217,234)

short triangleOffSet;//С����ƫ����(-1,0,1)
UINT triangleWidth;//С���ǿ��
UINT wallLength;//ǽ�ĳ���
UINT triangleX;//С���ǵĺ�����
UINT wallX;//���Ҳ�ǽ��λ��
UINT wallDistance;//ǽ���
BOOL walls[3][3] = { 1,1,1,1,1,1,1,1,1 };
UINT speed;//�ƶ��ٶ�

void CreateBlueGame(void) {
	const int width = blueRect.right - blueRect.left;
	const int height = blueRect.bottom - blueRect.top;
	triangleOffSet = 0;
	triangleWidth = width / 20;//ȡ�����ȵĶ�ʮ��֮һ
	wallLength = height / 3;//ȡ����߶ȵ�����֮һ
	triangleX = width * 5 / 6;//���������ұ�Ե����֮һ��ȵ�λ��
	wallX = width * 2 / 3;//���Ҳ�ǽ�ĺ����꣬���������ұ�Ե����֮һ��ȵ�λ��
	wallDistance = width / 3;//ȡ�����ȵ�����֮һ
	srand(time(0) + rand());
	//ÿһ��ǽ��һ��ȱ��
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
	//�������軭�ʻ�ˢ
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	wallPen = blackPen(triangleWidth / 4);
	trianglePen = CreatePen(PS_SOLID, 1, TRIANGLECOLOR);
	//���Ʊ���
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, blueRect.left, blueRect.top, blueRect.right, blueRect.bottom);
	//����ǽ��
	SelectObject(hdcMem, wallPen);
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			//���������i�У��������µ�j��
			if (walls[i][j]) {
				poly[0].x = poly[1].x = blueRect.left + wallX - i*wallDistance;
				poly[0].y = blueRect.top + j*wallLength;
				poly[1].y = blueRect.top + (j + 1)*wallLength;
				Polyline(hdcMem, poly, 2);
			}
		}
	}
	//����С����
	SelectObject(hdcMem, trianglePen);
	for (j = 0; j < triangleWidth; ++j) {
		poly[0].x = poly[1].x = blueRect.left + triangleX + j;
		poly[0].y = blueRect.top+triangleOffSet*wallLength + height / 2 + j*0.65;
		poly[1].y = blueRect.top+triangleOffSet*wallLength + height / 2 - j*0.65;
		Polyline(hdcMem, poly, 2);
	}
	//������Դ
	DeleteObject(backGroundBrush);
	DeleteObject(wallPen);
	DeleteObject(trianglePen);
}