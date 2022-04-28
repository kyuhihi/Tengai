#include "stdafx.h"
#include "Monster.h"
int bosshit = 0;


CMonster::CMonster()
	: m_bTurn(false)
	, m_BossPatternTime(0)
{

}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	switch (m_tInfo.m_eType)
	{
	case NOMAL:
		m_tInfo.m_iHp = 2;
		break;

	case BOOM:
		m_tInfo.m_iHp = 1;
		break;

	case BOSS:
		m_tInfo.m_iHp = 50;
		m_BPattern = GUIDED;
		m_tInfo.fAngle = 115.f;
		break;
	}
	m_iBoom = 2;
	m_tInfo.fSpeed = 5.f;
	MTime = GetTickCount();
}

int CMonster::Update(void)
{
	if (m_tInfo.m_bDead)

	{
		if (m_tInfo.m_eType == BOSS)
		{
			return OBJ_DEAD;
		}
		else if (m_tInfo.m_eType != BOSS)
		{
			if (m_iBoom >= 30)
			{
			return OBJ_DEAD;
			}
		}
		
	}

	

	switch (m_tInfo.m_eType)
	{
	case NOMAL:
		Update_Nomal();
		break;

	case BOOM:
		Update_Boom();
		break;

	case BOSS:
		Update_Boss();
		++m_BossPatternTime;
		break;
	}

	return OBJ_ALIVE;
}

void CMonster::Late_Update(void)
{
	if (m_tInfo.m_eType != BOOM)
	{
		if (m_tInfo.fY < 0 || m_tInfo.fY > WINCY)
			Set_Turn();
	}

	if (m_BossPatternTime >= 500)
	{
		Update_Pattern();
		m_BossPatternTime = 0;
	}
	
	if (m_tInfo.m_iHp <= 0)
	{
		

		if (Get_Random() < 5)
		{
			random_device random;
			mt19937 rd(random());
			uniform_int_distribution<int> range(1, 4);
			int _rand = range(rd);

			if (m_tInfo.m_iHp > -4 && m_tInfo.m_eType != BOSS)
			{
				if (1 == _rand)
				{
					if (MTime + 300 < GetTickCount())
					{
						(*m_Itemlist).push_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY, SHIELD));
						MTime = GetTickCount();
					}
				}
				else if (2 == _rand)
				{
					if (MTime + 300 < GetTickCount())
					{
						(*m_Itemlist).push_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY, PORTION));
						MTime = GetTickCount();
					}
				}
				else if (3 == _rand)
				{
					if (MTime + 300 < GetTickCount())
					{
						(*m_Itemlist).push_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY, QUANTITY));
						MTime = GetTickCount();
					}
				}
				else
				{
					if (MTime + 300 < GetTickCount())
					{
						(*m_Itemlist).push_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY, ATSPEED));
						MTime = GetTickCount();
					}
				}
			}
		}
		
		
		m_tInfo.m_bDead = true;
	}
}

void CMonster::Render(HDC _hDC)
{
	if (m_tInfo.m_eType == BOSS)
	{
		SelectObject(_hDC, GetStockObject(DC_BRUSH));
		SetDCBrushColor(_hDC, RGB(255, 188, 217));
	}
	if (m_tInfo.m_eType != BOOM)
	{
		if (m_tInfo.iHit > 0)
		{
			SelectObject(_hDC, GetStockObject(DC_BRUSH));
			SetDCBrushColor(_hDC, RGB(255, 0, 0));
			m_tInfo.iHit -= 1;
		}
	}
	
	

	if (m_tInfo.m_eType == BOSS)
	{
		SetBkColor(_hDC, RGB(0, 255, 0));
		wsprintf(BossHp, TEXT("Â¯½Ú Ä¿ºñ"));
		TextOut(_hDC, m_tRect.left + 70, m_tRect.top - 70, BossHp, lstrlen(BossHp));
		SetBkColor(_hDC, RGB(255, 255, 255));

		SetBkColor(_hDC, RGB(255, 0, 0));
		wsprintf(BossHp, TEXT("                                                  "));
		TextOut(_hDC, m_tRect.left, m_tRect.top - 50, BossHp, lstrlen(BossHp + bosshit));
		SetBkColor(_hDC, RGB(255, 255, 255));
	}

	if (m_tInfo.m_bDead)
	{
		if (m_iBoom < 30)
		{
			SelectObject(_hDC, GetStockObject(DC_BRUSH));
			SetDCBrushColor(_hDC, RGB(255, 0, 0));
			Ellipse(_hDC, LONG(m_tInfo.fX) - m_iBoom, LONG(m_tInfo.fY) - m_iBoom, LONG(m_tInfo.fX) + m_iBoom, LONG(m_tInfo.fY) + m_iBoom);
		}
	}
	else
	{
		CPaint::Monster(_hDC, m_tInfo, m_tRect, m_tInfo.m_eType, m_tInfo.iHit);
	}
	SetDCBrushColor(_hDC, RGB(255, 255, 255));
}

void CMonster::Release(void)
{

}

void CMonster::Update_Nomal()
{

	if (m_tInfo.m_bDead)
	{
		m_iBoom += 2;
		return;
	}
		
	if (m_tInfo.fX > 1100)
	{
		m_tInfo.fX -= m_tInfo.fSpeed;
	}
	else
	{
		if (m_bTurn)
		{
			m_tInfo.fY += m_tInfo.fSpeed;
		}
		else
		{
			m_tInfo.fY -= m_tInfo.fSpeed;
		}
	}	

	if (m_tInfo.fX <= 1100)
	{
		if (MTime + 800 < GetTickCount())
		{
			m_Bulletlist->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 50, m_tInfo.fY, 180 * PI / 180));

			MTime = GetTickCount();
		}
	}
}

void CMonster::Update_Boom()
{
	if (m_tInfo.m_bDead)
	{
		m_iBoom += 2;
		return;
	}


	float fWidth = (m_tInfo.fToX - m_tInfo.fX);
	float fHeight = (m_tInfo.fToY - m_tInfo.fY);
	float fRadius = (fWidth*fWidth) + (fHeight*fHeight);
	float fDistance = sqrtf(fRadius);

	float _sinseta = asin(fHeight / fDistance);
	float _cosseta = acos(fWidth / fDistance);
	m_tInfo.fY += sinf(_sinseta)*m_tInfo.fSpeed;
	m_tInfo.fX += cosf(_cosseta)*m_tInfo.fSpeed;
}

void CMonster::Update_Boss()
{
	
	if (m_tInfo.fX > 1000)
	{
		m_tInfo.fX -= m_tInfo.fSpeed;
	}
	else
	{
		
		if (m_bTurn)
		{
			//m_tInfo.fY += m_tInfo.fSpeed;
		}
		else
		{
			//m_tInfo.fY -= m_tInfo.fSpeed;
		}
	}

	//º¸½º ÃÑ¾Ë ÆÐÅÏ
	if (m_tInfo.fX <= 1100)
	{
		switch (m_BPattern)
		{
		case MACHINEGUN:
		{
			if (MTime + 100 < GetTickCount())
			{				
				if (!m_bTurn)
				{
					m_tInfo.fAngle -= 5.f;
					if (m_tInfo.fAngle <= 120.f)
					{
						m_bTurn = true;
					}
				}
				else
				{
					m_tInfo.fAngle += 5.f;
					if (m_tInfo.fAngle >= 240.f)
					{
						m_bTurn = false;
					}
				}
				
				m_Bulletlist->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY+70, m_tInfo.fAngle * (PI / 180.f)));

				MTime = GetTickCount();
			}
		}
			break;

		case SHOTGUN:
		{
			if (MTime + 1000 < GetTickCount())
			{
				m_tInfo.fAngle = 150.f;
				for (int i = 0; i < 12; ++i)
				{
					m_tInfo.fAngle += 5.f;
					m_Bulletlist->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY + 70, m_tInfo.fAngle * (PI / 180.f)));
					
				}
				MTime = GetTickCount();
			}
		}
			break;

		case GUIDED:
		{
			if (MTime + 2000 < GetTickCount())
			{
				m_tInfo.fAngle = 150.f;
				for (int i = 0; i < 12; ++i)
				{
					m_tInfo.fAngle += 5.f;
					m_Bulletlist->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY + 70, m_tInfo.fAngle * (PI / 180.f)));
					
					m_Bulletlist->back()->Set_ToPos(m_tInfo.fToX, m_tInfo.fToY);
					static_cast<CBullet*>(m_Bulletlist->back())->Set_Shot(m_tInfo.fX, m_tInfo.fX -m_tInfo.fToX);
				}
				MTime = GetTickCount();
			}
		}
			break;
		}
	}
}


void CMonster::Update_Pattern()
{
	if (m_BPattern == SHOTGUN)
	{
		m_BPattern = GUIDED;
	}
	else if (m_BPattern == GUIDED)
	{
		m_tInfo.fAngle = 115.f;
		m_BPattern = MACHINEGUN;
	}
	else if (m_BPattern == MACHINEGUN)
	{
		m_tInfo.fAngle = 115.f;
		m_BPattern = SHOTGUN;
	}
}

int CMonster::Get_Random()
{
	random_device random;
	mt19937 rd(random());
	uniform_int_distribution<int> range(1, 10);
	int _rand = range(random);
	return _rand;
}