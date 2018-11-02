#include "stdafx.h"
#include "SEU_Beat_Plane.h"
#include "CGameStart.h"
#include "CUserPlane.h"
#include "CPicture.h"
#include "CConnect.h"
#include<windows.h>
#include<Mmsystem.h>
#include<stdio.h>
#pragma comment(lib,"WinMM.Lib")
#define MAX_LOADSTRING 100
using namespace std;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

bool IfSend = false;

DWORD g_tPre = 0, g_tNow = 0;
GameStart start;
HWND hWnd;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL Game_Start_Init();
void Game_Start_Paint(HWND);


#include "CGameControler.h"
HDC g_hdc=NULL;
GameControler *pGameControl = NULL;
static Connect Link;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	PlaySound(TEXT("Animenz - aLIEz - Aldnoah.Zero ED2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//背景音乐

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SEUBEATPLANE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SEUBEATPLANE));
	
	//游戏循环
	while (msg.message != WM_QUIT)
	{
		
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(start.getGamestatus()==9)
			pGameControl->UpdateScence();
		g_tNow= GetTickCount();
	}

	if (!IfSend)
	{
		Link.SendScore(UserPlane::GetScore());
		IfSend = false;
	}

	pGameControl->EXIT();

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SEUBEATPLANE));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_SEUBEATPLANE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd, 100, 10, SCREEN_WIDTH, SCREEN_HEIGHT, true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	Game_Start_Init();
	return TRUE;
}

//
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
	case WM_KEYDOWN:
		if (start.getGamestatus() == 9)
			pGameControl->KeyDown(wParam);
		else start.KeyDown(wParam);
		break;
	case WM_KEYUP:
		if (start.getGamestatus() == 9)
			pGameControl->KeyUp(wParam);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_MOUSEMOVE:
	{
		if (start.getGamestatus() == 9)
			break;
		start.MouseMove(lParam);
		Game_Start_Paint(hWnd);
		break;
	}
	case WM_LBUTTONDOWN:
	{
	
		switch (start.getGamestatus())
		{
		case -1:
			DestroyWindow(hWnd);
			pGameControl->EXIT();
			break;
		case 1:
			start.SetGamestatus(4);
			Game_Start_Paint(hWnd);
			break;
		case 2:
			start.SetGamestatus(5);
			Game_Start_Paint(hWnd);
			break;
		case 5:
			start.SetGamestatus(9);
			UserPlane::chosefighter=1;
			g_hdc = GetDC(hWnd);
			pGameControl = GameControler::GetInstance();
			pGameControl->SetWndDC(g_hdc);
			pGameControl->START();
			UpdateWindow(hWnd);

			pGameControl->UpdateScence();
			UserPlane::SetBestScore(Link.GetBestScore());
			break;
		case 6:
			start.SetGamestatus(9);
			UserPlane::chosefighter=2;
			g_hdc = GetDC(hWnd);
			pGameControl = GameControler::GetInstance();
			pGameControl->SetWndDC(g_hdc);
			pGameControl->START();
			UpdateWindow(hWnd);

			pGameControl->UpdateScence();
			UserPlane::SetBestScore(Link.GetBestScore());
			break;
		case 8:
			start.SetGamestatus(0);
			Game_Start_Paint(hWnd);
			break;
		default:
			break;
		}
		break;
	}
	case WM_DESTROY:
		ReleaseDC(hWnd, g_hdc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

BOOL Game_Start_Init()
{
	GameStart::LoadMap();
	POINT pt, lt, rb;
	RECT rect;

	pt.x = 300;
	pt.y = 100;
	ClientToScreen(hWnd, &pt);
	SetCursorPos(pt.x, pt.y);

	ShowCursor(TRUE);

	GetClientRect(hWnd, &rect);
	lt.x = rect.left;
	lt.y = rect.top;
	rb.x = rect.right;
	rb.y = rect.bottom;

	ClientToScreen(hWnd, &lt);
	ClientToScreen(hWnd, &rb);

	rect.left = lt.x;
	rect.top = lt.y-20;
	rect.right = rb.x;
	rect.bottom = rb.y;

	ClipCursor(&rect);

	return TRUE;
}

VOID Game_Start_Paint(HWND hWnd)
{
	if (g_tNow - g_tPre > 0.3f)
	{
		start.DrawMap(hWnd);
		g_tPre = GetTickCount();

	}

}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
