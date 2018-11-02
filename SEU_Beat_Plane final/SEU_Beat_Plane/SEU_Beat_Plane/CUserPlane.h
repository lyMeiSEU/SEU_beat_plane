#pragma once

#include "CBase_Spriet.h"
#include "CPhoto.h"

class UserPlane : public Base_Sprite
{
public:
	//控制生成单例
	static UserPlane * GetInstance();
	virtual ~UserPlane();

	//初始化飞机，包括血量的更新
	void InitPlane();

	//碰撞检测
	bool CheckCollision(int x, int y, int width, int height, int power);
	bool CheckGift(int x, int y, int width, int height, GiftType gifttype);

	//渲染
	void Render(HDC hDC);

	//更新精灵函数（位置，角度等属性）
	void Update();

	//加载飞机图片和血量图片
	static void LoadBimap();
	static void FreeBitmap();

	BulletType GetBulletType(){ return CUP_nBulletType; }

	static int GetUserX() { return CUP_pCUserPlane->CBS_nX; }
	static int GetUserY() { return CUP_pCUserPlane->CBS_nY; }
	static int GetScore();

	static void AddScore(int score);

	void SetBulletType(BulletType bulletType){ CUP_nBulletType = bulletType; }

	void SetAmmoCount(int nAmmoCount){ CUP_nAmmoCount = nAmmoCount ;}

	static void SetBestScore(int score) { CUP_pCUserPlane->BestScore = score; }

	void Control(ActionType actionType);

	static bool GetGameOver(){ return CUP_bGameOver; }
	static int chosefighter;
	static bool	CUP_bGameOver;
protected:
	UserPlane(int x, int y);

	static UserPlane * CUP_pCUserPlane;
	static Photo *	CUP_pPhotoPlane1; //飞机图片
	static Photo * CUP_pPhotoPlane2;
	static Photo *	CUP_pPhotoLife;	//生命图片
	static Photo *	CUP_pPhotoHP;       
	static Photo *	CUP_pPhotoHPSide;     //图片指针
	static Photo * CUP_pPhotoScore;     
	static Photo * CUP_pPhotoScore0_4;
	static Photo * CUP_pPhotoScore5_9;
	static Photo * CUP_pPhotoWholeFiredNumber;
	int BestScore;
	BulletType	CUP_nBulletType;
	int	CUP_nHP;
	int	CUP_nLife;
	float	CUP_fBulletFrequency;
	float	CUP_fTrackerBulletFrequnecy;
	float	CUP_fInvincibletime;//无敌时间(单位秒)
	int		CUP_nAmmoCount;//每次发射子弹数量
	float	CUP_fFrequencyTime;//连续发射子弹时间(秒)
	bool	CUP_bUnDead;
	bool	CUP_bIsStopMove;
	bool CUP_bBossMusic=true;
	bool	CUP_bFire;
	int		CUP_nWholeFired;//全炸数量
	ActionType CUP_nAction;

};

