#include "pch.h"
#include "TextItem.h"


TextItem::TextItem(wchar_t* text, UINT size)
{
	this->FontSize = size;
	this->ItemContent = new std::wstring(text);
	this->fontItem = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, L"Verdana");
}


TextItem::~TextItem()
{
}
