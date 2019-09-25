#include "pch.h"
#include "PCInfoHiddenWindow.h"
#include <thread>

std::map<HWND, PCInfoHiddenWindow*> PCInfoHiddenWindow::message_handles;

PCInfoHiddenWindow::PCInfoHiddenWindow(ScreenText text_data)
{
	this->_displayText = text_data;
	this->background_thread = new std::thread([=] { this->background_processor(this); });
}

void PCInfoHiddenWindow::background_processor(PCInfoHiddenWindow *parent) {
	PCInfoDraw *drawBackgroundObject = new PCInfoDraw();
	PCInfoDraw *drawLockObject = new PCInfoDraw();
	HDC hdc = ::GetDC(FindDTWindow(_T("Progman"), _T("Program Manager")));
	HDC hdcss = ::GetDC(FindDTWindow(_T("Progman"), _T("WindowsScreenSaverClass")));
	bool screenLocked = false;
	bool lockedRegistered = false;
	bool backgroundRegistered = true;
	drawBackgroundObject->RegisterStencil(hdc);
	int runs = 0;
	int total_runs = (int)floor(1000 / 16);
	while (true) {
		std::lock_guard<std::mutex> lock(this->mainMtx);
		//Run our drawing code here for the desktop.

		//Run our drawing code for the lock screen here.
		if (screenLocked) {
			if (!lockedRegistered) {
				lockedRegistered = true;
				drawLockObject->RegisterStencil(hdcss);
			}
			drawLockObject->DrawStencil(parent->_displayText);
		}
		else {
			if (lockedRegistered) {
				drawLockObject->Unregister();
				lockedRegistered = false;
			}
			drawBackgroundObject->DrawStencil(parent->_displayText);
		}
		if (runs++ >= total_runs) {
			runs = 0;
			screenLocked = this->IsSessionLocked();
		}
		if (!this->runBackground)
			break;
		Sleep(16);
	}
}

BOOL PCInfoHiddenWindow::PCInfoHiddenWindow::Create()
{
	return TRUE;
}

bool PCInfoHiddenWindow::IsSessionLocked()
{
	typedef BOOL(PASCAL * WTSQuerySessionInformation)(HANDLE hServer, DWORD SessionId, WTS_INFO_CLASS WTSInfoClass, LPTSTR* ppBuffer, DWORD* pBytesReturned);
	typedef void (PASCAL * WTSFreeMemory)(PVOID pMemory);

	WTSINFOEXW * pInfo = NULL;
	WTS_INFO_CLASS wtsic = WTSSessionInfoEx;
	bool bRet = false;
	LPTSTR ppBuffer = NULL;
	DWORD dwBytesReturned = 0;
	LONG dwFlags = 0;
	WTSQuerySessionInformation pWTSQuerySessionInformation = NULL;
	WTSFreeMemory pWTSFreeMemory = NULL;

	HMODULE hLib = LoadLibrary(L"wtsapi32.dll");
	if (!hLib)
	{
		return false;
	}
	pWTSQuerySessionInformation = (WTSQuerySessionInformation)GetProcAddress(hLib, "WTSQuerySessionInformationW");
	if (pWTSQuerySessionInformation)
	{
		pWTSFreeMemory = (WTSFreeMemory)GetProcAddress(hLib, "WTSFreeMemory");
		if (pWTSFreeMemory != NULL)
		{
			DWORD dwSessionID = WTSGetActiveConsoleSessionId();
			if (pWTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, dwSessionID, wtsic, &ppBuffer, &dwBytesReturned))
			{
				if (dwBytesReturned > 0)
				{
					pInfo = (WTSINFOEXW*)ppBuffer;
					if (pInfo->Level == 1)
					{
						dwFlags = pInfo->Data.WTSInfoExLevel1.SessionFlags;
					}
					if (dwFlags == WTS_SESSIONSTATE_LOCK)
					{
						bRet = true;
					}
				}
				pWTSFreeMemory(ppBuffer);
				ppBuffer = NULL;
			}
		}
	}
	if (hLib != NULL)
	{
		FreeLibrary(hLib);
	}
	return bRet;
}

HWND PCInfoHiddenWindow::FindDTWindow(LPCWSTR className, LPCWSTR WindowName)
{
	HWND hWnd = ::FindWindow(className, WindowName);

	DWORD dResult = 0;

	SendMessageTimeout(hWnd,
		0x052C,
		0,
		NULL,
		SMTO_NORMAL,
		1000,
		&dResult);

	HWND hwndWorkW = NULL;
	do
	{
		hwndWorkW = ::FindWindowEx(NULL, hwndWorkW, L"WorkerW", NULL);
		if (NULL == hwndWorkW)
		{
			continue;
		}

		HWND hView = ::FindWindowEx(hwndWorkW, NULL, L"SHELLDLL_DefView", NULL);
		if (NULL == hView)
		{
			continue;
		}

		HWND h = ::FindWindowEx(NULL, hwndWorkW, L"WorkerW", NULL);
		while (NULL != h)
		{
			SendMessage(h, WM_CLOSE, 0, 0);
			h = ::FindWindowEx(NULL, hwndWorkW, L"WorkerW", NULL);
		}
		break;

	} while (true);

	return hWnd;
}

PCInfoHiddenWindow::~PCInfoHiddenWindow()
{
}
