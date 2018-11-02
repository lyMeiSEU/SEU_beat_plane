#pragma once
#pragma comment(lib,"Msimg32.lib")

#include<windows.h>
using namespace std;
class Picture
{
public:
	Picture();
	~Picture();

	VOID DrawBitmap(HWND hWnd, //Ŀ���豸�������
		int xoriginDest,//Ŀ��������Ͻ�x������
		int yoriginDest,//y����
		int wDest,//Ŀ����ο��
		int hDest,//�߶�
		int xoriginSrc,//ԭ�������Ͻ�x����
		int yoriginSrc);//y����

	VOID LoadBitmap(LPCTSTR lpszName, UINT Color, int w, int h);//����
	VOID FreeBitmap();
	
	HBITMAP GetBitmap() { return CPi_hBitmap; }
	int	GetWidth() { return CPi_nWidth; }
	int GetHeight() { return CPi_nHeight; }
private:

	HBITMAP		CPi_hBitmap;//����λͼ���
	UINT	CPi_TransColor;//����Ϊ͸��ɫ�ı�����ɫ
	int			CPi_nWidth;//���ο��
	int			CPi_nHeight;//����ͼƬ�߶�
};


