#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include "game.h"
#include "redPart.h"
#include "bluePart.h"
#include "yellowPart.h"
#include "greenPart.h"


short left, top, right, bottom, midX, midY;
float zoomRate;

DWORD WINAPI PlayMySound(LPVOID pParam) {
	PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME);
}


void CreateGame() {
	hdc = GetDC(hwnd);
	dead = FALSE;
	pause = TRUE;
	zoomRate = 0.5;
	Resize();
	CreateRedGame();
	CreateBlueGame();
	CreateYellowGame();
	CreateGreenGame();
	CreateThread(0, 0, PlayMySound, 0, 0, 0);
	SetTimer(hwnd, PAINTER_TIMER_ID, 10, NULL);//��������֡�ʵ�Painter Timer
}
void OnTimer(TIMER_ID timerID) {
	switch (timerID) {
	case RED_TIMER_ID:
		OnRedTimer();
		if (dead) {
			KillAllTimer();
			MessageBox(hwnd, "��ĺ�ɫС������Ҫ����ȥ�ˣ�", "��Ϸ����", NULL);
			ExitProcess(0);
		}
		break;
	case BLUE_TIMER_ID:
		OnBlueTimer();
		if (dead) {
			KillAllTimer();
			MessageBox(hwnd, "�����ɫС��������ײ���ˣ�", "��Ϸ����", NULL);
			ExitProcess(0);
		}
		break;
	case GREEN_TIMER_ID:
		OnGreenTimer();
		if (dead) {
			KillAllTimer();
			MessageBox(hwnd, "�����ɫС����������ײ���ˣ�", "��Ϸ����", NULL);
			ExitProcess(0);
		}
		break;
	case YELLOW_TIMER_ID:
		OnYellowTimer();
		if (dead) {
			KillAllTimer();
			MessageBox(hwnd,"��Ļ�ɫС���κ�������ˣ�","��Ϸ����",NULL);
			ExitProcess(0);
		}
		break;
	case PAINTER_TIMER_ID:
		GamePaint();
		break;
	default:
		break;
	}
}
void OnKeyDown(DWORD vk) {
	switch (vk) {
	case 'P':
		pause = !pause;
		break;
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
	HBITMAP hbmMem;
	HPEN pen;
	hdcMem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	pen = transparentPen();
	SelectObject(hdcMem, hbmMem);

	//�ĸ����ֱַ����
	SelectObject(hdcMem, pen);
	RedGamePaint();
	SelectObject(hdcMem, pen);
	BlueGamePaint();
	SelectObject(hdcMem, pen);
	YellowGamePaint();
	SelectObject(hdcMem, pen);
	GreenGamePaint();

	//���
	BitBlt(hdc,0, 0, rect.right - rect.left, rect.bottom - rect.top,hdcMem, 0, 0, SRCCOPY);

	//������Դ
	DeleteObject(hbmMem);
	DeleteObject(hdcMem);
}
void ResizeRedPart(void) {
	midX = (left + right) * zoomRate;
	midY = (top + bottom)  * zoomRate;
	//��ɫ���������Ͻ�
	redRect.left = left;
	redRect.top = top;
	redRect.right = midX;
	redRect.bottom = midY;
}
void ResizeBluePart(void) {
	midX = (left + right) * zoomRate;
	midY = (top + bottom)  * zoomRate;
	//��ɫ���������Ͻ�
	blueRect.left = right - midX;
	blueRect.top = top;
	blueRect.right = right;
	blueRect.bottom = midY;
}
void ResizeYellowPart(void) {
	midX = (left + right) * zoomRate;
	midY = (top + bottom)  * zoomRate;
	//��ɫ���������½�
	yellowRect.left = left;
	yellowRect.top = bottom - midY;
	yellowRect.right = midX;
	yellowRect.bottom = bottom;
}
void ResizeGreenPart(void) {
	midX = (left + right) * zoomRate;
	midY = (top + bottom)  * zoomRate;
	//��ɫ���������½�
	greenRect.left = right - midX;
	greenRect.top = bottom - midY;
	greenRect.right = right;
	greenRect.bottom = bottom;
}
void Resize(void) {
	GetClientRect(hwnd, &rect);

	left = rect.left;
	top = rect.top;
	right = rect.right;
	bottom = rect.bottom;

	ResizeRedPart();
	ResizeBluePart();
	ResizeYellowPart();
	ResizeGreenPart();
}
void KillAllTimer(void) {
	KillTimer(hwnd, RED_TIMER_ID);
	KillTimer(hwnd, BLUE_TIMER_ID);
	KillTimer(hwnd, GREEN_TIMER_ID);
	KillTimer(hwnd, YELLOW_TIMER_ID);
	KillTimer(hwnd, PAINTER_TIMER_ID);
}

HPEN blackPen(int cWidth) {
	return CreatePen(PS_SOLID, cWidth, RGB(0, 0, 0));
}
HPEN transparentPen(void) {
	return CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}