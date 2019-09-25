#pragma once
class TextItem
{
public:
	TextItem(wchar_t *);
	std::wstring *ItemContent;
	UINT *FontSize;
	~TextItem();
};

