

#include "stdafx.h"
#include "CGameStart.h"


#include "CGameStart.h"
#include<windows.h>
#include "CPicture.h"
int GameStart::Gamestatus = 0;
Picture* GameStart::Option[7] = { 0 };
GameStart::GameStart()
{
}

void GameStart::freeOption()
{
	delete[] Option;
}
VOID GameStart::LoadMap()
{
	for (int i = 0; i <7; i++)
		Option[i] = new Picture();
	Option[0]->LoadBitmap(L"Resource\\bk.bmp", RGB(255,255,255), 1080, 640);
	Option[1]->LoadBitmap(L"Resource\\start.bmp", RGB(255, 255, 255), 360, 100);
	Option[2]->LoadBitmap(L"Resource\\exit.bmp", RGB(255, 255, 255), 360, 100);
	Option[3]->LoadBitmap(L"Resource\\single.bmp", RGB(255, 255, 255), 360, 100);
	Option[4]->LoadBitmap(L"Resource\\multiplayer.bmp", RGB(255, 255, 255), 360, 100);
	Option[5]->LoadBitmap(L"Resource\\Chosefighter1.bmp", RGB(0, 71, 157), 200, 282);
	Option[6]->LoadBitmap(L"Resource\\Chosefighter2.bmp", RGB(255, 255, 255), 296, 225);
}

VOID GameStart::DrawMap(HWND hWnd)
{
	Option[0]->DrawBitmap(hWnd, 0, 0, 1080, 640, 0, 0);
	switch (Gamestatus)
	{
	case-1:
	case 0:
	case 1:
	{
		
		Option[1]->DrawBitmap(hWnd, 50, 250, 300, 140, 0, 0);
		Option[2]->DrawBitmap(hWnd, 50, 450, 300, 140, 0, 0);
		break;

	}
	case 2:
	case 3:
	case 4:
	{
		HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"Î¢ÈíÑÅºÚ");
		HDC h = GetDC(hWnd);
		SelectObject(h, hFont);
		SetBkMode(h, TRANSPARENT);
		wchar_t text1[] = L"WASD¿ØÖÆÒÆ¶¯";
		wchar_t text2[] = L"Êý×Ö¼üÑ¡×Óµ¯£¬J¿ª»ð";
		wchar_t text3[] = L"¿Õ¸ñ¼ü´ó±¬Õ¨";
		SetTextColor(h, RGB(255, 255, 0));
		TextOut(h, 600, 300, text1, wcslen(text1));
		TextOut(h, 600, 350, text2, wcslen(text2));
		TextOut(h, 600, 400, text3, wcslen(text3));
		DeleteObject(hFont);
		Option[3]->DrawBitmap(hWnd, 50, 250, 300, 140, 0, 0);
		Option[4]->DrawBitmap(hWnd, 50, 450, 300, 140, 0, 0);
		DeleteDC(h);
		break;
	}
	case 5:
	case 6:
	case 7:
	{
		Option[5]->DrawBitmap(hWnd, 250, 250, 200,282, 0, 0);
		Option[6]->DrawBitmap(hWnd, 600, 300, 296, 225, 0, 0);
		break;
	}
	
	default:
		break;
	}
}
VOID GameStart::KeyDown(WPARAM nKeyCode)
{
	switch (nKeyCode)
	{
	case VK_DOWN:
	{
		if (Gamestatus == 1)
		{
			SetGamestatus(-1);
		}
		break;
	}
	case VK_UP:
	{
		if (Gamestatus == -1)
		{
			SetGamestatus(1);
		}
		break;
	}
	case VK_RETURN:
	{
		if (Gamestatus == 1)
		{
			SetGamestatus(2);
		}
		break;
	}

	default:
		break;
	}
}

void GameStart::MouseMove(LPARAM lParam)
{
	int	g_iX = LOWORD(lParam);
	int	g_iY = HIWORD(lParam);
	if (Gamestatus >= -1 && Gamestatus <= 4)
	{
		if (g_iX > 50 && g_iX < 350)
		{
			if (g_iY > 250 && g_iY < 350)
			{
				if (Gamestatus >= -1 && Gamestatus <= 1)Gamestatus = 1;
				else if (Gamestatus >= 2 && Gamestatus <= 4)Gamestatus = 2;
			}
			else if (g_iY > 450 && g_iY < 550)
			{
				if (Gamestatus >= -1 && Gamestatus <= 1)Gamestatus = -1;
				else if (Gamestatus >= 2 && Gamestatus <= 4)Gamestatus = 3;

			}
			else
			{
				if (Gamestatus >= -1 && Gamestatus <= 1)Gamestatus = 0;
				else if (Gamestatus >= 2 && Gamestatus <= 4)Gamestatus = 4;
			}

		}
		else
		{
			if (Gamestatus >= -1 && Gamestatus <= 1)Gamestatus = 0;
			else if (Gamestatus >= 2 && Gamestatus <= 4)Gamestatus = 4;
		}
	}
	else if (Gamestatus >= 5&& Gamestatus <= 7)
	{
		if (g_iX >= 250 && g_iX <= 450)
		{
			if (g_iY >= 250 && g_iY <= 550)
			{
				Gamestatus = 5;
			}
		}
		else if (g_iX >= 600 && g_iX <= 900)
		{
			if (g_iY >= 300 && g_iY <= 600)
			{
				Gamestatus = 6;
			}
		}
		else
					Gamestatus = 7;
	}
}
void GameStart::SetGamestatus(int i)
{
	Gamestatus = i;
}
int GameStart::getGamestatus()
{
	return Gamestatus;
}
GameStart::~GameStart()
{
}