#include <Windows.h>
#include "yellowPart.h"

#define TRIANGLECOLOR RGB(255,255,0)
#define BACKGROUNDCOLOR RGB(255,255,123)

void CreateYellowGame(void) {

}
void OnYellowTimer(void) {

}
void OnYellowKeyDown(DWORD vk) {

}
void OnYellowKeyUp(DWORD vk) {

}
void YellowGamePaint(void) {
	HBRUSH backGroundBrush;
	//�������軭�ʻ�ˢ
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	//���Ʊ���
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, yellowRect.left, yellowRect.top, yellowRect.right, yellowRect.bottom);
	//������Դ
	DeleteObject(backGroundBrush);
}