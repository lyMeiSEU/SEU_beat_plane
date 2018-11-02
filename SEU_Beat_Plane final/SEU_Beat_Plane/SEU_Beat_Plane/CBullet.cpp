#include "StdAfx.h"
#include "CBullet.h"

Photo * Bullet::CBl_pPictureAmmo[10] = {0};

Bullet::Bullet(int x, int y):Base_Sprite(x, y)
{
}


Bullet::~Bullet(void)
{
	
}

void Bullet::FreeBullet()
{
	for(int i = 0; i < 10; ++i)
	{
		CBl_pPictureAmmo[i]->FreeBitmap();
	}
}

void Bullet::LoadBullet()
{
	for(int i = 0; i < 10; ++i)
	{
		CBl_pPictureAmmo[i] = new Photo();
	}
	CBl_pPictureAmmo[0]->LoadBitmap(_T("Resource\\Ammo0.bmp"), RGB(255, 0, 255));
	CBl_pPictureAmmo[1]->LoadBitmap(_T("Resource\\Ammo1.bmp"), RGB(255, 0, 255));
	CBl_pPictureAmmo[2]->LoadBitmap(_T("Resource\\Ammo2.bmp"), RGB(255, 0, 255));
	CBl_pPictureAmmo[3]->LoadBitmap(_T("Resource\\Ammo3.bmp"), RGB(255, 0, 255));
	CBl_pPictureAmmo[4]->LoadBitmap(_T("Resource\\Ammo4.bmp"), RGB(0, 0, 0));
	CBl_pPictureAmmo[5]->LoadBitmap(_T("Resource\\Ammo5.bmp"), RGB(0, 0, 0));
	CBl_pPictureAmmo[6]->LoadBitmap(_T("Resource\\Ammo6.bmp"), RGB(255, 0, 255));
	CBl_pPictureAmmo[7]->LoadBitmap(_T("Resource\\redray1.bmp"), RGB(0, 0, 0));
	CBl_pPictureAmmo[8]->LoadBitmap(_T("Resource\\Ammo8.bmp"), RGB(0, 0, 0));
	CBl_pPictureAmmo[9]->LoadBitmap(_T("Resource\\WholeFried.bmp"), RGB(0, 248, 0));
}
