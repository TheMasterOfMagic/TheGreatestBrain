#include <Windows.h>
#include "redPart.h"

#define BALLCOLOR RGB(255,0,0)
#define BACKGROUNDCOLOR RGB(255,174,201)

void CreateRedGame(void) {

}
void OnRedTimer(void) {

}
void OnRedKeyDown(DWORD vk) {

}
void OnRedKeyUp(DWORD vk) {

}
void RedGamePaint(void) {
	HBRUSH backGroundBrush;
	//�������軭�ʻ�ˢ
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	//���Ʊ���
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, redRect.left, redRect.top, redRect.right, redRect.bottom);
	//������Դ
	DeleteObject(backGroundBrush);
}