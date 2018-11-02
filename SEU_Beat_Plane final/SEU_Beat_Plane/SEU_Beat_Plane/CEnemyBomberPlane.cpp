#include "stdafx.h"
#include "CEnemyBomberPlane.h"
#include "CGameControler.h"
#include "CEnemyBullet.h"
#include "CExplosion.h"
#include "CGift.h"
#include "CUserPlane.h"
#include <math.h>

EnemyBomberPlane::EnemyBomberPlane() :EnemyPlane(ENEMY4)
{

}

EnemyBomberPlane::EnemyBomberPlane(int x,int y):EnemyPlane(ENEMY4)
{
	CBS_nX = x;
	CBS_nY = y;
}


EnemyBomberPlane::~EnemyBomberPlane()
{

}

void EnemyBomberPlane::Update()
{
	float tD = GameControler::GetInstance()->GetElapsedTime();
	CEBP_fTime += tD;
	CBS_nSpeed = 3;

	int nStartX = 0, nStartY = 0;
	double NowAngelCos = abs(CBS_nX - UserPlane::GetUserX() + CBS_nWidth / 5) /
		sqrt(abs(CBS_nX - UserPlane::GetUserX() + CBS_nWidth / 5)*abs(CBS_nX - UserPlane::GetUserX() + CBS_nWidth / 5)
			+ abs(CBS_nY - UserPlane::GetUserY() + CBS_nHeight / 5)*abs(CBS_nY - UserPlane::GetUserY() + CBS_nHeight / 5));
	double NowAngelSin = sqrt(1 - NowAngelCos * NowAngelCos);
	if (UserPlane::GetUserX() > CBS_nX + CBS_nWidth / 5)
	{
		CBS_nX += CBS_nSpeed * NowAngelCos;
	}
	else
	{
		CBS_nX -= CBS_nSpeed * NowAngelCos;
	}
	if (UserPlane::GetUserY() > CBS_nY + CBS_nHeight / 5)
	{
		CBS_nY += CBS_nSpeed * NowAngelSin;
	}
	else
	{
		CBS_nY -= CBS_nSpeed * NowAngelSin;
	}

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
