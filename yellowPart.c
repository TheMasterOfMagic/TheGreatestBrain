#include <Windows.h>
#include "yellowPart.h"


#define DIAMONDCOLOR (broken ?  RGB(150,150,150) : RGB(255,255-temperature,0))
#define BACKGROUNDCOLOR RGB(255,255,180)

#define N 4//ͬһʱ���ϰ�����

int temperature;
int barrierDistance;//�ϰ���֮��ļ������
int barrierX;//������ϰ��ĺ�����
int barrierLength;//�ϰ��ĳ���
int barrierY[N];//ÿ���ϰ��϶˵��������
UINT barrierDirection[N];//ÿ���ϰ����ݷ����ٶ�
UINT speed;//�ٶ�
BOOL spacePress;
int diamondX;//С�������Ҷ˵ĺ�����
int diamondY;//С����������
int diamondWidth;//С���ο��
BOOL broken;

void CreateYellowGame(void) {
	const int width = yellowRect.right - yellowRect.left;
	const int height = yellowRect.bottom - yellowRect.top;
	int i;

	temperature = 0;
	barrierDistance = width / N;//ȡ�����������ԵN��֮һ��ȵ�λ��
	barrierX = barrierDistance;
	barrierLength = height / 4;//ȡ����߶ȵ��ķ�֮һ
	for (i = 0; i < N; ++i) {
		barrierY[i] = rand() % (height - barrierLength);
		barrierDirection[i] = rand() & 1 ? 1 : -1;
	}
	speed = 1;
	spacePress = FALSE;
	diamondX = width / 6;//ȡ�����������Ե����֮һ��ȵ�λ��
	diamondY = height / 2;//ȡ�����м�ĸ߶�
	diamondWidth = width / 20;//ȡ�����ȵĶ�ʮ��֮һ
	broken = FALSE;
	SetTimer(hwnd, YELLOW_TIMER_ID, 20, NULL);
}
void OnYellowTimer(void) {
	int i;
	const int height = yellowRect.bottom - yellowRect.top;

	if (pause) {
		return;
	}
	//�ϰ����ƶ�
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
	//�ж��Ƿ����޵�״̬
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
		//�ж��Ƿ�����
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
	//�������軭�ʻ�ˢ
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	barrierPen = CreatePen(PS_SOLID,diamondWidth / 4,(spacePress && !broken ? RGB(255,255,255):RGB(0,0,0)));
	diamondPen = CreatePen(PS_SOLID, 1, DIAMONDCOLOR);
	//���Ʊ���
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, yellowRect.left, yellowRect.top, yellowRect.right, yellowRect.bottom);
	//�����ϰ�
	SelectObject(hdcMem, barrierPen);
	for (i = 0; i < N; ++i) {
		poly[0].x = poly[1].x = yellowRect.left+barrierX + i*barrierDistance;
		poly[0].y = yellowRect.top+barrierY[i];
		poly[1].y = yellowRect.top+barrierY[i] + barrierLength;
		Polyline(hdcMem, poly, 2);
	}
	//����С����
	SelectObject(hdcMem, diamondPen);
	for (i = 0; i <= diamondWidth/2; ++i) {
		poly[0].y = yellowRect.top + diamondY - i;
		poly[1].y = yellowRect.top + diamondY + i;
		poly[0].x = poly[1].x = yellowRect.left + diamondX - i;
		Polyline(hdcMem, poly, 2);
		poly[0].x = poly[1].x = yellowRect.left + diamondX - diamondWidth+i;
		Polyline(hdcMem, poly, 2);
	}
	//������Դ
	DeleteObject(backGroundBrush);
	DeleteObject(barrierPen);
	DeleteObject(diamondPen);
}