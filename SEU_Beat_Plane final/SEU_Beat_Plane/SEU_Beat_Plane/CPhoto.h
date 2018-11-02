#pragma once

class Photo
{
public:
	Photo();
	~Photo(void);

	//��λͼ����͸������������ָ��DC��
	void DrawBitmap(HDC hdcDest,			//Ŀ��DC
					   int nXOriginDest,	//��ʼX����
					   int nYOriginDest,	//��ʼY����
					   int nWidthDest,		//Ŀ��DC���	
					   int nHeightDest,		//Ŀ��DC�߶�
					   int nXOriginSrc,		//λͼ��ʼX����
					   int nYOriginSrc);	//λͼ��ʼY����

	//��Ҫ�ṩ�ļ�������������͸��������ɫ����Ϊ�ҵ���ͼƬ�����а��к����̣���������˴˲���
	void LoadBitmap(TCHAR *szFileName, COLORREF clTransparent);
	
	//��ȡλͼ��Դ���
	HBITMAP GetBitmap(){ return CPh_hBitmap; }

	int	GetWidth(){ return CPh_nWidth; }
	int GetHeight(){ return CPh_nHeight; }

	void FreeBitmap();
private:
	//����λͼ��Դ
	void LoadBitmap(TCHAR *szFileName);

	//��ͼƬ����͸������
	void TransparentBitmap();

	HBITMAP		CPh_hBitmap;
	HBITMAP		CPh_hMaskBitmap;
	COLORREF	CPh_TransColor;

	int			CPh_nWidth;
	int			CPh_nHeight;
};

