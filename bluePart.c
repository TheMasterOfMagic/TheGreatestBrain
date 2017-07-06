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
	//创造所需画笔画刷
	backGroundBrush = CreateSolidBrush(BACKGROUNDCOLOR);
	//绘制背景
	SelectObject(hdcMem, backGroundBrush);
	Rectangle(hdcMem, blueRect.left, blueRect.top, blueRect.right, blueRect.bottom);
	//回收资源
	DeleteObject(backGroundBrush);
}