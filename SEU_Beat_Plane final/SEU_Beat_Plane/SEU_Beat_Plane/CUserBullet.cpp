#include "StdAfx.h"
#include "CUserBullet.h"
#include <math.h>
#include "CEnemyPlane.h"
#include "CExplosion.h"
#include "CTrackerBullet.h"
#include "CUserPlane.h"

UserBullet * UserBullet::CUB_pBullet = NULL;

UserBullet * UserBullet::GetInstance()
{
	if (NULL == CUB_pBullet)
	{
		CUB_pBullet = new UserBullet(SCREEN_WIDTH / 2 - 24, 350, (BulletType)(rand() % 7), PI / 2);
	}
	return CUB_pBullet;
}

UserBullet::UserBullet(int x, int y, BulletType bulletType, float angle):Bullet(x, y)
{
	CBS_nSpeed = 10;
	CBl_nPower = 3;
	CBl_nBulletType = bulletType;
	CBS_fAngle = angle;
	CBS_nCurrentFrame = 0;
	CBS_nFrameStartX = 0;
	CUB_nFrameStartY = 0;
	switch(bulletType)
	{
	case AMMO0:
		CBS_nWidth = 11;
		CBS_nHeight = 11;
		CBS_nFrameCount = 1;
		CBl_nPower = 1;
		break;
	case AMMO1:
		CBS_nWidth = 16;
		CBS_nHeight = 16;
		CBS_nFrameCount = 6;
		CBl_nPower = 2;
		break;
	case AMMO2:
		CBS_nWidth = 16;
		CBS_nHeight = 16;
		CBS_nFrameCount = 6;
		CBl_nPower = 3;
		break;
	case AMMO3:
		CBS_nWidth = 16;
		CBS_nHeight = 16;
		CBS_nFrameCount = 8;
		CBl_nPower = 4;
		break;
	case AMMO4:
		CBS_nWidth = 26;
		CBS_nHeight = 31;
		CBS_nFrameCount = 3;
		CBl_nPower = 7;
		break;
		
	case AMMO5:
		CBS_nWidth = 23;
		CBS_nHeight = 49;
		CBS_nFrameCount = 1;
		CBl_nPower = 6;
		break;
	case AMMO6:
		
		CBS_nWidth = 12;
		CBS_nHeight = 60;
		CBS_nFrameCount = 5;
		CBl_nPower = 5;
		break;
	case WHOLEFRIED:
		CBS_nWidth = 224;
		CBS_nHeight = 320;
		CBS_nFrameCount = 12;
		break;
	}
}


UserBullet::~UserBullet(void)
{
}

bool UserBullet::IfVisible()
{
	if (CBl_nBulletType == WHOLEFRIED)
	{
		if (CBS_nCurrentFrame > 11)
		{
			return false;
		}
		return true;
	}
	if(CBS_bIsVisible==false)
	{
		return CBS_bIsVisible;
	}
	if(CBS_nX < -50	||
	   CBS_nY < -50	||
	   CBS_nX > SCREEN_WIDTH+50	||
	   CBS_nY > SCREEN_HEIGHT+50)
	{
		return false;
	}
	return true;
}

void UserBullet::Render(HDC hDC)
{
	CBl_pPictureAmmo[CBl_nBulletType]->DrawBitmap(hDC, CBS_nX, CBS_nY,
		CBS_nWidth, CBS_nHeight, CBS_nFrameStartX, CUB_nFrameStartY);
}

void UserBullet::Update()
{
	
	if (CBl_nBulletType == WHOLEFRIED)
	{
		int row = CBS_nCurrentFrame / 3;
		int col = CBS_nCurrentFrame % 3;
		CBS_nFrameStartX = col*1080 + col/1;
		CUB_nFrameStartY = row*640 + (row+1)/1;
		CBS_nCurrentFrame++;
		return;
	}
	float fDis = CBS_nSpeed;
	int nStartX = 0, nStartY = 0;

	CBS_nX += cos(CBS_fAngle) * fDis;
	CBS_nY += sin(CBS_fAngle) * fDis;

	CBS_nFrameStartX = CBS_nCurrentFrame * CBS_nWidth;
	++CBS_nCurrentFrame;
	CBS_nCurrentFrame %= CBS_nFrameCount;

	EnemyPlane* temp = EnemyPlane::spEnemyHead;
	for(;temp!=NULL;temp=temp->m_pEmnemyNext)
	{
		if(temp->CheckCollision(CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight, CBl_nPower))
		{
			CBS_bIsVisible = false;
			new Explosion(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, BULLETBLAST);
			break;
		}
	}
}

bool UserBullet::CheckCollision(int x, int y, int width, int height)
{
	int Xa3 = CUB_pBullet->CBS_nX + CUB_pBullet->CBS_nWidth / 2;
	int Ya3 = CUB_pBullet->CBS_nY + CUB_pBullet->CBS_nHeight / 2;
	int Xb3 = x + width / 2;
	int Yb3 = y + height / 2;

	//由于图片的尺寸问题，稍微调整
	if ((abs(CUB_pBullet->CBS_nX-x)) <= 3 * (CUB_pBullet->CBS_nWidth + width) / 4  &&
		(abs(CUB_pBullet->CBS_nY-y)) <= 3 * (CUB_pBullet->CBS_nHeight + height) / 4 )
	{
		return true;
	}
	return false;
}