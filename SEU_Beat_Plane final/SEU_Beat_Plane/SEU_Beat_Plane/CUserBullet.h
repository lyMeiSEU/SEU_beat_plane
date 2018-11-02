#pragma once

#include "CBullet.h"

class UserBullet : public Bullet
{
public:
	static UserBullet * GetInstance();

	UserBullet(int x, int y, BulletType bulletType, float angle);
	virtual ~UserBullet(void);

	//��Ⱦ
	void Render(HDC hDC);

	//���¾��麯����λ�ã��Ƕȵ����ԣ�
	void Update();

	bool IfVisible();
	static bool CheckCollision(int x, int y, int width, int height);
protected:
	static UserBullet * CUB_pBullet;

	int CUB_nFrameStartY;
};

