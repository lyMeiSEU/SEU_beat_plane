#pragma once

#include "CBase_Spriet.h"
#include "CPhoto.h"

class EnemyPlane : public Base_Sprite
{
public:
	EnemyPlane(EnemyType enemyType);
	virtual ~EnemyPlane(void);

	//碰撞检测
	bool CheckCollision(int x, int y, int width, int height, int power);

	static void CreateEnemy();

	//渲染
	virtual void Render(HDC hDC);

	//更新精灵函数（位置，角度等属性）
	void Update();

	//加载飞机图片
	static void LoadBimap();
	static void FreeBitmap();

	static int GetEnemyPlaneX();
	static int GetWidth();

	bool IsVisible();

	void CircleBullet(int x, int y, BulletType bulletType);

	static EnemyPlane *spEnemyHead;
	EnemyPlane * m_pEmnemyNext;
	EnemyType	CEP_nEnemyType;

protected:
	
	static Photo * CEP_pPhotoEnemy[9];
	static Photo *	CEP_pPhotoHP;
	static Photo *	CEP_pPhotoHPSide;
	static int CEP_nEnemyCount;
	static float CEP_fLastCreateTime;
	static float CEP_fLastCreateBomberPlaneTime;
	float  CEP_fAllTime;
	float	CEP_fFireTime;
	int		CEP_nHP;
	int		CEP_nWholeHP;
	
};

