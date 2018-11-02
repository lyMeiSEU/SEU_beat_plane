#pragma once
#include "CBase_Spriet.h"
#include "CPhoto.h"

class Bullet : public Base_Sprite
{
public:
	Bullet(int x, int y);
	virtual ~Bullet(void);

	//��Ⱦ
	virtual void Render(HDC hdc) = 0;

	//���¾��麯����λ�ã��Ƕȵ����ԣ�
	virtual void Update() = 0;

	static void LoadBullet();
	static void FreeBullet();
protected:
	int					CBl_nPower;//����
	BulletType			CBl_nBulletType;
	static Photo *	CBl_pPictureAmmo[10];
};

