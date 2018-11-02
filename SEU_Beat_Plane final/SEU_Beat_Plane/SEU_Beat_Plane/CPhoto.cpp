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
	//��ȡλͼ���
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
	//͸����ͼ
	HDC	hBitmapDC = CreateCompatibleDC(hdcDest);
	SelectObject(hBitmapDC, CPh_hBitmap);
	HDC hMaskDC=CreateCompatibleDC(hdcDest);
	SelectObject(hMaskDC, CPh_hMaskBitmap);

	SetBkColor(hdcDest, RGB(255, 255, 255));
	SetTextColor(hdcDest, RGB(0, 0, 0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, nXOriginSrc, nYOriginSrc, SRCAND);// �������붴
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hBitmapDC, nXOriginSrc, nYOriginSrc, SRCPAINT); // ͸��Ч��
	
	DeleteObject(hBitmapDC);
	DeleteObject(hMaskDC);
}

void Photo::TransparentBitmap()
{
	//��������DC��λͼ���Ա�����͸��Ч��
	HDC	hMaskDC, hBitmapDC;

	CPh_hMaskBitmap = CreateBitmap(CPh_nWidth, CPh_nHeight, 1, 1, NULL);//��ɫλͼ
	hBitmapDC = CreateCompatibleDC(0);
	hMaskDC = CreateCompatibleDC(0);

	SelectObject(hBitmapDC, CPh_hBitmap);
	SelectObject(hMaskDC, CPh_hMaskBitmap);

	//�����ǽ���͸������ǰ�࣬ԭ����ο�ͷ�ļ��г�����ַ
	SetBkColor(hBitmapDC, CPh_TransColor);	
	BitBlt(hMaskDC, 0, 0, CPh_nWidth, CPh_nHeight, hBitmapDC, 0, 0, SRCCOPY);//��������λͼ

	SetBkColor( hBitmapDC, RGB(0, 0, 0) );
	SetTextColor(hBitmapDC, RGB(255, 255, 255) );

	BitBlt(hBitmapDC, 0, 0, CPh_nWidth, CPh_nHeight, hMaskDC, 0, 0, SRCAND);//��ɫ����ͼ

	DeleteObject(hBitmapDC);
	DeleteObject(hMaskDC);
}