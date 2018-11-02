#pragma once

#include "CBase_Spriet.h"
#include "CPhoto.h"

class Explosion : Base_Sprite
{
public:
	Explosion(int x, int y, BlastType blastType);
	virtual ~Explosion(void);

	static void LoadImage();
	static void FreeImage();

	void Update();
	void Render(HDC hDC);
private:
	static	Photo * CEP_pPictureBlast[2];
	BlastType CEP_nBlastType;
};

