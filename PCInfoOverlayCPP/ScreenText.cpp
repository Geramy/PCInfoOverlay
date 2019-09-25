#include "pch.h"
#include "ScreenText.h"


ScreenText::ScreenText()
{
}

bool ScreenText::AddTextItem(TextItem* tItem) {
	this->textItems.push_back(tItem);
	return true;
}

int ScreenText::GetTextCount() {
	return this->textItems.capacity();
}
TextItem* ScreenText::GetTextItem(int i)
{
	return this->textItems.at(i);
}

ScreenText::~ScreenText()
{
}
