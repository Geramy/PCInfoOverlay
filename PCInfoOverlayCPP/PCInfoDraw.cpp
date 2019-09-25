#include "pch.h"
#include "PCInfoDraw.h"


PCInfoDraw::PCInfoDraw()
{
}

void PCInfoDraw::DrawStencil() {
	if (this->ReadyToDraw) {
		for (int i = 0; i < this->_stext.GetTextCount(); i++) {
			TextItem *textObj = this->_stext.GetTextItem(i);
			DrawText(this->parentHandle, textObj->ItemContent->c_str(), -1, &rect, DT_SINGLELINE | DT_NOCLIP);
		}
	}
}

void PCInfoDraw::RegisterStencil(HDC dcHandle, ScreenText text) {
	this->ReadyToDraw = true;
	this->_stext = text;
	this->parentHandle = dcHandle;
	SetTextColor(this->parentHandle, RGB(250, 250, 250));
	SetBkMode(this->parentHandle, TRANSPARENT);
	SetBkColor(this->parentHandle, RGB(0, 0, 0));
	this->hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, L"Verdana");
	auto hTmp = (HFONT)SelectObject(this->parentHandle, hFont);
	rect.left = 40;
	rect.top = 10;
	::UpdateWindow(0);
}

void PCInfoDraw::Unregister() {
	this->ReadyToDraw = false;
	DeleteObject(SelectObject(parentHandle, this->hTmp));
	::UpdateWindow(0);
	::ReleaseDC(0, this->parentHandle);
	::UpdateWindow(0);
}
PCInfoDraw::~PCInfoDraw()
{
}
