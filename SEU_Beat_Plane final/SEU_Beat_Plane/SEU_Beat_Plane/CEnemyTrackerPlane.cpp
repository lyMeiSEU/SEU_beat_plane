#include "stdafx.h"
#include "CEnemyTrackerPlane.h"
#include "CEnemyPlane.h"
#include "CGameControler.h"
#include "CEnemyBullet.h"
#include "CExplosion.h"
#include "CGift.h"
#include "CUserPlane.h"


EnemyTrackerPlane::EnemyTrackerPlane():EnemyPlane(ENEMY4)
{
	
}


EnemyTrackerPlane::~EnemyTrackerPlane()
{

}

void EnemyTrackerPlane::Update()
{
	float tD = GameControler::GetInstance()->GetElapsedTime();
	float fDis = tD * CBS_nSpeed;
	int XSpeed = 100;
	if (UserPlane::GetUserX() > this->CBS_nX)
	{
		CBS_nX += XSpeed * tD;
		CBS_nSpeed = 100;
	}
	else if(UserPlane::GetUserX() < this->CBS_nX)
	{
		CBS_nX -= XSpeed * tD;
		CBS_nSpeed = 100;
	}
	else
	{
		CBS_nSpeed = 0;
	}

	CBS_nY += fDis;

	CEP_fFireTime -= tD;
	if (CEP_fFireTime <= 0.0f)
	{
		CEP_fFireTime = 1.0f;
		new EnemyBullet(CBS_nX + CBS_nWidth / 2 - 8, CBS_nY + CBS_nHeight, (BulletType)(CEP_nEnemyType % 4), 17.0 * PI / 36.0);
	}

	if (UserPlane::GetInstance()->CheckCollision(CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight, 20))
	{
		CBS_bIsVisible = false;
		if ((rand() % 10) > 6)
		{
			new Gift(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, (GiftType)(rand() % 4));
		}
		new Explosion(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, PLANEBLAST);
		return;
	}

}
