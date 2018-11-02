#pragma once

#include <windef.h>
#include "CBase_Spriet.h"
#include "CPhoto.h"

class Gift : public Base_Sprite
{
public:
	Gift(int x, int y,GiftType gifetype);
	virtual ~Gift(void);

	//��Ⱦ
	void Render(HDC hdc) ;

	//���¾��麯����λ�ã��Ƕȵ����ԣ�
	void Update() ;

	static void LoadImage();
	static void FreeImage();

	bool IsVisible();
protected:
	
	GiftType			CGf_nGiftType;
	static Photo  *	CGf_pPictureGift[4];
};

