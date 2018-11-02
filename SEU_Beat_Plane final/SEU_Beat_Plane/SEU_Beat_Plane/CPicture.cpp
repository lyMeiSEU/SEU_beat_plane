#include "stdafx.h"
#include "CPicture.h"


#include<windows.h>
#include <iostream>


Picture::Picture() :
	CPi_hBitmap(NULL),
	CPi_TransColor(RGB(0, 0, 0)),
	CPi_nWidth(0),
	CPi_nHeight(0)
{
}

Picture::~Picture()
{
	FreeBitmap();
}


VOID Picture::FreeBitmap()
{
	if (CPi_hBitmap)
		DeleteObject(CPi_hBitmap);
}

VOID Picture::LoadBitmap(LPCTSTR lpszName, UINT Color, int w, int h)//����λͼ���ļ�������Ҫ͸�����ı�����ɫ��λͼ��λͼ�ߣ�
{
	CPi_nWidth = w;
	CPi_nHeight = h;
	CPi_TransColor = Color;
	if (CPi_hBitmap)
	{
		DeleteObject(CPi_hBitmap);
	}
	CPi_hBitmap = (HBITMAP)LoadImage(NULL, lpszName, IMAGE_BITMAP, CPi_nWidth, CPi_nHeight, LR_LOADFROMFILE);//����λͼ

}

VOID Picture::DrawBitmap(HWND hWnd, int xoriginDest, int yoriginDest, int wDest, int hDest, int xoriginSrc, int yoriginSrc)//���Ʊ���͸��ͼ
{
	HDC ghdc = GetDC(hWnd);
	HDC g_mdc = CreateCompatibleDC(ghdc);//��������DC
	SelectObject(g_mdc, CPi_hBitmap);//ѡ��λͼ����
	TransparentBlt(ghdc, xoriginDest, yoriginDest, wDest, hDest, g_mdc, xoriginSrc, yoriginSrc, CPi_nWidth, CPi_nHeight, CPi_TransColor);
	//��ͼ�������豸���������Ŀ�ľ���X���꣬Ŀ�ľ���Y��Ŀ���Ŀ��ߣ�ԭ�豸���������ԭ����X���꣬Y��ԭ���ο��ߣ�RGB��ɫֵ��
	ReleaseDC(hWnd, ghdc);
	DeleteDC(g_mdc);
	DeleteDC(ghdc);
}

