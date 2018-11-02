#include "stdafx.h"
#include "CTrackerBullet.h"
#include "CGameControler.h"
#include <cmath>
#include"CExplosion.h"
#include"CUserPlane.h"
#include "CUserBullet.h"

TrackerBullet * TrackerBullet::CTB_pBullet=NULL;

TrackerBullet * TrackerBullet::GetInstance()
{
	if (NULL == CTB_pBullet)
	{
		CTB_pBullet = new TrackerBullet(SCREEN_WIDTH / 2 - 24, 350, (BulletType)(rand() % 7), PI / 2);
	}
	return CTB_pBullet;
}

TrackerBullet::TrackerBullet(int x, int y,BulletType bullettype, float angle):EnemyBullet(x, y, bullettype, angle)
{
	CBS_nSpeed = 6;
	CETBl_fTime = 0.0;
}


TrackerBullet::~TrackerBullet()
{
}

void TrackerBullet::Update()
{
	float tD = GameControler::GetInstance()->GetElapsedTime();
	CETBl_fTime += tD;
	float fDis = tD * CBS_nSpeed;
	int nStartX = 0, nStartY = 0;
	double NowAngelCos = abs(CBS_nX - UserPlane::GetUserX()+ CBS_nWidth / 5)/
		sqrt(abs(CBS_nX - UserPlane::GetUserX()+CBS_nWidth / 5)*abs(CBS_nX - UserPlane::GetUserX() + CBS_nWidth / 5)
		+abs(CBS_nY-UserPlane::GetUserY()+CBS_nHeight / 5)*abs(CBS_nY - UserPlane::GetUserY()+CBS_nHeight / 5));
	double NowAngelSin = sqrt(1 - NowAngelCos * NowAngelCos);
	if(UserPlane::GetUserX() > CBS_nX + CBS_nWidth / 5)
	{
		CBS_nX += CBS_nSpeed * NowAngelCos;
	}
	else 
	{
		CBS_nX -= CBS_nSpeed * NowAngelCos;
	}
	if (UserPlane::GetUserY () > CBS_nY+CBS_nHeight / 5)
	{
		CBS_nY += CBS_nSpeed * NowAngelSin;
	}
	else
	{
		CBS_nY -= CBS_nSpeed * NowAngelSin;
	}

	CBS_nFrameStartX = CBS_nCurrentFrame * CBS_nWidth;
	++CBS_nCurrentFrame;
	CBS_nCurrentFrame %= CBS_nFrameCount;

	if (CETBl_fTime > 2.0)
	{
		CBS_bIsVisible = false;
		CETBl_fTime = 0.0;
	}
	if (UserBullet::GetInstance()->CheckCollision(CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight))
	{
		CBS_bIsVisible = false;
		new Explosion(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, BULLETBLAST);
	}

	if (UserPlane::GetInstance()->CheckCollision(CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight, CBl_nPower))
	{
		CBS_bIsVisible = false;
		new Explosion(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, BULLETBLAST);
	}
}

