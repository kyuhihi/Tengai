#include "stdafx.h"
#include "Item.h"
#include "Paint.h"


CItem::CItem()
{
}

CItem::~CItem()
{
}

void CItem::Initialize(void)
{//�׳� ���ٴϴ°�
	m_tInfo.fSpeed = 5.f;
}

int CItem::Update(void)
{
	if (m_tInfo.m_bDead == true)
		return OBJ_DEAD;
	
	m_tInfo.fX -= m_tInfo.fSpeed;

	return OBJ_ALIVE;
}

void CItem::Late_Update(void)
{
	if ((m_tInfo.fX - m_tInfo.fCX < 0) || (m_tInfo.fX + m_tInfo.fCX > WINCX))
		m_tInfo.m_bDead = true;
}

void CItem::Render(HDC _hDC)
{
	CPaint::Item(_hDC, m_tInfo, m_tRect, m_tInfo.m_eType);
}

void CItem::Release(void)
{
}

//void CItem::Initialize(TYPE t)
//{
//	// ����ٴϴ� ������
//	// 
//	m_tInfo.fCX = 20.f;
//	m_tInfo.fCY = 20.f;
//
//	m_tInfo.fSpeed = 5.f;
//	m_tInfo.m_eType = t;
//}
