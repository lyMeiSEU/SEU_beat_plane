#pragma once
#include"CEnemyBullet.h"

class TrackerBullet :public EnemyBullet
{
public:
	static TrackerBullet * GetInstance();

	TrackerBullet(int x, int y, BulletType bulletType, float angle);
	virtual ~TrackerBullet();

	void Update();
protected:
	static TrackerBullet * CTB_pBullet;

	float CETBl_fTime; //¼ÆÊ±Æ÷
};

