#pragma once

class UserPlane;

class GameControler
{
public:
	static GameControler * GetInstance();
	~GameControler(void);

	//更新游戏场景
	void UpdateScence();
	void WIN();
	//获取时间间隔
	float GetElapsedTime(){ return CGC_fElapsedTime;}

	//键盘按键处理
	void KeyDown(WPARAM nKeyCode);
	void KeyUp(WPARAM nKeyCode);

	void SetLastTime(DWORD lastTime){ CGC_dwLastTime = lastTime; }
	void SetCurrentTime(DWORD currentTime){ CGC_dwCurrentTime = currentTime; }

	void SetWndDC(HDC hDC);

	void START();

	void END();


	void EXIT();
private:
	GameControler(void);

	//地图循环贴图
	void CirculationMap();

	static GameControler * CGC_pGameControler;

	DWORD CGC_dwLastTime;//上次绘图时间
	DWORD CGC_dwCurrentTime;//当前时间

	HDC	  CGC_hMemDC;

	HBITMAP	CGC_hBitmapMap;
	HBITMAP CGC_hMemBitmap;

	HDC		CGC_hWndDC;
	HDC		CGC_hMapDC; 
	int		CGC_nY; //记录地图被截取的宽度
	float	CGC_fElapsedTime;

	int		CGC_nPreKey;
	int		CGC_nCurKey;

	UserPlane * CGC_pPrincipalPlane;
};

