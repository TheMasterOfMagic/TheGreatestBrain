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
	//创造所需画笔画刷
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	//绘制背景
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, yellowRect.left, yellowRect.top, yellowRect.right, yellowRect.bottom);
	//回收资源
	DeleteObject(backGroundBrush);
}