#pragma once
#include "Obj.h"
class CPaint :
	public CObj
{
public:
	CPaint();
	virtual ~CPaint();
public:
	virtual        void    Initialize(void);
	virtual        int    Update(void);
	virtual        void    Late_Update(void);
	virtual        void    Render(HDC _hDC);
	virtual        void    Release(void);
public:
	static void Player(HDC m_hDC, INFO& m_tInfo, RECT& m_tRect);
	static void Bullet(HDC m_hDC, INFO& m_tInfo, RECT& m_tRect);
	static void Monster(HDC m_hDC, INFO& m_tInfo, RECT& m_tRect, TYPE _MonsterType, int _Hit_Color);
	static void Item(HDC m_hDC, INFO& m_tInfo, RECT& m_tRect, TYPE _ItemType);
	static void Posin(HDC m_hDC, INFO& m_Posin);
	static void ItemShield(HDC m_hDC, INFO& m_tInfo, INFO* PlayerInfo, RECT& m_tRect, float& Angle);

};

