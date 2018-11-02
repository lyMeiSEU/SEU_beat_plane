#pragma once

#include "CBase_Spriet.h"
#include "CPhoto.h"

class EnemyPlane : public Base_Sprite
{
public:
	EnemyPlane(EnemyType enemyType);
	virtual ~EnemyPlane(void);

	//��ײ���
	bool CheckCollision(int x, int y, int width, int height, int power);

	static void CreateEnemy();

	//��Ⱦ
	virtual void Render(HDC hDC);

	//���¾��麯����λ�ã��Ƕȵ����ԣ�
	void Update();

	//���طɻ�ͼƬ
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

