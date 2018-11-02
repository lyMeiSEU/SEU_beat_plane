#pragma once
#include "stdafx.h"
#include "CEnemyPlane.h"

class EnemyBomberPlane :public EnemyPlane
{
public:
	EnemyBomberPlane();
	EnemyBomberPlane(int x, int y);

	float CEBP_fTime;

	virtual ~EnemyBomberPlane();

	void Update();
};

