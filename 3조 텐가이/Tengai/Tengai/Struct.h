#pragma once
#include "Enum.h"
typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;
	float fToX;
	float fToY;
	float fAngle;
	float fSpeed;
	int m_iHp;
	bool m_bDead;
	TYPE m_eType;
	bool _bPlayer_Bullet;
	int iHit;
}INFO;