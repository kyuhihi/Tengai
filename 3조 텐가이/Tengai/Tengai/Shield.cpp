#include "stdafx.h"
#include "Shield.h"
#include "Paint.h"

CShield::CShield()
	: fDiagonalTemp(50.f)
{
}


CShield::~CShield()
{
}

void CShield::Initialize(void)
{
	m_tInfo.m_iHp = 1;
}

int CShield::Update(void)
{
	if (m_tInfo.m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = ((*m_PlayerXY).fX + fDiagonalTemp * cosf((m_PlayerAngle * PI) / 180.f));
	m_tInfo.fY = ((*m_PlayerXY).fY - fDiagonalTemp * sinf((m_PlayerAngle * PI) / 180.f));

	return OBJ_ALIVE;
}

void CShield::Late_Update(void)
{
	if (m_tInfo.m_iHp <= 0)
		m_tInfo.m_bDead = true;
	m_PlayerAngle += 10;
}

void CShield::Render(HDC _hDC)
{
	CPaint::ItemShield(_hDC, m_tInfo, m_PlayerXY, m_tRect, m_PlayerAngle);
}

void CShield::Release(void)
{
}

void CShield::SetPlayerInfo(INFO* _tPlayer, float Angle)
{
	m_PlayerXY = _tPlayer;
	m_PlayerAngle = Angle;
}
