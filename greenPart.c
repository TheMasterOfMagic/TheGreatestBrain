#include <Windows.h>
#include "greenPart.h"

#define RECTANGLECOLOR RGB(34,177,76)
#define BACKGROUNDCOLOR RGB(145,234,171)

void CreateGreenGame(void) {

}
void OnGreenTimer(void) {

}
void OnGreenKeyDown(DWORD vk) {

}
void OnGreenKeyUp(DWORD vk) {

}
void GreenGamePaint(void) {
	HBRUSH backGroundBrush;
	//�������軭�ʻ�ˢ
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	//���Ʊ���
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, greenRect.left, greenRect.top, greenRect.right, greenRect.bottom);
	//������Դ
	DeleteObject(backGroundBrush);
}