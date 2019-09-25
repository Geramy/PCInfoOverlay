#include "pch.h"
#include "TextItem.h"


TextItem::TextItem(wchar_t* text)
{
	this->ItemContent = new std::wstring(text);
}


TextItem::~TextItem()
{
}
