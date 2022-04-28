#include "stdafx.h"
#include "Player.h"
#include "Paint.h"
#include "Bullet.h"
#include "Shield.h"


int test, test2;
CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 100;
	m_tInfo.fY = 360;
	m_Posin.fX = m_tInfo.fX;
	m_Posin.fY = m_tInfo.fY;
	m_Posin.fAngle = 0.f;
	m_tInfo.m_iHp = 10;
	m_tInfo.m_eType = PLAYER;
	m_iAtSpeed = 600;
	Time = GetTickCount();
	m_tInfo.fSpeed = 3;
	m_iBullet_Quantity = 1;
}

int CPlayer::Update(void)
{
	if (m_tInfo.m_bDead)
		return OBJ_DEAD;

	m_fShieldAngle += 0.4f;
	Key_Input();
	
	return OBJ_ALIVE;
}

void CPlayer::Late_Update(void)
{
	m_Posin.fX = m_tInfo.fX;
	m_Posin.fY = m_tInfo.fY;

	if (hit >= 10)
	{
		m_tInfo.m_bDead = true;
	}
	
}

void CPlayer::Render(HDC m_hDC)
{
	if (m_tInfo.iHit > 0)
	{
		SelectObject(m_hDC, GetStockObject(DC_BRUSH));
		SetDCBrushColor(m_hDC, RGB(255, 0, 0));
		m_tInfo.iHit -= 1;
	}
	CPaint::Player(m_hDC, m_tInfo, m_tRect);
	CPaint::Posin(m_hDC, m_Posin);
	SetDCBrushColor(m_hDC, RGB(255, 255, 255));
}

void CPlayer::Key_Input()
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (m_tInfo.fY - 50 > 0)
		m_tInfo.fY -= m_tInfo.fSpeed;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (m_tInfo.fY + 50 < WINCY)
		m_tInfo.fY += m_tInfo.fSpeed;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_tInfo.fX + 40 < WINCX)
		m_tInfo.fX += m_tInfo.fSpeed;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_tInfo.fX - 40 > 0)
			m_tInfo.fX -= m_tInfo.fSpeed;
	}

	if (GetAsyncKeyState('Z'))
	{
		if(m_Posin.fAngle >= -1.f)
			m_Posin.fAngle -= 0.03f; /*앵글이 -60도보다 크면 앵글을 - 해라 
									앵글을 -하면 팔이 위로가고
									앵글을 +하면 팔이 아래로감 */
	}

	if (GetAsyncKeyState('X'))
	{
		if (m_Posin.fAngle <= 1.f) //앵글이 60도 보다 작으면 앵글을 더해라
			m_Posin.fAngle += 0.03f;
		
	}

	

	if (Time + m_iAtSpeed < GetTickCount())
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			for (int i = 0; i < m_iBullet_Quantity; ++i)
			{
				float _fBullet_Y;
				_fBullet_Y = m_Posin.fY + 50.f;
				_fBullet_Y -= (100.f / (m_iBullet_Quantity + 1.f) * float(i+1));
				m_Bulletlist->push_back(CAbstractFactory<CBullet>::Create(m_Posin.fX, _fBullet_Y, m_Posin.fAngle, true));
			}			
		}
		Time = GetTickCount();
	}
}

void CPlayer::PickItem(TYPE _Type)
{
	switch (_Type)
	{
	case SHIELD:	
		{
			for (auto& iter : (*m_ShieldList))
			{
				iter->Set_Dead();
			}
			float _i = 120.f;
			for (int i = 1; i < 4; ++i)
			{
				m_ShieldList->push_back(CAbstractFactory<CShield>::Create());//실드 부족한 개수만큼 생성				
				dynamic_cast<CShield*>(m_ShieldList->back())->SetPlayerInfo(&m_tInfo, _i*i);
			}
		}
		break;

	case  PORTION:
		if (hit >= 3)
		{
			hit -= 3;
			m_tInfo.m_iHp += 3;
		}
		else if (hit <= 3)
		{
			hit = 0;
			m_tInfo.m_iHp = 10;
		}

		break;
	case QUANTITY:
		if (m_iBullet_Quantity < 3)
		{
			++m_iBullet_Quantity;
		}
		break;

	case ATSPEED:
		if(m_iAtSpeed >= 300)
		m_iAtSpeed -= 200;
		break;
	}
}

void CPlayer::Release(void)
{
}
