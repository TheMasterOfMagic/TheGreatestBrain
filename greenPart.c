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
	//创造所需画笔画刷
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	//绘制背景
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, greenRect.left, greenRect.top, greenRect.right, greenRect.bottom);
	//回收资源
	DeleteObject(backGroundBrush);
}