#include <Windows.h>
#include "bluePart.h"

#define TRIANGLECOLOR RGB(0,162,232)
#define BACKGROUNDCOLOR RGB(153,217,234)

void CreateBlueGame(void) {

}
void OnBlueTimer(void) {

}
void OnBlueKeyDown(DWORD vk) {

}
void OnBlueKeyUp(DWORD vk) {

}
void BlueGamePaint(void) {
	HBRUSH backGroundBrush;
	//�������軭�ʻ�ˢ
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	//���Ʊ���
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, blueRect.left, blueRect.top, blueRect.right, blueRect.bottom);
	//������Դ
	DeleteObject(backGroundBrush);
}