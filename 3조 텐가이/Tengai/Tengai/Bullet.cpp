#include "stdafx.h"
#include "Bullet.h"



CBullet::CBullet()
	: m_bTurn(false)
	, m_BossShot_Y(0)
	, m_BossShot_X(0)
{
}
//bullllllllllllllllllllllllllllllllllllet

CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo.fSpeed = 5.0f;
	m_tInfo.m_iHp = 1;
}

int CBullet::Update(void)
{
	if (m_tInfo.m_bDead)
	{
		return OBJ_DEAD;
	}

	if (!m_bTurn)
	{
		m_tInfo.fY += sinf(m_tInfo.fAngle)*m_tInfo.fSpeed;
		m_tInfo.fX += cosf(m_tInfo.fAngle)*m_tInfo.fSpeed;
		if (m_BossShot_Y)
		{ 
			if (m_tInfo.fToX + ((m_BossShot_Y - m_tInfo.fToX)*0.3) >= m_tInfo.fX)
			{
				float fWidth = (m_tInfo.fToX - m_tInfo.fX);
				float fHeight = (m_tInfo.fToY - m_tInfo.fY);
				float fRadius = (fWidth*fWidth) + (fHeight*fHeight);
				float fDistance = sqrtf(fRadius);

				_sinseta = asin(fHeight / fDistance);
				_cosseta = acos(fWidth / fDistance);
				m_bTurn = true;
			}
		}
	}
	else
	{
		m_tInfo.fY += sinf(_sinseta)*m_tInfo.fSpeed;
		m_tInfo.fX += cosf(_cosseta)*m_tInfo.fSpeed;

		/*if (m_tInfo.fX <= m_tInfo.fToX+5 && m_tInfo.fX >= m_tInfo.fToX - 5)
			m_tInfo.m_bDead = true;*/
	}
	
	return OBJ_ALIVE;
}

void CBullet::Late_Update(void)
{

	if (
			m_tRect.left < 0 ||
			m_tRect.top < 0 ||
			m_tRect.right > WINCX ||
			m_tRect.bottom > WINCY
		
		)
	{
		m_tInfo.m_bDead = true;
	}

	if (m_tInfo.m_iHp <= 0)
	{
		m_tInfo.m_bDead = true;
	}

}

void CBullet::Render(HDC _hDC)
{
	CPaint::Bullet(_hDC, m_tInfo, m_tRect);
}

void CBullet::Release(void)
{
}