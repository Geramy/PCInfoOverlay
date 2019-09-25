#pragma once
#include "ScreenText.h"
class PCInfoDraw
{
public:
	PCInfoDraw();
	void RegisterStencil(HDC dcHandle, ScreenText text);
	void DrawStencil();
	void Unregister();
	~PCInfoDraw();
private:
	bool ReadyToDraw = false;
	ScreenText _stext;
	RECT rect;
	HFONT hFont;
	HFONT hTmp;
	HDC parentHandle;
};

