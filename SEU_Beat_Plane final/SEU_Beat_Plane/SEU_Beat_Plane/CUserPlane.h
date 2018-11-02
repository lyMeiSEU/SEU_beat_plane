#pragma once

#include "CBase_Spriet.h"
#include "CPhoto.h"

class UserPlane : public Base_Sprite
{
public:
	//�������ɵ���
	static UserPlane * GetInstance();
	virtual ~UserPlane();

	//��ʼ���ɻ�������Ѫ���ĸ���
	void InitPlane();

	//��ײ���
	bool CheckCollision(int x, int y, int width, int height, int power);
	bool CheckGift(int x, int y, int width, int height, GiftType gifttype);

	//��Ⱦ
	void Render(HDC hDC);

	//���¾��麯����λ�ã��Ƕȵ����ԣ�
	void Update();

	//���طɻ�ͼƬ��Ѫ��ͼƬ
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
	static Photo *	CUP_pPhotoPlane1; //�ɻ�ͼƬ
	static Photo * CUP_pPhotoPlane2;
	static Photo *	CUP_pPhotoLife;	//����ͼƬ
	static Photo *	CUP_pPhotoHP;       
	static Photo *	CUP_pPhotoHPSide;     //ͼƬָ��
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
	float	CUP_fInvincibletime;//�޵�ʱ��(��λ��)
	int		CUP_nAmmoCount;//ÿ�η����ӵ�����
	float	CUP_fFrequencyTime;//���������ӵ�ʱ��(��)
	bool	CUP_bUnDead;
	bool	CUP_bIsStopMove;
	bool CUP_bBossMusic=true;
	bool	CUP_bFire;
	int		CUP_nWholeFired;//ȫը����
	ActionType CUP_nAction;

};

