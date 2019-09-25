#pragma once
class TextItem
{
public:
	TextItem(wchar_t* text, UINT size);
	std::wstring *ItemContent;
	UINT FontSize;
	HFONT fontItem;
	~TextItem();
};

