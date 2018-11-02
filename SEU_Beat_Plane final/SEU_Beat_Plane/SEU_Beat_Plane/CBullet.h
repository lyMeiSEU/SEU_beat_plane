#pragma once
#include "CBase_Spriet.h"
#include "CPhoto.h"

class Bullet : public Base_Sprite
{
public:
	Bullet(int x, int y);
	virtual ~Bullet(void);

	//渲染
	virtual void Render(HDC hdc) = 0;

	//更新精灵函数（位置，角度等属性）
	virtual void Update() = 0;

	static void LoadBullet();
	static void FreeBullet();
protected:
	int					CBl_nPower;//火力
	BulletType			CBl_nBulletType;
	static Photo *	CBl_pPictureAmmo[10];
};

