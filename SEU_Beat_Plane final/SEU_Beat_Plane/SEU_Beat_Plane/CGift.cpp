#include "stdafx.h"
#include "CGift.h"
#include <math.h>
#include "CGameControler.h"
#include "CUserPlane.h"
#include "CBase_Spriet.h"

Photo * Gift::CGf_pPictureGift[4] = { 0 };

Gift::Gift(int x, int y,GiftType gifttype) :Base_Sprite(x, y)
{
	CBS_nSpeed = 60 * (rand() % 10) / 10 + 30;
	CBS_fAngle = ((rand() % 360 / 180) * PI) + (PI / 16);
	CBS_nFrameStartX = 0;
	CBS_nCurrentFrame = 0;
	
	CGf_nGiftType = gifttype;
	switch (gifttype)
	{
	case SPEEDUP:
		CBS_nWidth = 40;
		CBS_nHeight = 38;
		CBS_nFrameCount = 1;
		break;
	case ADDBLOOD:
		CBS_nWidth = 40;
		CBS_nHeight = 37;
		CBS_nFrameCount = 1;
		break;
	case ADDLIFE:
		CBS_nWidth = 40;
		CBS_nHeight = 38;
		CBS_nFrameCount = 1;
		break;
	case ADDFIREALL:
		CBS_nWidth = 40;
		CBS_nHeight = 37;
		CBS_nFrameCount = 1;
		break;
	}
}


Gift::~Gift(void)
{

}

void Gift::Render(HDC hDC)
{
	CGf_pPictureGift[CGf_nGiftType]->DrawBitmap(hDC, CBS_nX, CBS_nY,
		CBS_nWidth, CBS_nHeight, CBS_nFrameStartX, 0);
}

void Gift::Update()
{
	float tD = GameControler::GetInstance()->GetElapsedTime();
	float fDis = tD * CBS_nSpeed;
	int nStartX = 0, nStartY = 0;

	CBS_nX += cos(CBS_fAngle) * fDis;
	CBS_nY += sin(CBS_fAngle) * fDis;

	CBS_nFrameStartX = CBS_nCurrentFrame * CBS_nWidth;
	++CBS_nCurrentFrame;
	CBS_nCurrentFrame %= CBS_nFrameCount;

	if (UserPlane::GetInstance()->CheckGift(CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight, CGf_nGiftType))
	{
		CBS_bIsVisible = false;
	}
}

void Gift::FreeImage()
{
	for (int i = 0; i < 4; ++i)
	{
		CGf_pPictureGift[i]->FreeBitmap();
	}
}

void Gift::LoadImage()
{
	for (int i = 0; i < 4; ++i)
	{
		CGf_pPictureGift[i] = new Photo();
	}
	CGf_pPictureGift[0]->LoadBitmap(_T("Resource\\speed.bmp"), RGB(102, 102, 100));
	CGf_pPictureGift[1]->LoadBitmap(_T("Resource\\blood.bmp"), RGB(102, 102, 100));
	CGf_pPictureGift[2]->LoadBitmap(_T("Resource\\addlife.bmp"), RGB(102, 102, 100));
	CGf_pPictureGift[3]->LoadBitmap(_T("Resource\\boom.bmp"), RGB(102, 102, 100));
}

bool Gift::IsVisible()
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