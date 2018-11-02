#pragma once
#pragma comment(lib,"Msimg32.lib")

#include<windows.h>
using namespace std;
class Picture
{
public:
	Picture();
	~Picture();

	VOID DrawBitmap(HWND hWnd, //目标设备环境句柄
		int xoriginDest,//目标矩形左上角x轴坐标
		int yoriginDest,//y坐标
		int wDest,//目标矩形宽度
		int hDest,//高度
		int xoriginSrc,//原矩形左上角x坐标
		int yoriginSrc);//y坐标

	VOID LoadBitmap(LPCTSTR lpszName, UINT Color, int w, int h);//名称
	VOID FreeBitmap();
	
	HBITMAP GetBitmap() { return CPi_hBitmap; }
	int	GetWidth() { return CPi_nWidth; }
	int GetHeight() { return CPi_nHeight; }
private:

	HBITMAP		CPi_hBitmap;//加载位图句柄
	UINT	CPi_TransColor;//设置为透明色的背景颜色
	int			CPi_nWidth;//矩形宽度
	int			CPi_nHeight;//矩形图片高度
};


