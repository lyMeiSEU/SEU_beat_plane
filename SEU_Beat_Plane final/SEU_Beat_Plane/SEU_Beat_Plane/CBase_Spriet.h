#pragma once

#define PI	3.141592653f

enum GiftType
{
	SPEEDUP = 0,
	ADDBLOOD,
	ADDLIFE,
	ADDFIREALL
};

//定义子弹类型
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

//定义动作类型
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

//敌机类型
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

//爆炸效果类型
enum BlastType
{
	BULLETBLAST,
	PLANEBLAST
};

class Base_Sprite
{
public:
	//精灵位置，定义为图片左上角
	Base_Sprite(int	x, int y);
	virtual ~Base_Sprite(void);

	//刷新一帧画面
	static void FrameRender(HDC hDC);

	//统一更新帧数据
	static void FrameUpdate();
	
	//判断精灵是否可见
	virtual bool IsVisible();

	//渲染，即绘制函数
	virtual void Render(HDC hDC) = 0;

	//更新精灵函数（位置，角度等属性）
	virtual void Update() = 0;

	//以下为设置和获取位置函数
	int GetX(){ return CBS_nX; }
	int GetY(){ return CBS_nY; }
	void SetX(int x){ CBS_nX = x; }
	void SetY(int y){ CBS_nY = y; }

	static bool win;

protected:
	int	CBS_nX;
	int CBS_nY;
	int CBS_nFrameStartX;//当前帧图片开始贴图的X坐标
	int	CBS_nSpeed;//精灵速度
	int CBS_nFrameCount;//帧数（如一类子弹有几张图）
	int CBS_nCurrentFrame;//当前帧数
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

