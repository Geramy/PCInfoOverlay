#pragma once
#include "TextItem.h"
#include <vector>
class ScreenText
{
public:
	typedef enum ScreenPosition {
		Top,
		Left,
		Center,
		Right,
		Bottom,
	};
public:
	ScreenText();
	bool AddTextItem(TextItem*);
	int GetTextCount();
	TextItem* GetTextItem(int i);
	ScreenPosition display_position;
	~ScreenText();
private:
	std::vector<TextItem*> textItems;
};

