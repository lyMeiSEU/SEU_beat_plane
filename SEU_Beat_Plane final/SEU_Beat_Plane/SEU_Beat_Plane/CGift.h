#pragma once

#include <windef.h>
#include "CBase_Spriet.h"
#include "CPhoto.h"

class Gift : public Base_Sprite
{
public:
	Gift(int x, int y,GiftType gifetype);
	virtual ~Gift(void);

	//渲染
	void Render(HDC hdc) ;

	//更新精灵函数（位置，角度等属性）
	void Update() ;

	static void LoadImage();
	static void FreeImage();

	bool IsVisible();
protected:
	
	GiftType			CGf_nGiftType;
	static Photo  *	CGf_pPictureGift[4];
};

