#include "StdAfx.h"
#include "CEnemyBullet.h"
#include <math.h>
#include "CGameControler.h"
#include "CUserBullet.h"
#include "CTrackerBullet.h"
#include "CUserPlane.h"
#include "CExplosion.h"

static UserPlane * CUP_pCUserPlane;

EnemyBullet::EnemyBullet(int x, int y, BulletType bulletType, float angle) :Bullet(x, y)
{
	CBS_nSpeed = 220;
	CBl_nBulletType = bulletType;
	CBS_fAngle = angle;
	CBS_nCurrentFrame = 0;
	CBS_nFrameStartX = 0;
	switch (bulletType)
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
		CBl_nPower = 5;
	break; 
	case AMMO7:
		CBS_nWidth = 45;
		CBS_nHeight = 600;
		CBS_nFrameCount = 1;
		CBl_nPower = 10;
		CBS_nSpeed = 0;
		CEB_fTIme = 1.0f;
		break;
	case AMMO8:
		CBS_nWidth = 50;
		CBS_nHeight = 50;
		CBS_nFrameCount = 1;
		CBl_nPower = 10;
		break;
	}
}


EnemyBullet::~EnemyBullet(void)
{

}

bool EnemyBullet::IsVisible()
{
	if (CBS_bIsVisible == false)
	{
		return CBS_bIsVisible;
	}
	if (CBS_nX < -50 ||
		CBS_nY < -50 ||
		CBS_nX > SCREEN_WIDTH + 50 ||
		CBS_nY > SCREEN_HEIGHT + 50)
	{
		return false;
	}
	return true;
}

void EnemyBullet::Render(HDC hDC)
{
	CBl_pPictureAmmo[CBl_nBulletType]->DrawBitmap(hDC, CBS_nX, CBS_nY,
		CBS_nWidth, CBS_nHeight, CBS_nFrameStartX, 0);
}

void EnemyBullet::Update()
{
	float tD = GameControler::GetInstance()->GetElapsedTime();
	float tDis = tD * CBS_nSpeed;

	if (CBl_nBulletType == AMMO7)
	{
		CEB_fTIme -= tD;

		if (CEB_fTIme <= 0.0f)
		{
			CBS_bIsVisible = false;
		}
	}

	if (CBl_nBulletType != AMMO7)
	{
		int nStartX = 0, nStartY = 0;
		CBS_nX += cos(CBS_fAngle) * tDis;
		CBS_nY += sin(CBS_fAngle) * tDis;

		CBS_nFrameStartX = CBS_nCurrentFrame * CBS_nWidth;
		++CBS_nCurrentFrame;
		CBS_nCurrentFrame %= CBS_nFrameCount;
	}
	if (UserPlane::GetInstance()->CheckCollision(CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight, CBl_nPower))
	{
		if (CBl_nBulletType != AMMO7)
			this->CBS_bIsVisible = false;
		new Explosion(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, BULLETBLAST);
	}
}