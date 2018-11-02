#pragma once

class UserPlane;

class GameControler
{
public:
	static GameControler * GetInstance();
	~GameControler(void);

	//������Ϸ����
	void UpdateScence();
	void WIN();
	//��ȡʱ����
	float GetElapsedTime(){ return CGC_fElapsedTime;}

	//���̰�������
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

	//��ͼѭ����ͼ
	void CirculationMap();

	static GameControler * CGC_pGameControler;

	DWORD CGC_dwLastTime;//�ϴλ�ͼʱ��
	DWORD CGC_dwCurrentTime;//��ǰʱ��

	HDC	  CGC_hMemDC;

	HBITMAP	CGC_hBitmapMap;
	HBITMAP CGC_hMemBitmap;

	HDC		CGC_hWndDC;
	HDC		CGC_hMapDC; 
	int		CGC_nY; //��¼��ͼ����ȡ�Ŀ��
	float	CGC_fElapsedTime;

	int		CGC_nPreKey;
	int		CGC_nCurKey;

	UserPlane * CGC_pPrincipalPlane;
};

