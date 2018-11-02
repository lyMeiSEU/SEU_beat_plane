#include "StdAfx.h"
#include "CExplosion.h"

Photo * Explosion::CEP_pPictureBlast[2] = {0};

Explosion::Explosion(int x, int y, BlastType blastType):Base_Sprite(x, y),
	CEP_nBlastType(blastType)
{
	CBS_nFrameStartX = 0;
	CBS_nCurrentFrame = 0;
	switch(blastType)
	{
	case BULLETBLAST:
		CBS_nWidth = 32;
		CBS_nHeight = 32;
		CBS_nFrameCount = 5;
		break;
	case PLANEBLAST:
		CBS_nWidth = 65;
		CBS_nHeight = 75;
		CBS_nFrameCount = 12;
		break;	
	}
}


Explosion::~Explosion(void)
{
	
}

void Explosion::FreeImage()
{
	for (int i = 0; i < 2; ++i)
	{
		CEP_pPictureBlast[i]->FreeBitmap();
	}
}

void Explosion::LoadImage()
{
	for (int i = 0; i < 2; ++i)
	{
		CEP_pPictureBlast[i] = new Photo();
	}

	CEP_pPictureBlast[0]->LoadBitmap(_T("Resource\\BulletBlast.bmp"), RGB(255, 0, 255));
	CEP_pPictureBlast[1]->LoadBitmap(_T("Resource\\PlaneBlast.bmp"), RGB(0, 0, 0));
}

void Explosion::Update()
{
	if (CBS_nCurrentFrame >= CBS_nFrameCount)
	{
		CBS_bIsVisible = false;
	}
	CBS_nFrameStartX = CBS_nCurrentFrame * CBS_nWidth;
	CBS_nCurrentFrame++;
}

void Explosion::Render(HDC hDC)
{
	CEP_pPictureBlast[CEP_nBlastType]->DrawBitmap(hDC, CBS_nX - CBS_nWidth/2, CBS_nY - CBS_nHeight / 2,
		CBS_nWidth, CBS_nHeight, CBS_nFrameStartX, 0);
}