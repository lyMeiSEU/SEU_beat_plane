#pragma once

#define PI	3.141592653f

enum GiftType
{
	SPEEDUP = 0,
	ADDBLOOD,
	ADDLIFE,
	ADDFIREALL
};

//�����ӵ�����
enum BulletType
{
	AMMO0 = 0,
	AMMO1,
	AMMO2,
	AMMO3,
	AMMO4,
	AMMO5,
	AMMO6,
	AMMO7,
	AMMO8,
	WHOLEFRIED
};

//���嶯������
enum ActionType
{
	LEFT,
	DOWN,
	RIGHT,
	UP,
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN,
	STOP_MOVE,
	FIRE,
	STOP_FIRE,
	FIREALL
};

//�л�����
enum EnemyType
{
	ENEMY0 = 0,
	ENEMY1,
	ENEMY2,
	ENEMY3,
	ENEMY4,
	BOSS,
	BIGBOSS
};

//��ըЧ������
enum BlastType
{
	BULLETBLAST,
	PLANEBLAST
};

class Base_Sprite
{
public:
	//����λ�ã�����ΪͼƬ���Ͻ�
	Base_Sprite(int	x, int y);
	virtual ~Base_Sprite(void);

	//ˢ��һ֡����
	static void FrameRender(HDC hDC);

	//ͳһ����֡����
	static void FrameUpdate();
	
	//�жϾ����Ƿ�ɼ�
	virtual bool IsVisible();

	//��Ⱦ�������ƺ���
	virtual void Render(HDC hDC) = 0;

	//���¾��麯����λ�ã��Ƕȵ����ԣ�
	virtual void Update() = 0;

	//����Ϊ���úͻ�ȡλ�ú���
	int GetX(){ return CBS_nX; }
	int GetY(){ return CBS_nY; }
	void SetX(int x){ CBS_nX = x; }
	void SetY(int y){ CBS_nY = y; }

	static bool win;

protected:
	int	CBS_nX;
	int CBS_nY;
	int CBS_nFrameStartX;//��ǰ֡ͼƬ��ʼ��ͼ��X����
	int	CBS_nSpeed;//�����ٶ�
	int CBS_nFrameCount;//֡������һ���ӵ��м���ͼ��
	int CBS_nCurrentFrame;//��ǰ֡��
	int	CBS_nWidth;
	int CBS_nHeight;
	int CBS_nScore;
	float CBS_fSpeedX;
	float CBS_fSpeedY;
	float CBS_fAngle;
	bool	CBS_bIsVisible;
	Base_Sprite * CBS_pNext;
	static Base_Sprite * CBS_pHead;
};

