#include "StdAfx.h"
#include "CEnemyPlane.h"
#include "CGameControler.h"
#include "CEnemyBullet.h"
#include "CUserPlane.h"
#include "CUserBullet.h"
#include "CExplosion.h"
#include "CEnemyTrackerPlane.h"
#include "CTrackerBullet.h"
#include "CBigBoss.h"
#include "CGift.h"
#include <math.h>
#include<windows.h>
#include<Mmsystem.h>
#include<stdio.h>
#pragma comment(lib,"WinMM.Lib")
using namespace std;


Photo * EnemyPlane::CEP_pPhotoEnemy[9] = {0};
Photo * EnemyPlane::CEP_pPhotoHP;
Photo * EnemyPlane::CEP_pPhotoHPSide;
float EnemyPlane::CEP_fLastCreateTime = 0.0;
float EnemyPlane::CEP_fLastCreateBomberPlaneTime = 0.0;
int EnemyPlane::CEP_nEnemyCount = 0;
EnemyPlane * EnemyPlane::spEnemyHead = NULL;



EnemyPlane::EnemyPlane(EnemyType enemyType):Base_Sprite(0, 0),CEP_nEnemyType(enemyType)
{
	CBS_nFrameStartX = 0;
	CBS_nCurrentFrame = 0;
	int nRandom = rand() % 50;//随机随0-2产生的飞机从屏幕上方左中右出现
							
	CEP_fFireTime = 1.0f;

	if (CEP_nEnemyCount < 10)
	{
		CEP_nEnemyCount++;
	}
	
	switch (CEP_nEnemyType)
	{
	case ENEMY0:
		CBS_nWidth = 43;
		CBS_nHeight = 36;
		CEP_nWholeHP = CEP_nHP = 4;
		CBS_nSpeed = 150;
		CBS_fAngle = PI / 2;
		CEP_fAllTime = 3.0;
		CBS_nScore = 1;
		break;
	case ENEMY1:
		CBS_nWidth = 76;
		CBS_nHeight = 94;
		CEP_nWholeHP = CEP_nHP = 10;
		CBS_nSpeed = 100;
		CBS_fAngle = PI / 2;
		CEP_fAllTime = 3.0;
		CBS_nScore = 2;
		break;
	case ENEMY2:
		CBS_nWidth = 93;
		CBS_nHeight = 85;
		CEP_nWholeHP = CEP_nHP = 10;
		CBS_nSpeed = 90;
		CBS_fAngle = PI / 2;
		CEP_fAllTime = 3.0;
		CBS_nScore = 3;
		break;
	case ENEMY3:
		CBS_nWidth = 100;
		CBS_nHeight = 47;
		CEP_nWholeHP = CEP_nHP = 6;
		CBS_nSpeed = 80;
		CBS_fAngle = PI / 2;
		CEP_fAllTime = 3.0;
		CBS_nScore = 4;
		break;
	case ENEMY4:
		CBS_nWidth = 45;
		CBS_nHeight = 43;
		CEP_nWholeHP = CEP_nHP = 8;
		CBS_nSpeed = 100;
		CBS_fAngle = PI / 2;
		CEP_fAllTime = 3.0;
		CBS_nScore = 5;
		break;
	case BOSS:
		CBS_nWidth = 100;
		CBS_nHeight = 108;
		CEP_nWholeHP = CEP_nHP = 500;
		CBS_nSpeed = 100;
		CBS_fAngle = PI / 2;
		CEP_fAllTime = 3.0;
		CBS_nScore = 2000;
		break;
	case BIGBOSS:
		CBS_nWidth = 96;
		CBS_nHeight = 123;
		CEP_nWholeHP = CEP_nHP = 1000;
		CBS_nSpeed = 100;
		CBS_fAngle = PI / 2;
		CEP_fAllTime = 3.0;
		CBS_nScore = 1000;

	}

	if (nRandom == 0)
	{
		CBS_nX = 0;
	}
	else
	{
		CBS_nX = nRandom * SCREEN_WIDTH/50 - CBS_nWidth / 2;
	}
	CBS_nY = -CBS_nHeight + 2; 

	m_pEmnemyNext = spEnemyHead;
	spEnemyHead  = this;
}


EnemyPlane::~EnemyPlane(void)
{
	CEP_nEnemyCount--;
	if (spEnemyHead == this)
	{
		spEnemyHead = this->m_pEmnemyNext;
	}
	else
	{
		EnemyPlane* temp = spEnemyHead;
		for(;temp->m_pEmnemyNext!=NULL;temp=temp->m_pEmnemyNext)
		{
			if(temp->m_pEmnemyNext==this)
			{
				temp->m_pEmnemyNext = this->m_pEmnemyNext;
				return;
			}
		}
	}
}
bool IfBoss = false;
void EnemyPlane::CreateEnemy()
{
	float tD = GameControler::GetInstance()->GetElapsedTime();
	CEP_fLastCreateTime += tD;
	CEP_fLastCreateBomberPlaneTime += tD;

	if (IfBoss)
	{
		if (CEP_nEnemyCount < 2)
		{
			if (rand() % 10 > 8)
			{
				new EnemyTrackerPlane();
			}
			new EnemyPlane((EnemyType)(CEP_nEnemyCount % 5));
		}
		CEP_fLastCreateTime -= 0.5f;
	}
	else if (UserPlane::GetScore() > 500)
	{		
		PlaySound(TEXT("小提琴.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //BOSS出现时播放音乐
		new BigBoss;

		IfBoss = true;
	
	}


	else if (CEP_fLastCreateTime > 0.3f)//0.5秒产生一架敌机
	{
		if (CEP_nEnemyCount < 5)
		{
			if (rand() % 10 > 7)
			{
				
				new EnemyTrackerPlane();
			}
			new EnemyPlane((EnemyType)(CEP_nEnemyCount % 5));
		}
		CEP_fLastCreateTime -= 0.5f;
	}
}

int EnemyPlane::GetEnemyPlaneX()
{
	if (NULL != spEnemyHead)
	{
		return spEnemyHead->CBS_nX;
	}
}

int EnemyPlane::GetWidth()
{
	if (NULL != spEnemyHead)
	{
		return spEnemyHead->CBS_nWidth;
	}
}

void EnemyPlane::FreeBitmap()
{
	for(int i = 0; i < 9; ++i)
	{
		CEP_pPhotoEnemy[i]->FreeBitmap();
	}
}

void EnemyPlane::LoadBimap()
{
	for(int i = 0; i < 9; ++i)
	{
		CEP_pPhotoEnemy[i] = new Photo();
	}
	CEP_pPhotoHP = new Photo();
	CEP_pPhotoHPSide = new Photo();
	CEP_pPhotoEnemy[0]->LoadBitmap(_T("Resource\\Enemy0.bmp"), RGB(255, 255, 255));
	CEP_pPhotoEnemy[1]->LoadBitmap(_T("Resource\\Enemy1.bmp"), RGB(255, 255, 255));
	CEP_pPhotoEnemy[2]->LoadBitmap(_T("Resource\\Enemy2.bmp"), RGB(255, 255, 255));
	CEP_pPhotoEnemy[3]->LoadBitmap(_T("Resource\\Enemy3.bmp"), RGB(255, 0, 255));
	CEP_pPhotoEnemy[4]->LoadBitmap(_T("Resource\\Enemy4.bmp"), RGB(255, 255, 255));
	CEP_pPhotoEnemy[5]->LoadBitmap(_T("Resource\\BOSS.bmp"), RGB(0,0,0));
	CEP_pPhotoEnemy[6]->LoadBitmap(_T("Resource\\d_1.bmp"), RGB(0, 0, 0));
	CEP_pPhotoEnemy[7]->LoadBitmap(_T("Resource\\d_2.bmp"), RGB(0, 0, 0));
	CEP_pPhotoEnemy[8]->LoadBitmap(_T("Resource\\d_3.bmp"), RGB(0, 0, 0));
	CEP_pPhotoHP->LoadBitmap(_T("Resource\\EnemyHPBar.bmp"), RGB(255, 0, 255));
	CEP_pPhotoHPSide->LoadBitmap(_T("Resource\\EnemyHPBarSide.bmp"), RGB(255, 0, 255));
}

bool EnemyPlane::IsVisible()
{
	if(CBS_nX < - CBS_nWidth	||
	   CBS_nX > SCREEN_WIDTH + CBS_nWidth	||
	   CBS_nY < -CBS_nHeight	||
	   CBS_nY > SCREEN_HEIGHT + CBS_nHeight)
	{
		CBS_bIsVisible = false;
		return false;
	}
	return CBS_bIsVisible;
}

void EnemyPlane::Update()
{
	float tD = GameControler::GetInstance()->GetElapsedTime();
	CEP_fAllTime += tD;
	if ((rand() % 10 > 5)&&(CEP_fAllTime > 3.0))
	{
		CEP_fAllTime = 0.0;
		CBS_fAngle = PI * (rand() % 180) / 180;
	}
	

	float tX = tD * cos((double)CBS_fAngle)*CBS_nSpeed;
	float tY = tD * sin((double)CBS_fAngle)*CBS_nSpeed;
	CBS_nX += tX;
	CBS_nY += tY;

	CEP_fFireTime -= tD;
	if (CEP_fFireTime <= 0.0f)
	{
		CEP_fFireTime = 1.0f;
		if(rand()%10 > 7&&(CBS_nY<=SCREEN_HEIGHT/4))
		{
			EnemyPlane::CircleBullet(CBS_nX + CBS_nWidth / 2 - 8, CBS_nY + CBS_nHeight, (BulletType)(CEP_nEnemyType % 4));
		}
		if (rand() % 10 > 7)
		{
			new TrackerBullet(CBS_nX + CBS_nWidth / 2 - 8, CBS_nY + CBS_nHeight, (BulletType)(CEP_nEnemyType % 7), 17.0 * PI / 36.0);
		}
		new EnemyBullet(CBS_nX + CBS_nWidth / 2 - 8, CBS_nY + CBS_nHeight, (BulletType)(CEP_nEnemyType % 7), 17.0 * PI / 36.0);
	}

	if (UserPlane::GetInstance()->CheckCollision(CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight, 20) && CEP_nEnemyType != BOSS&& CEP_nEnemyType != BIGBOSS)
	{
		CBS_bIsVisible = false;
		UserPlane::AddScore(this->CBS_nScore);

		if ((rand() % 10) > 6)
		{
			new Gift(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, (GiftType)(rand() % 4));
		}
		new Explosion(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, PLANEBLAST);

		return;
	}
}

void EnemyPlane::Render(HDC hDC)
{
	
	if (CEP_nEnemyType == BIGBOSS)
	{
		CEP_pPhotoHP->DrawBitmap(hDC, CBS_nX + (CBS_nWidth - 50) / 2, CBS_nY, CEP_nHP * 51 / 1000, 5,
			0, 0);
		switch (BigBoss::bossstatus)
		{
		case 1:
			CEP_pPhotoEnemy[CEP_nEnemyType]->DrawBitmap(hDC, CBS_nX, CBS_nY,
				CBS_nWidth, CBS_nHeight, CBS_nFrameStartX, 0);
			CEP_pPhotoEnemy[7]->DrawBitmap(hDC, CBS_nX - 60, CBS_nY,
				62, 130, CBS_nFrameStartX, 0);
			CEP_pPhotoEnemy[7]->DrawBitmap(hDC, CBS_nX + 93, CBS_nY,
				62, 130, CBS_nFrameStartX, 0);
			break;
		case 2:
			CEP_pPhotoEnemy[CEP_nEnemyType]->DrawBitmap(hDC, CBS_nX, CBS_nY,
				CBS_nWidth, CBS_nHeight, CBS_nFrameStartX, 0);
			break;
		case 3:
			CEP_pPhotoEnemy[8]->DrawBitmap(hDC, CBS_nX, CBS_nY,
				CBS_nWidth, CBS_nHeight, CBS_nFrameStartX, 0);
			break;
		default:
			break;
		}
	}
	else
	{
		CEP_pPhotoHP->DrawBitmap(hDC, CBS_nX + (CBS_nWidth - 50) / 2, CBS_nY , CEP_nHP*(51 / CEP_nWholeHP), 5,
		0, 0);
		CEP_pPhotoEnemy[CEP_nEnemyType]->DrawBitmap(hDC, CBS_nX, CBS_nY,
			CBS_nWidth, CBS_nHeight, CBS_nFrameStartX, 0);
	}
	
	CEP_pPhotoHPSide->DrawBitmap(hDC, CBS_nX + (CBS_nWidth - 51) / 2, CBS_nY , 51, 6,
		0, 0);
}

bool EnemyPlane::CheckCollision(int x, int y, int width, int height, int power)
{
	int Xa3 = CBS_nX + CBS_nWidth / 2;
	int Ya3 = CBS_nY + CBS_nHeight / 2;
	int Xb3 = x + width / 2;
	int Yb3 = y + height / 2;

	//由于图片的尺寸问题，稍微调整
	if ( (abs( Xb3 - Xa3 ) + CBS_nWidth / 5) <= (CBS_nWidth + width)/2 &&
		( abs( Yb3 - Ya3 ) + CBS_nHeight / 5) <= (CBS_nHeight + height)/2)
	{
		CEP_nHP -= power;
		if (CEP_nHP <= 0)
		{
			CBS_bIsVisible = false;
			if (CEP_nEnemyType == BIGBOSS)
				win = 1;
			UserPlane::AddScore(this->CBS_nScore);
			if ((rand() % 10) > 6)
			{
				new Gift(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, (GiftType)(rand() % 4));
			}
			new Explosion(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, PLANEBLAST);
		}
		return true;
	}
	return false;
}

void EnemyPlane::CircleBullet(int x, int y, BulletType bulletType)
{
	for (int i = 0; i < 10; i++)
	{
		new EnemyBullet(x, y, bulletType, i*(2 * PI / 10));
	}
}