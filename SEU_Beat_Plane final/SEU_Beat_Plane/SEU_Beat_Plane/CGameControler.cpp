#include "StdAfx.h"
#include "CGameControler.h"
#include "CBase_Spriet.h"
#include"CUserPlane.h"
#include "CBullet.h"
#include "CEnemyPlane.h"
#include "CExplosion.h"
#include "CBigBoss.h"
#include "CGift.h"
#include "CGameStart.h"



GameControler * GameControler::CGC_pGameControler = NULL;

GameControler* GameControler::GetInstance()
{
	if (NULL == CGC_pGameControler)
	{
		CGC_pGameControler = new GameControler;
	}

	return CGC_pGameControler;
}

GameControler::GameControler(void):CGC_nY(0),
	CGC_fElapsedTime(0)
{
	CGC_nPreKey = CGC_nCurKey = 0;
	UserPlane::LoadBimap();
	Bullet::LoadBullet();
	EnemyPlane::LoadBimap();
	Explosion::LoadImage();
	Gift::LoadImage();
	CGC_pPrincipalPlane = UserPlane::GetInstance();	
}


GameControler::~GameControler(void)
{
	
}

void GameControler::EXIT()
{
	UserPlane::FreeBitmap();
	EnemyPlane::FreeBitmap();
	Explosion::FreeImage();
	Bullet::FreeBullet();
	Gift::FreeImage();
	DeleteDC(CGC_hMemDC);
	DeleteDC(CGC_hMapDC);
	DeleteObject(CGC_hBitmapMap);
	DeleteObject(CGC_hMemBitmap);
}

void GameControler::END()
{
	DeleteObject(CGC_hBitmapMap);
	CGC_hBitmapMap = (HBITMAP)LoadImage(NULL, _T("Resource\\gameover.bmp"), IMAGE_BITMAP,
		SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
	SelectObject(CGC_hMapDC, CGC_hBitmapMap);
	BitBlt(CGC_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, CGC_hMapDC, 0, 0, SRCCOPY);
	UserPlane::GetInstance();
	GameStart::SetGamestatus(8);
}

void GameControler::WIN()
{
	DeleteObject(CGC_hBitmapMap);
	CGC_hBitmapMap = (HBITMAP)LoadImage(NULL, _T("Resource\\WIN.bmp"), IMAGE_BITMAP,
		SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
	SelectObject(CGC_hMapDC, CGC_hBitmapMap);
	BitBlt(CGC_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, CGC_hMapDC, 0, 0, SRCCOPY);
	GameStart::SetGamestatus(8);
}

void GameControler::CirculationMap()
{
	BitBlt(CGC_hMemDC, 0, 0, SCREEN_WIDTH, CGC_nY, CGC_hMapDC, 0, SCREEN_HEIGHT - CGC_nY, SRCCOPY);

	BitBlt(CGC_hMemDC, 0, CGC_nY, SCREEN_WIDTH, SCREEN_HEIGHT - CGC_nY, CGC_hMapDC, 0, 0, SRCCOPY);

	CGC_nY += 0.5;
	if(CGC_nY==640)
		CGC_nY = 0;
}

void GameControler::SetWndDC(HDC hDC)
{
	CGC_hWndDC = hDC;
	CGC_hMemDC = CreateCompatibleDC(hDC);
	CGC_hMapDC = CreateCompatibleDC(hDC);

	CGC_hMemBitmap = CreateCompatibleBitmap(hDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(CGC_hMemDC, CGC_hMemBitmap);

	CGC_hBitmapMap = (HBITMAP)LoadImage(NULL, _T("Resource\\Map.bmp"), IMAGE_BITMAP,
		SCREEN_WIDTH, SCREEN_HEIGHT, LR_LOADFROMFILE);
	SelectObject(CGC_hMapDC, CGC_hBitmapMap);
}

void GameControler::START()
{
	CGC_dwLastTime = GetTickCount();
	srand((unsigned)time(0));
}


void GameControler::UpdateScence()
{
	if (BigBoss::win == 1)
	{
		WIN();
		BigBoss::win = 0;
		return;
	}
	if (UserPlane::GetGameOver())
	{
		UserPlane::CUP_bGameOver = false;
		END();
		return;
	}


	CGC_dwCurrentTime = GetTickCount();
	if (CGC_dwCurrentTime - CGC_dwLastTime < MSPERFRAME)
	{
		return;
	}

	SelectObject(CGC_hMemDC, GetStockObject(BLACK_BRUSH));
	Rectangle(CGC_hMemDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	CirculationMap();
	CGC_fElapsedTime = (CGC_dwCurrentTime - CGC_dwLastTime) / 1000.0;

	CGC_dwLastTime = CGC_dwCurrentTime;

	EnemyPlane::CreateEnemy();
	Base_Sprite::FrameUpdate();
	Base_Sprite::FrameRender(CGC_hMemDC);

	BitBlt(CGC_hWndDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, CGC_hMemDC, 0, 0, SRCCOPY);
}

void GameControler::KeyDown(WPARAM nKeyCode)
{
	switch (nKeyCode)
	{
	case 'A':
	case 'S':
	case 'D':
	case 'W':
		CGC_nPreKey = CGC_nCurKey;
		CGC_nCurKey = nKeyCode;


		if ( (CGC_nPreKey + CGC_nCurKey)%'A' == 0)
		{
			CGC_pPrincipalPlane->Control(LEFT);
		}
		else if ((CGC_nPreKey + CGC_nCurKey)%'D'==0)
		{
			CGC_pPrincipalPlane->Control(RIGHT);
		}
		else if ((CGC_nPreKey + CGC_nCurKey)%'W' == 0)
		{
			CGC_pPrincipalPlane->Control(UP);
		}
		else if ((CGC_nPreKey + CGC_nCurKey)%'S' == 0)
		{
			CGC_pPrincipalPlane->Control(DOWN);
		}
		else if ((CGC_nPreKey + CGC_nCurKey) == ('A' + 'W'))
		{
			CGC_pPrincipalPlane->Control(LEFT_UP);

		}
		else if ((CGC_nPreKey + CGC_nCurKey) == ('A' + 'S'))
		{
			CGC_pPrincipalPlane->Control(LEFT_DOWN);
	
		}
		else if ((CGC_nPreKey + CGC_nCurKey) == ('D' + 'W'))
		{
			CGC_pPrincipalPlane->Control(RIGHT_UP);

		}
		else if ((CGC_nPreKey + CGC_nCurKey) == ('D' + 'S'))
		{
			CGC_pPrincipalPlane->Control(RIGHT_DOWN);

		}		
		break;
	case 'J':
		CGC_pPrincipalPlane->Control(FIRE);
		break;
	case '1':
		CGC_pPrincipalPlane->SetBulletType(AMMO0);
		break;
	case '2':
	{
		if ((UserPlane::GetScore() >= 84 && UserPlane::GetScore() <= 500) || UserPlane::GetScore() >= 584) 
		{
			CGC_pPrincipalPlane->SetBulletType(AMMO1);
		}		
		break;
	}
	case '3':
	{
		if ((UserPlane::GetScore() >= 168 && UserPlane::GetScore() <= 500) || UserPlane::GetScore() >= 668)
		{
			CGC_pPrincipalPlane->SetBulletType(AMMO2);
		}
		break;
	}
		break;
	case '4':
	{
		if ((UserPlane::GetScore() >= 252 && UserPlane::GetScore() <= 500) || UserPlane::GetScore() >= 752)
		{
			CGC_pPrincipalPlane->SetBulletType(AMMO3);
		}
		break;
	}
		break;
	case '5':
	{
		if ((UserPlane::GetScore() >= 336 && UserPlane::GetScore() <= 500) || UserPlane::GetScore() >= 836)
		{
			CGC_pPrincipalPlane->SetBulletType(AMMO1);
		}
		break;
	}
		break;
	case '6':
	{
		if ((UserPlane::GetScore() >= 420 && UserPlane::GetScore() <= 500) || UserPlane::GetScore() >= 920)
		{
			CGC_pPrincipalPlane->SetBulletType(AMMO1);
		}
		break;
	}
		break;
	case '7':
	{
		if ((UserPlane::GetScore() >= 470 && UserPlane::GetScore() <= 500) || UserPlane::GetScore() >= 970)
		{
			CGC_pPrincipalPlane->SetBulletType(AMMO1);
		}
		break;
	}
		break;
	case VK_SPACE:
		CGC_pPrincipalPlane->Control(FIREALL);
		break;
	}
}

void GameControler::KeyUp(WPARAM nKeyCode)
{
	if (nKeyCode == CGC_nCurKey)
	{	
		if (CGC_nPreKey && (CGC_nPreKey != CGC_nCurKey))
		{
			CGC_nCurKey = CGC_nPreKey;
			CGC_nPreKey = 0;
			if ((CGC_nPreKey + CGC_nCurKey) % 'A' ==0)
			{
				CGC_pPrincipalPlane->Control(LEFT);
			}
			else if ((CGC_nPreKey + CGC_nCurKey) % 'D' == 0)
			{
				CGC_pPrincipalPlane->Control(RIGHT);
			}
			else if ((CGC_nPreKey + CGC_nCurKey) % 'W' == 0)
			{
				CGC_pPrincipalPlane->Control(UP);
			}
			else if ( (CGC_nPreKey + CGC_nCurKey) % 'S' == 0)
			{
				CGC_pPrincipalPlane->Control(DOWN);
			}
		}
		else
		{
			CGC_nCurKey = 0;
			CGC_pPrincipalPlane->Control(STOP_MOVE);
		}
	}
	else if (nKeyCode == CGC_nPreKey)
	{	
		if (CGC_nCurKey)
		{
			CGC_nPreKey = 0;
			if ((CGC_nPreKey + CGC_nCurKey) % 'A' ==0)
			{
				CGC_pPrincipalPlane->Control(LEFT);
			}
			else if ((CGC_nPreKey + CGC_nCurKey) % 'D' == 0)
			{
				CGC_pPrincipalPlane->Control(RIGHT);
			}
			else if ((CGC_nPreKey + CGC_nCurKey) % 'W' == 0)
			{
				CGC_pPrincipalPlane->Control(UP);
			}
			else if ( (CGC_nPreKey + CGC_nCurKey) % 'S' == 0)
			{
				CGC_pPrincipalPlane->Control(DOWN);
			}
		}
		else
		{
			CGC_nPreKey = 0;
			CGC_pPrincipalPlane->Control(STOP_MOVE);
		}
	}
	else if ( nKeyCode == 'J')
	{
		CGC_pPrincipalPlane->Control(STOP_FIRE);
	}
}