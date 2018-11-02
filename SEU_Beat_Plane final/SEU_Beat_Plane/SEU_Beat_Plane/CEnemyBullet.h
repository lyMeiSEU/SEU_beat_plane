#pragma once

#include "CBullet.h"

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(int x, int y, BulletType bulletType, float angle);
	virtual ~EnemyBullet(void);

	//��Ⱦ
	void Render(HDC hDC);

	//���¾��麯����λ�ã��Ƕȵ����ԣ�
	void Update();

	bool IsVisible();
private:
	float CEB_fTIme;
};

