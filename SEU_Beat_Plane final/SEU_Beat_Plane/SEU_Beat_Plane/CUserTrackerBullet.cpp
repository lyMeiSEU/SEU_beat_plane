#include "stdafx.h"
#include "CUserTrackerBullet.h"
#include"CEnemyPlane.h"
#include"CExplosion.h"
#include<cmath>
#include "CGameControler.h"


UserTrackerBullet::UserTrackerBullet(int x, int y, BulletType bulletType, float angle) :UserBullet(x, y, bulletType, angle)
{
	CUTB_bIfShoot = false;
	CBl_nPower = 30;
}


UserTrackerBullet::~UserTrackerBullet()
{
}

void UserTrackerBullet::Update()
{
	if (CBl_nBulletType == WHOLEFRIED)
	{
		int row = CBS_nCurrentFrame / 3;
		int col = CBS_nCurrentFrame % 3;
		CBS_nFrameStartX = col * 1080 + col / 1;
		CUB_nFrameStartY = row * 640 + (row + 1) / 1;
		CBS_nCurrentFrame++;
		return;
	}
	float fDis = CBS_nSpeed;
	int nStartX = 0, nStartY = 0;
	float tD = GameControler::GetInstance()->GetElapsedTime();
	EnemyPlane * temp = EnemyPlane::spEnemyHead;

	if (temp->GetEnemyPlaneX()  +temp->GetWidth()/ 2> this->CBS_nX && !CUTB_bIfShoot)
	{
		CBS_nX += 800 * tD;
	}
	else if (temp->GetEnemyPlaneX() + temp->GetWidth() / 2 < this->CBS_nX && !CUTB_bIfShoot)
	{
		CBS_nX -= 800 * tD;
	}
	else
	{
		CUTB_bIfShoot = true;
		CBS_nY -= 2000 * tD;
	}

	CBS_nFrameStartX = CBS_nCurrentFrame * CBS_nWidth;
	++CBS_nCurrentFrame;
	CBS_nCurrentFrame %= CBS_nFrameCount;


	for (; temp != NULL; temp = temp->m_pEmnemyNext)
	{
		if (temp->CheckCollision(CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight, CBl_nPower))
		{
			CBS_bIsVisible = false;
			new Explosion(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, BULLETBLAST);
			break;
		}
	}
}
