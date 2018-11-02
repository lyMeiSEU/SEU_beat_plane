#pragma once

#include "CEnemyPlane.h"

class EnemyTrackerPlane :public EnemyPlane
{
public:
	EnemyTrackerPlane();
	virtual ~EnemyTrackerPlane();

	void Update();
};

