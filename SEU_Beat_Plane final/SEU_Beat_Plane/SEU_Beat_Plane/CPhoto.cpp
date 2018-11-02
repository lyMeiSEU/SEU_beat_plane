#include "StdAfx.h"
#include "CPhoto.h"


Photo::Photo():
	CPh_hBitmap(NULL),
	CPh_hMaskBitmap(NULL)
{
}


Photo::~Photo(void)
{
}

void Photo::FreeBitmap()
{
	if (CPh_hBitmap)
	{
		DeleteObject(CPh_hBitmap);
	}

	if (CPh_hMaskBitmap)
	{
		DeleteObject(CPh_hMaskBitmap);
	}
}

void Photo::LoadBitmap(TCHAR *szFileName)
{
	if (CPh_hBitmap)
	{
		DeleteObject(CPh_hBitmap);
	}
	CPh_hBitmap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);
	//获取位图宽高
	BITMAP	bmpTemp;
	GetObject(CPh_hBitmap, sizeof(BITMAP), &bmpTemp);
	CPh_nWidth = bmpTemp.bmWidth;
	CPh_nHeight = bmpTemp.bmHeight;
}

void Photo::LoadBitmap(TCHAR *szFileName, COLORREF clTransparent)
{
	LoadBitmap(szFileName);
	CPh_TransColor = clTransparent;
	TransparentBitmap();
}

void Photo::DrawBitmap(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc)
{
	//透明贴图
	HDC	hBitmapDC = CreateCompatibleDC(hdcDest);
	SelectObject(hBitmapDC, CPh_hBitmap);
	HDC hMaskDC=CreateCompatibleDC(hdcDest);
	SelectObject(hMaskDC, CPh_hMaskBitmap);

	SetBkColor(hdcDest, RGB(255, 255, 255));
	SetTextColor(hdcDest, RGB(0, 0, 0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, nXOriginSrc, nYOriginSrc, SRCAND);// 生成掩码洞
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hBitmapDC, nXOriginSrc, nYOriginSrc, SRCPAINT); // 透明效果
	
	DeleteObject(hBitmapDC);
	DeleteObject(hMaskDC);
}

void Photo::TransparentBitmap()
{
	//创建兼容DC和位图，以便制作透明效果
	HDC	hMaskDC, hBitmapDC;

	CPh_hMaskBitmap = CreateBitmap(CPh_nWidth, CPh_nHeight, 1, 1, NULL);//单色位图
	hBitmapDC = CreateCompatibleDC(0);
	hMaskDC = CreateCompatibleDC(0);

	SelectObject(hBitmapDC, CPh_hBitmap);
	SelectObject(hMaskDC, CPh_hMaskBitmap);

	//下面是进行透明处理前奏，原理请参看头文件列出的网址
	SetBkColor(hBitmapDC, CPh_TransColor);	
	BitBlt(hMaskDC, 0, 0, CPh_nWidth, CPh_nHeight, hBitmapDC, 0, 0, SRCCOPY);//生成掩码位图

	SetBkColor( hBitmapDC, RGB(0, 0, 0) );
	SetTextColor(hBitmapDC, RGB(255, 255, 255) );

	BitBlt(hBitmapDC, 0, 0, CPh_nWidth, CPh_nHeight, hMaskDC, 0, 0, SRCAND);//黑色背景图

	DeleteObject(hBitmapDC);
	DeleteObject(hMaskDC);
}