#pragma once
#include"CUserBullet.h"
class UserTrackerBullet :
	public UserBullet
{
public:
	UserTrackerBullet(int x, int y, BulletType bulletType, float angle);
	virtual ~UserTrackerBullet();

	void Update();
	bool CUTB_bIfShoot;
};

