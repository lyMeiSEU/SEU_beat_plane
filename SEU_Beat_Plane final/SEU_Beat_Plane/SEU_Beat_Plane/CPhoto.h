#pragma once

class Photo
{
public:
	Photo();
	~Photo(void);

	//将位图进行透明处理，并贴到指定DC上
	void DrawBitmap(HDC hdcDest,			//目的DC
					   int nXOriginDest,	//起始X坐标
					   int nYOriginDest,	//起始Y坐标
					   int nWidthDest,		//目标DC宽度	
					   int nHeightDest,		//目标DC高度
					   int nXOriginSrc,		//位图起始X坐标
					   int nYOriginSrc);	//位图起始Y坐标

	//需要提供文件名和用于设置透明的掩码色，因为找到的图片背景有白有红有绿，因此设置了此参数
	void LoadBitmap(TCHAR *szFileName, COLORREF clTransparent);
	
	//获取位图资源句柄
	HBITMAP GetBitmap(){ return CPh_hBitmap; }

	int	GetWidth(){ return CPh_nWidth; }
	int GetHeight(){ return CPh_nHeight; }

	void FreeBitmap();
private:
	//加载位图资源
	void LoadBitmap(TCHAR *szFileName);

	//将图片进行透明处理
	void TransparentBitmap();

	HBITMAP		CPh_hBitmap;
	HBITMAP		CPh_hMaskBitmap;
	COLORREF	CPh_TransColor;

	int			CPh_nWidth;
	int			CPh_nHeight;
};

