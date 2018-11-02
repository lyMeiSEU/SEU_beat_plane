
#include "StdAfx.h"
#include "CUserPlane.h"
#include "CGameControler.h"
#include <math.h>
#include "CUserBullet.h"
#include "CEnemyPlane.h"
#include "CUserTrackerBullet.h"
#include<Windows.h>

int UserPlane::chosefighter = 1;
UserPlane * UserPlane::CUP_pCUserPlane = NULL;
Photo * UserPlane::CUP_pPhotoLife = NULL;
Photo * UserPlane::CUP_pPhotoPlane1 = NULL;
Photo * UserPlane::CUP_pPhotoPlane2 = NULL;

Photo * UserPlane::CUP_pPhotoHP = NULL;
Photo * UserPlane::CUP_pPhotoHPSide = NULL;
Photo * UserPlane::CUP_pPhotoScore = NULL;
Photo * UserPlane::CUP_pPhotoScore0_4 = NULL;
Photo * UserPlane::CUP_pPhotoScore5_9 = NULL;
Photo * UserPlane::CUP_pPhotoWholeFiredNumber = NULL;
bool UserPlane::CUP_bGameOver = false;

UserPlane * UserPlane::GetInstance()
{
	if (NULL == CUP_pCUserPlane)
	{
		CUP_pCUserPlane = new UserPlane(SCREEN_WIDTH/2 - 24, 350);
	}
	return CUP_pCUserPlane;
}

UserPlane::UserPlane(int x, int y):Base_Sprite(x, y)
{
	CUP_nLife = 5;
	CUP_nAmmoCount = 1;
	CUP_nBulletType = AMMO0;
	CUP_nAction = STOP_MOVE;
	
	CBS_nScore = 0;
	switch (chosefighter)
	{
	case 1:
		CBS_nWidth = 49;
		CBS_nHeight = 69;
		CBS_nSpeed = 350;
	case 2:
		CBS_nWidth = 76;
		CBS_nHeight = 58;
		CBS_nSpeed = 350;
	default:
		break;
	}
	
	InitPlane();
}

void UserPlane::InitPlane()
{
	CUP_bIsStopMove = true;
	CUP_nHP = 100;	
	CBS_nX = SCREEN_WIDTH/2 - 24;
	CBS_nY = 480;
	CUP_fBulletFrequency = 0.2;//每秒发射5次子弹
	CUP_fFrequencyTime = 0.0f;
	CUP_fTrackerBulletFrequnecy = 0.0f;
	CUP_fInvincibletime = 1.0;
	CUP_bUnDead = true;
	CUP_bFire = false;
	CUP_nWholeFired = 2;
}

UserPlane::~UserPlane()
{
}

void UserPlane::LoadBimap()
{
	CUP_pPhotoPlane1 = new Photo();
	CUP_pPhotoPlane2 = new Photo();
	CUP_pPhotoLife = new Photo();
	CUP_pPhotoHP = new Photo();
	CUP_pPhotoHPSide = new Photo();
	CUP_pPhotoScore = new Photo();
	CUP_pPhotoScore0_4 = new Photo();
	CUP_pPhotoScore5_9 = new Photo();
	CUP_pPhotoWholeFiredNumber = new Photo();

	CUP_pPhotoPlane1->LoadBitmap(_T("Resource\\OurFighter.bmp"), RGB(0, 71, 157));
	CUP_pPhotoPlane2->LoadBitmap(_T("Resource\\OurFighter1.bmp"), RGB(255, 255, 255));
	CUP_pPhotoLife->LoadBitmap(_T("Resource\\Life.bmp"), RGB(255, 0, 255));

	CUP_pPhotoHP->LoadBitmap(_T("Resource\\HPBar.bmp"), RGB(255, 0, 255));
	CUP_pPhotoHPSide->LoadBitmap(_T("Resource\\HPBarSide.bmp"), RGB(255, 0, 255));

	CUP_pPhotoScore->LoadBitmap(_T("Resource\\Score.bmp"), RGB(0, 0, 0));
	CUP_pPhotoScore0_4->LoadBitmap(_T("Resource\\Score0_4.bmp"), RGB(0, 0, 0));
	CUP_pPhotoScore5_9->LoadBitmap(_T("Resource\\Score5_9.bmp"), RGB(0, 0, 0));
	CUP_pPhotoWholeFiredNumber->LoadBitmap(_T("Resource\\WholeFired.bmp"), RGB(0,0,0));

}

void UserPlane::FreeBitmap()
{
	CUP_pPhotoPlane1->FreeBitmap();
	CUP_pPhotoPlane2->FreeBitmap();
	CUP_pPhotoLife->FreeBitmap();
	CUP_pPhotoHP->FreeBitmap();
	CUP_pPhotoHPSide->FreeBitmap();
	CUP_pPhotoScore->FreeBitmap();
	CUP_pPhotoScore0_4->FreeBitmap();
	CUP_pPhotoScore5_9->FreeBitmap();
	CUP_pPhotoWholeFiredNumber->FreeBitmap();
}

void UserPlane::Update()
{
	float tD = GameControler::GetInstance()->GetElapsedTime();
	float fDis = tD * CBS_nSpeed;
	if (CBS_nScore > 500) 
	{
		CUP_nAmmoCount = 3;
	}

	if (CBS_nScore > 1000)
	{
		CUP_nAmmoCount = 5;
	}

	if (CUP_bUnDead)
	{
		if (CUP_bIsStopMove && (CBS_nY > 2 * SCREEN_HEIGHT / 3))
		{
			CBS_nY -= fDis;
		}
		
		CUP_fInvincibletime -= tD;
		if (CUP_fInvincibletime <= 0)
		{
			CUP_bUnDead = false;
			CUP_fInvincibletime = 1.0;
		}
	}

	CUP_fFrequencyTime +=tD;
	CUP_fTrackerBulletFrequnecy += tD;

	if (!CUP_bIsStopMove)
	{
		CBS_nX += cos(CBS_fAngle) * fDis;
		CBS_nY += sin(CBS_fAngle) * fDis;
		if(CBS_nX<0.0f)
			CBS_nX = 0.0f;
		if(CBS_nY<0.0f)
			CBS_nY = 0.0f;
		if(CBS_nX>SCREEN_WIDTH-CBS_nWidth)
			CBS_nX = SCREEN_WIDTH-CBS_nWidth;
		if(CBS_nY>SCREEN_HEIGHT-CBS_nHeight)
			CBS_nY = SCREEN_HEIGHT-CBS_nHeight;
	}
	
	

	if (CUP_bFire && CUP_fFrequencyTime >= CUP_fBulletFrequency)
	{
		switch(CUP_nAmmoCount)
		{
		case 1:
			new UserBullet(CBS_nX + CBS_nWidth / 2 - 8, CBS_nY - 16,
				CUP_nBulletType, float(PI * 3.0 / 2.0));
			break;
		case 3:
			new UserBullet(CBS_nX + CBS_nWidth / 2 - 16, CBS_nY - 16, CUP_nBulletType, float(17.0*PI/12.0));
			new UserBullet(CBS_nX + CBS_nWidth / 2 - 8, CBS_nY - 16, CUP_nBulletType, float(3.0*PI/2.0));
			new UserBullet(CBS_nX + CBS_nWidth / 2 , CBS_nY - 16, CUP_nBulletType, float(8.0*PI/5.0));
			if (CUP_fTrackerBulletFrequnecy > 3.0f)
			{
				new UserTrackerBullet(CBS_nX + CBS_nWidth / 2 - 24, CBS_nY - 16, AMMO5, float(17.0*PI / 12.0));
				CUP_fTrackerBulletFrequnecy -= 3.0f;
			}
			break;
		case 5:
			new UserBullet(CBS_nX + CBS_nWidth / 2 - 32, CBS_nY - 16,  AMMO6 , float(4.0*PI/3.0));
			new UserBullet(CBS_nX + CBS_nWidth / 2 - 24, CBS_nY - 16, CUP_nBulletType, float(17.0*PI/12.0));
			new UserBullet(CBS_nX + CBS_nWidth / 2 - 16, CBS_nY - 16, CUP_nBulletType, float(3.0*PI/2.0));
			new UserBullet(CBS_nX + CBS_nWidth / 2 - 8, CBS_nY - 16,  CUP_nBulletType, float(8.0*PI/5.0));
			new UserBullet(CBS_nX + CBS_nWidth / 2, CBS_nY - 16, AMMO6 , float(5.0*PI / 3.0));
			if (CUP_fTrackerBulletFrequnecy > 3.0f)
			{
				new UserTrackerBullet(CBS_nX + CBS_nWidth / 2 - 24, CBS_nY - 16, AMMO5, float(17.0*PI / 12.0));
				new UserTrackerBullet(CBS_nX + CBS_nWidth / 2 + 24, CBS_nY - 16, AMMO5, float(17.0*PI / 12.0));
				CUP_fTrackerBulletFrequnecy -= 3.0f;
			}
			break;
		}

		while(CUP_fFrequencyTime > CUP_fBulletFrequency)
		{
			CUP_fFrequencyTime -= CUP_fBulletFrequency;
		}
	}	
}

void UserPlane::Control(ActionType actionType)
{
	CUP_nAction = actionType;
	switch(actionType)
	{
	case LEFT:
		CBS_fAngle = PI;
		CUP_bIsStopMove = false;
		break;
	case RIGHT:
		CBS_fAngle = 0.0f;
		CUP_bIsStopMove = false;
		break;
	case UP:
		CBS_fAngle = 3.0f * PI / 2.0f;
		CUP_bIsStopMove = false;
		break;
	case DOWN:
		CBS_fAngle = PI / 2.0f;
		CUP_bIsStopMove = false;
		break;
	case LEFT_UP:
		CBS_fAngle = 5.0f * PI / 4.0f;
		CUP_bIsStopMove = false;
		break;
	case LEFT_DOWN:
		CBS_fAngle = 3.0f * PI / 4.0f;
		CUP_bIsStopMove = false;
		break;
	case RIGHT_UP:
		CBS_fAngle = 2.0f * PI - PI / 4.0f;
		CUP_bIsStopMove = false;
		break;
	case RIGHT_DOWN:
		CBS_fAngle = PI / 4.0f;
		CUP_bIsStopMove = false;
		break;
	case STOP_MOVE:
		CUP_bIsStopMove = true;
		break;
	case FIRE:	
		CUP_bFire = true;	
		break;
	case STOP_FIRE:
		CUP_bFire = false;
		break;
	case FIREALL:
		if (CUP_nWholeFired)
		{
			new UserBullet(0, SCREEN_HEIGHT / 2 - 320 /2, WHOLEFRIED, 0.0);
			new UserBullet(SCREEN_WIDTH/2 - 224 /2, SCREEN_HEIGHT / 2 - 320 /2, WHOLEFRIED, 0.0);
			new UserBullet(SCREEN_WIDTH - 224, SCREEN_HEIGHT / 2 - 320 /2, WHOLEFRIED, 0.0);
			EnemyPlane * temp = EnemyPlane::spEnemyHead;
			for(;temp!=NULL;temp=temp->m_pEmnemyNext)
			{
				if (temp->CEP_nEnemyType == BOSS|| temp->CEP_nEnemyType == BIGBOSS)
				{
					continue;
				}
				temp->CheckCollision(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 100);
			}
			CUP_nWholeFired--;
		}
		break;
	}
	
}

void UserPlane::Render(HDC hDC)
{
	switch (chosefighter)
	{
	case 1:
		CUP_pPhotoPlane1->DrawBitmap(hDC, CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight,
			0, 0);
		break;
	case 2:
		CUP_pPhotoPlane2->DrawBitmap(hDC, CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight,
			0, 0);
		break;
	}
	

	for (int i = 0; i < CUP_nLife; ++i)
	{
		CUP_pPhotoLife->DrawBitmap(hDC, 25 + i * 18, 10 , 18, 24,0, 0);
	}

	for (int i = 0; i < CUP_nWholeFired; i++)
	{
		CUP_pPhotoWholeFiredNumber->DrawBitmap(hDC, 25 + i * 18, 60, 18, 24, 0, 0);
	}

	CUP_pPhotoHPSide->DrawBitmap(hDC, 20 , 40 , 105, 13,0, 0);
	CUP_pPhotoHP->DrawBitmap(hDC, 22 , 42 , CUP_nHP, 9,0, 0);
	CUP_pPhotoScore->DrawBitmap(hDC, 0, 100, 50, 50, 0, 0);

	int score = CBS_nScore;
	int bestscore = BestScore;
	int count1 = 0;
	int count2 = 0;

	while (score != 0)
	{
		score /= 10;
		count1++;
	}
	while (bestscore != 0)
	{
		bestscore /= 10;
		count2++;
	}

	int dX1 = count1 * 30 + 50;
	int dX2 = count2 * 30;

	score = CBS_nScore;
	bestscore = BestScore;

	if (score == 0)
	{
		CUP_pPhotoScore0_4->DrawBitmap(hDC, dX1, 100, 30, 50, 0, 0);
	}
	if (bestscore == 0)
	{
		CUP_pPhotoScore0_4->DrawBitmap(hDC, dX2, 200, 30, 50, 0, 0);
	}

	while (score != 0)
	{
		if (score % 10 < 5)
		{
			CUP_pPhotoScore0_4->DrawBitmap(hDC, dX1, 100, 30, 50, (score % 5) * 30, 0);
		}
		else
		{
			CUP_pPhotoScore5_9->DrawBitmap(hDC, dX1, 100, 30, 49, (score % 5) * 30, 0);
		}
		dX1 -= 30;
		score /= 10;
	}
	while (bestscore != 0)
	{
		if (bestscore % 10 < 5)
		{
			CUP_pPhotoScore0_4->DrawBitmap(hDC, dX2, 200, 30, 50, (bestscore % 5) * 30, 0);
		}
		else
		{
			CUP_pPhotoScore5_9->DrawBitmap(hDC, dX2, 200, 30, 49, (bestscore % 5) * 30, 0);
		}
		dX2 -= 30;
		bestscore /= 10;
	}
}

bool UserPlane::CheckCollision(int x, int y, int width, int height, int power)
{
	if (CUP_bUnDead)
	{
		return false;
	}

	int Xa3 = CBS_nX + CBS_nWidth / 2;
	int Ya3 = CBS_nY + CBS_nHeight / 2;
	int Xb3 = x + width / 2;
	int Yb3 = y + height / 2;

	//由于图片的尺寸问题，稍微调整
	if ( (abs( Xb3 - Xa3 ) + CBS_nWidth / 5) <= (CBS_nWidth + width)/2 &&
		( abs( Yb3 - Ya3 ) + CBS_nHeight / 5) <= (CBS_nHeight + height)/2)
	{
		CUP_nHP -= power;
		if (CUP_nHP <= 0)
		{
			CUP_nLife--;
			if (CUP_nLife >= 0)
			{
				//new blast
				InitPlane();
			}
			else
			{
				CUP_bGameOver = true;
			}
		}
		return true;
	}
	return false;
}

bool UserPlane::CheckGift(int x, int y, int width, int height, GiftType gifttype)
{

	if (CUP_bUnDead)
	{
		return false;
	}
	int Xa3 = CBS_nX + CBS_nWidth / 2;
	int Ya3 = CBS_nY + CBS_nHeight / 2;
	int Xb3 = x + width / 2;
	int Yb3 = y + height / 2;

	//由于图片的尺寸问题，稍微调整
	if ((abs(Xb3 - Xa3) + CBS_nWidth / 5) <= (CBS_nWidth + width) / 2 &&
		(abs(Yb3 - Ya3) + CBS_nHeight / 5) <= (CBS_nHeight + height) / 2)
	{
		switch (gifttype)
		{
		case SPEEDUP:
			CBS_nSpeed += 20;
			break;
		case ADDBLOOD:
			CUP_nHP += 10;
			break;
		case ADDLIFE:
		{
			if (CUP_nLife < 5)
			{
				CUP_nLife++;
			}
		}
		break;
		case ADDFIREALL:
			CUP_nWholeFired++;
			break;
		}
		return true;
	}
	return false;
}

void UserPlane::AddScore(int score)
{
	CUP_pCUserPlane->CBS_nScore += score;
	switch (CUP_pCUserPlane->CBS_nScore)
	{
	case 84:
		CUP_pCUserPlane->CUP_nBulletType = AMMO1;
	case 168:
		CUP_pCUserPlane->CUP_nBulletType = AMMO2;
	case 252:
		CUP_pCUserPlane->CUP_nBulletType = AMMO3;
	case 336:
		CUP_pCUserPlane->CUP_nBulletType = AMMO4;
	case 420:
		CUP_pCUserPlane->CUP_nBulletType = AMMO5;
	case 470:
		CUP_pCUserPlane->CUP_nBulletType = AMMO6;
	case 500:
		CUP_pCUserPlane->CUP_nBulletType = AMMO0;
	case 584:
		CUP_pCUserPlane->CUP_nBulletType = AMMO1;
	case 668:
		CUP_pCUserPlane->CUP_nBulletType = AMMO2;
	case 752:
		CUP_pCUserPlane->CUP_nBulletType = AMMO3;
	case 836:
		CUP_pCUserPlane->CUP_nBulletType = AMMO4;
	case 920:
		CUP_pCUserPlane->CUP_nBulletType = AMMO5;
	case 970:
		CUP_pCUserPlane->CUP_nBulletType = AMMO6;	
	}
}

int UserPlane::GetScore()
{
	if (NULL != CUP_pCUserPlane)
	{
		return CUP_pCUserPlane->CBS_nScore;
	}
	return 0;
}