#include "pch.h"
#include "PCInfoDraw.h"


PCInfoDraw::PCInfoDraw()
{
}

void PCInfoDraw::DrawStencil() {
	this->ReadyToDraw = true;
	int i = 0;
	
	
	while (true) {
		DrawText(this->parentHandle, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
		Sleep(1);
	}
}

void PCInfoDraw::RegisterStencil(HDC dcHandle, ScreenText text) {
	this->parentHandle = dcHandle;
	SetTextColor(this->parentHandle, RGB(0, 0, 255));
	SetBkMode(this->parentHandle, TRANSPARENT);
	SetBkColor(this->parentHandle, RGB(0, 0, 0));
	this->hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, L"Verdana");
	auto hTmp = (HFONT)SelectObject(this->parentHandle, hFont);
	rect.left = 40;
	rect.top = 10;
	::UpdateWindow(0);
}

void PCInfoDraw::Unregister() {
	DeleteObject(SelectObject(parentHandle, this->hTmp));
	::UpdateWindow(0);
	::ReleaseDC(0, this->parentHandle);
	::UpdateWindow(0);
}
PCInfoDraw::~PCInfoDraw()
{
}
