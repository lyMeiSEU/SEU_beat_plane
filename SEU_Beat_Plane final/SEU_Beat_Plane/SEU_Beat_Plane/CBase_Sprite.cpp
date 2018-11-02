#include "StdAfx.h"
#include "CBase_Spriet.h"

Base_Sprite * Base_Sprite::CBS_pHead = NULL;
bool Base_Sprite::win = 0;
Base_Sprite::Base_Sprite(int x, int y):
		CBS_bIsVisible(true)
{
	CBS_nX = x;
	CBS_nY = y;
	this->CBS_pNext = CBS_pHead;
	CBS_pHead = this;
}


Base_Sprite::~Base_Sprite(void)
{
	//精灵从画面上删除时，需要更新链表
	//当删除的精灵是表头精灵时
	if (CBS_pHead == this)
	{
		CBS_pHead = CBS_pNext;
		return;
	}
	//当删除的精灵不是表头精灵时
	Base_Sprite *pTemp = CBS_pHead;
	for (;pTemp->CBS_pNext != NULL; pTemp = pTemp->CBS_pNext)
	{
		if (pTemp->CBS_pNext == this)
		{
			pTemp->CBS_pNext = this->CBS_pNext;
			return;
		}
	}
}

bool Base_Sprite::IsVisible()
{
	if(false == CBS_bIsVisible)
	{
		return CBS_bIsVisible;
	}
	//超出可见区域
	if(CBS_nX < - CBS_nWidth		||
	   CBS_nY < - CBS_nHeight	||
	   CBS_nX > SCREEN_WIDTH	||
	   CBS_nY > SCREEN_HEIGHT)
	{
		return false;
	}

	return true;
}

void Base_Sprite::FrameRender(HDC hDC)
{
	Base_Sprite* pTemp = CBS_pHead;
	for(;pTemp!=NULL;pTemp=pTemp->CBS_pNext)
	{
		pTemp->Render(hDC);
	}
}

void Base_Sprite::FrameUpdate()
{
	//循环更新链上每一个图形
	Base_Sprite *pTemp = CBS_pHead;
	for (;pTemp != NULL;)
	{
		if (!pTemp->IsVisible())
		{
			//不可见则删除，并更新链表
			Base_Sprite *p = pTemp;
			p = p->CBS_pNext;
			delete pTemp;
			pTemp = p;
		} 
		else
		{
			pTemp->Update();
			pTemp = pTemp->CBS_pNext;
		}
	}
}