// 2dEngine.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "win32Game.h"

#define MAX_LOADSTRING 100
#define KEYDONW(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1:0)
#define KEYUP(vk_code)  ((GetAsyncKeyState(vk_code) & 0x8000)? 0:1)
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR buffer[MAX_LOADSTRING];
// Forward declarations of functions included in this code module:
 
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//游戏循环
void Game_Main(HWND hwnd);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	WNDCLASSEX wndex;
	HWND  hwnd;
//	HACCEL hAccelTable;

	// Initialize global strings
//	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//	LoadString(hInstance, IDC_MY2DENGINE, szWindowClass, MAX_LOADSTRING);
	//定制窗口 
	wndex.cbSize = sizeof(WNDCLASSEX);
	wndex.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndex.lpfnWndProc = WndProc;
	wndex.cbClsExtra = 0;
	wndex.cbWndExtra = 0;
	wndex.hInstance = hInstance;
	wndex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32GAME));
	wndex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndex.lpszMenuName = NULL;
	wndex.lpszClassName = _T("className");
	wndex.hIconSm = LoadIcon(wndex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (!RegisterClassEx(&wndex)) //注册窗口
		return 0;

	if (!(hwnd = CreateWindowEx(NULL,
		_T("className"),
		_T("title"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,
		400, 300,
		NULL,
		NULL,
		hInstance,
		NULL
		)))
		return 0;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDI_WIN32GAME));

	// Main message loop:
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		 
		Game_Main(hwnd);
	}
 
		//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		 
 
	 

	return (int)msg.wParam;
}

//  FUNCTION: Game_Main();
//
//  PURPOSE: Game main loop
 
void Game_Main(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	wsprintf(buffer, _T("up arrow = %d"), KEYDONW(VK_UP) );
	TextOut(hdc, 0,0, buffer, lstrlen(buffer));
	ReleaseDC(hwnd, hdc);
}

 
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_COMMAND:
		{

		}break;
		case WM_PAINT:
		{
		 	COLORREF old_fcolor, old_bcolor;
		 	int old_tmode;

		 	InvalidateRect(hWnd, NULL, FALSE);
			hdc = BeginPaint(hWnd, &ps);
 
			old_fcolor = SetTextColor(hdc, RGB(0,255,0));
			old_bcolor = SetBkColor(hdc, RGB(0,0,0));
			old_tmode  = SetBkMode(hdc, OPAQUE);
			TextOut(hdc, 20,30,_T("Hello"), strlen("Hello"));

			SetTextColor(hdc, old_fcolor);
			SetBkColor(hdc, old_bcolor);
			SetBkMode(hdc, old_tmode); 
					 // TODO: Add any drawing code here...
			EndPaint(hWnd, &ps);
		}break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;
		case WM_CLOSE:
		{
			DefWindowProc(hWnd, message, wParam, lParam);
		}break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

 