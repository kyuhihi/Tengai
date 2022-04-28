#pragma once

#include "include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual        void    Initialize(void)PURE;
	virtual        int    Update(void)PURE;
	virtual        void    Late_Update(void)PURE;
	virtual        void    Render(HDC _hDC)PURE;
	virtual        void    Release(void)PURE;
public:

	void    Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;        // fX ÀÇ ÁßÁ¡ÁÂÇ¥ _fX
		m_tInfo.fY = _fY;        // fY ÀÇ ÁßÁ¡ÁÂÇ¥ _fY
	}

	const    RECT&    Get_Rect(void) { return m_tRect; }
	const	 INFO&	  Get_Info(void) { return m_tInfo; }

	void Set_Angle(float _Angle) { m_tInfo.fAngle = _Angle; }

	void Set_Type(TYPE t) { m_tInfo.m_eType = t; }

	void Set_ToPos(INFO _tInfo) { m_tInfo.fToX = _tInfo.fX; m_tInfo.fToY = _tInfo.fY; }

	void Set_ToPos(float _fToX, float _fToY) { m_tInfo.fToX = _fToX; m_tInfo.fToY = _fToY; }

	void Set_Dead(){ m_tInfo.m_bDead = true; }

	void Plus_Hp(int _iHp) { m_tInfo.m_iHp += _iHp; }

	int Get_Hp() { return m_tInfo.m_iHp; }

	TYPE Get_Type() { return m_tInfo.m_eType; }

	void Set_Player_Bullet(bool _bPlayer_Bullet) { m_tInfo._bPlayer_Bullet = _bPlayer_Bullet; }

	int Get_Hit_Color() { return m_tInfo.iHit; }
	void Set_Hit_Color(int _iHit) { m_tInfo.iHit = _iHit; }

protected:

	INFO        m_tInfo;
	RECT        m_tRect;


};