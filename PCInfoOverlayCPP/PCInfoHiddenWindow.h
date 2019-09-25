#pragma once
#include <iterator>
#include <map>
#include <thread>
#include <mutex>
#include <vector>
#include "ScreenText.h"
#include "PCInfoDraw.h"
#include <WtsApi32.h>

class PCInfoHiddenWindow
{
public:
	PCInfoHiddenWindow(ScreenText);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
	BOOL Create();
	void HandleMessage(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
	~PCInfoHiddenWindow();
private:
	void background_processor(PCInfoHiddenWindow *parent);
	HWND FindDTWindow(LPCWSTR className, LPCWSTR WindowName);
	bool IsSessionLocked();
private:
	
	bool WindowsLocked = false;
	bool runBackground = true;
	static std::map<HWND, PCInfoHiddenWindow*> message_handles;
	std::thread *background_thread;
	std::mutex mainMtx;
	ScreenText _displayText;
};