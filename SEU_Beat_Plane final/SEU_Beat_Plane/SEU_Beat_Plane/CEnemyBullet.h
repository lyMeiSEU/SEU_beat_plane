#pragma once

#include "CBullet.h"

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(int x, int y, BulletType bulletType, float angle);
	virtual ~EnemyBullet(void);

	//渲染
	void Render(HDC hDC);

	//更新精灵函数（位置，角度等属性）
	void Update();

	bool IsVisible();
private:
	float CEB_fTIme;
};

