// PCInfoOverlayCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "PCInfoHiddenWindow.h"

int main()
{
	ScreenText text;
	TextItem *companyName = new TextItem((wchar_t*)L"Leo Fucking Perez Company", 30);
	TextItem *host = new TextItem((wchar_t*)L"FRS-GERAMY-MNM-01", 15);
	TextItem *ipaddr = new TextItem((wchar_t*)L"0.0.0.0", 15);
	TextItem *osbuild = new TextItem((wchar_t*)L"Windows 10 build version 1803", 15);
	TextItem *lastStart = new TextItem((wchar_t*)L"Everyday haha :)", 15);
	text.AddTextItem(companyName);
	text.AddTextItem(host);
	text.AddTextItem(ipaddr);
	text.AddTextItem(osbuild);
	text.AddTextItem(lastStart);
	PCInfoHiddenWindow *draw_window = new PCInfoHiddenWindow(text);
	draw_window->Create();
	draw_window->Wait();

	delete companyName;
	delete host;
	delete ipaddr;
	delete osbuild;
	delete lastStart;
	return 0;
}
