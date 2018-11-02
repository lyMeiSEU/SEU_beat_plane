#pragma once

#include "CBullet.h"

class UserBullet : public Bullet
{
public:
	static UserBullet * GetInstance();

	UserBullet(int x, int y, BulletType bulletType, float angle);
	virtual ~UserBullet(void);

	//渲染
	void Render(HDC hDC);

	//更新精灵函数（位置，角度等属性）
	void Update();

	bool IfVisible();
	static bool CheckCollision(int x, int y, int width, int height);
protected:
	static UserBullet * CUB_pBullet;

	int CUB_nFrameStartY;
};

