#include "stdafx.h"
#include "Paint.h"


void CPaint::Initialize(void)
{
}

int CPaint::Update(void)
{
	return 0;
}

void CPaint::Late_Update(void)
{
}

void CPaint::Render(HDC _hDC)
{
}

void CPaint::Release(void)
{
}

CPaint::CPaint()
{
}


CPaint::~CPaint()
{
}



void CPaint::Player(HDC m_hDC, INFO& m_tInfo, RECT& m_tRect)
{
	float rate = 0.7f;

	

	MoveToEx(m_hDC, LONG(m_tInfo.fX), LONG(m_tInfo.fY),nullptr);
	LineTo(m_hDC, LONG(m_tInfo.fX)-(15* rate), LONG(m_tInfo.fY) + (50* rate));
	MoveToEx(m_hDC, LONG(m_tInfo.fX), LONG(m_tInfo.fY), nullptr);
	LineTo(m_hDC, LONG(m_tInfo.fX) + (15* rate), LONG(m_tInfo.fY) + (50* rate));
	MoveToEx(m_hDC, LONG(m_tInfo.fX), LONG(m_tInfo.fY), nullptr);
	LineTo(m_hDC, LONG(m_tInfo.fX) - (40* rate), LONG(m_tInfo.fY) + (10*rate));
	MoveToEx(m_hDC, LONG(m_tInfo.fX), LONG(m_tInfo.fY), nullptr);
	LineTo(m_hDC, LONG(m_tInfo.fX), LONG(m_tInfo.fY) - (30* rate));
	MoveToEx(m_hDC, LONG(m_tInfo.fX), LONG(m_tInfo.fY) - 30, nullptr);
	Ellipse(m_hDC, LONG(m_tInfo.fX) - (15* rate), LONG(m_tInfo.fY)-(45 * rate), LONG(m_tInfo.fX) + (15* rate), LONG(m_tInfo.fY)-(15* rate));

	m_tRect.left = LONG(m_tInfo.fX) - 25;
	m_tRect.right = LONG(m_tInfo.fX) + 25;
	m_tRect.top = LONG(m_tInfo.fY) - 35;
	m_tRect.bottom = LONG(m_tInfo.fY) + 35;

	//Rectangle(m_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPaint::Posin(HDC m_hDC, INFO& m_Posin)
{
	float rate = 0.7f;
	MoveToEx(m_hDC, LONG(m_Posin.fX), LONG(m_Posin.fY), nullptr);
	LineTo(m_hDC, LONG(m_Posin.fX + cos(m_Posin.fAngle) * 50 * rate) , LONG(m_Posin.fY + sin(m_Posin.fAngle) * 50 * rate));
	m_Posin.fX += cos(m_Posin.fAngle) * 50;
	m_Posin.fY += sin(m_Posin.fAngle) * 50;
}


void CPaint::Bullet(HDC m_hDC, INFO& m_tInfo, RECT& m_tRect)
{
	if (m_tInfo._bPlayer_Bullet == true)
	{
		int iChange = -5;
		int iMagn = 1;
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + (iChange * iMagn), LONG(m_tInfo.fY) + (iChange* iMagn), nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + ((16 + iChange)* iMagn), LONG(m_tInfo.fY) + ((6 + iChange)* iMagn));

		MoveToEx(m_hDC, LONG(m_tInfo.fX) + ((16 + iChange)* iMagn), LONG(m_tInfo.fY) + ((6 + iChange)* iMagn), nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 0 + iChange, LONG(m_tInfo.fY) + 10 + iChange);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 0 + iChange, LONG(m_tInfo.fY) + 10 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 8 + iChange, LONG(m_tInfo.fY) + 5 + iChange);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 8 + iChange, LONG(m_tInfo.fY) + 5 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 0 + iChange, LONG(m_tInfo.fY) + 0 + iChange);

		m_tRect.left = LONG(m_tInfo.fX) - 5;
		m_tRect.right = LONG(m_tInfo.fX) + 5;
		m_tRect.top = LONG(m_tInfo.fY) - 5;
		m_tRect.bottom = LONG(m_tInfo.fY) + 5;
	}
	else
	{
		m_tRect.left = LONG(m_tInfo.fX) - 5;
		m_tRect.right = LONG(m_tInfo.fX) + 5;
		m_tRect.top = LONG(m_tInfo.fY) - 5;
		m_tRect.bottom = LONG(m_tInfo.fY) + 5;
		Ellipse(m_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CPaint::Monster(HDC m_hDC, INFO& m_tInfo, RECT& m_tRect, TYPE _MonsterType, int _Hit_Color)
{
	
	switch(_MonsterType)
	{
	case NOMAL:
		if (_Hit_Color > 0)
		{
			Ellipse(m_hDC, LONG(m_tInfo.fX) - 125 + 110, LONG(m_tInfo.fY) - 125 + 110, LONG(m_tInfo.fX) - 80 + 140, LONG(m_tInfo.fY) - 125 + 140);
			Rectangle(m_hDC, LONG(m_tInfo.fX) - 125 + 80, LONG(m_tInfo.fY) - 125 + 115, LONG(m_tInfo.fX) - 125 + 120, LONG(m_tInfo.fY) - 125 + 135);
			Rectangle(m_hDC, LONG(m_tInfo.fX) - 125 + 90, LONG(m_tInfo.fY) - 125 + 110, LONG(m_tInfo.fX) - 125 + 140, LONG(m_tInfo.fY) - 125 + 140);
			Rectangle(m_hDC, LONG(m_tInfo.fX) - 125 + 100, LONG(m_tInfo.fY) - 125 + 100, LONG(m_tInfo.fX) - 125 + 150, LONG(m_tInfo.fY) - 125 + 150);
			Rectangle(m_hDC, LONG(m_tInfo.fX) - 125 + 110, LONG(m_tInfo.fY) - 125 + 110, LONG(m_tInfo.fX) - 125 + 140, LONG(m_tInfo.fY) - 125 + 140);
		}
		else
		{
			SelectObject(m_hDC, GetStockObject(DC_BRUSH));
			SetDCBrushColor(m_hDC, RGB(255, 0, 0));
			Ellipse(m_hDC, LONG(m_tInfo.fX) - 125 + 110, LONG(m_tInfo.fY) - 125 + 110, LONG(m_tInfo.fX) - 80 + 140, LONG(m_tInfo.fY) - 125 + 140);
			SetDCBrushColor(m_hDC, RGB(220, 250, 130));
			Rectangle(m_hDC, LONG(m_tInfo.fX) - 125 + 80, LONG(m_tInfo.fY) - 125 + 115, LONG(m_tInfo.fX) - 125 + 120, LONG(m_tInfo.fY) - 125 + 135);
			SetDCBrushColor(m_hDC, RGB(0, 0, 255));
			Rectangle(m_hDC, LONG(m_tInfo.fX) - 125 + 90, LONG(m_tInfo.fY) - 125 + 110, LONG(m_tInfo.fX) - 125 + 140, LONG(m_tInfo.fY) - 125 + 140);
			SetDCBrushColor(m_hDC, RGB(255, 212, 0));
			Rectangle(m_hDC, LONG(m_tInfo.fX) - 125 + 100, LONG(m_tInfo.fY) - 125 + 100, LONG(m_tInfo.fX) - 125 + 150, LONG(m_tInfo.fY) - 125 + 150);
			SetDCBrushColor(m_hDC, RGB(245, 102, 150));
			Rectangle(m_hDC, LONG(m_tInfo.fX) - 125 + 110, LONG(m_tInfo.fY) - 125 + 110, LONG(m_tInfo.fX) - 125 + 140, LONG(m_tInfo.fY) - 125 + 140);

			SetDCBrushColor(m_hDC, RGB(255, 255, 255));
		}

		MoveToEx(m_hDC, LONG(m_tInfo.fX) - 125 + 110, LONG(m_tInfo.fY) - 125 + 100, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) - 125 + 150, LONG(m_tInfo.fY) - 125 + 80);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) - 125 + 150, LONG(m_tInfo.fY) - 125 + 80, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) - 125 + 140, LONG(m_tInfo.fY) - 125 + 100);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) - 125 + 110, LONG(m_tInfo.fY) - 125 + 150, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) - 125 + 150, LONG(m_tInfo.fY) - 125 + 170);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) - 125 + 150, LONG(m_tInfo.fY) - 125 + 170, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) - 125 + 140, LONG(m_tInfo.fY) - 125 + 150);

		m_tRect.left = LONG(m_tInfo.fX) - 20;
		m_tRect.right = LONG(m_tInfo.fX) + 20;
		m_tRect.top = LONG(m_tInfo.fY) - 20;
		m_tRect.bottom = LONG(m_tInfo.fY) + 20;

		//Rectangle(m_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		break;

	case BOSS:
	{
		int iChange = 80;
		
		
		
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 50, LONG(m_tInfo.fY) - 110 + 200, LONG(m_tInfo.fX) + iChange + 30, LONG(m_tInfo.fY) - 70 + 200);
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 190, LONG(m_tInfo.fY) - 110 + 200, LONG(m_tInfo.fX) + iChange - 110, LONG(m_tInfo.fY) - 70 + 200);
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 205, LONG(m_tInfo.fY) - 335 + 200, LONG(m_tInfo.fX) + iChange - 155, LONG(m_tInfo.fY) - 150 + 200);
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange + 0, LONG(m_tInfo.fY) - 340 + 200, LONG(m_tInfo.fX) + iChange + 45, LONG(m_tInfo.fY) - 190 + 200);
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 200, LONG(m_tInfo.fY) - 320 + 200, LONG(m_tInfo.fX) + iChange + 40, LONG(m_tInfo.fY) - 80 + 200);
		


		//´«
		SetDCBrushColor(m_hDC, RGB(255, 255, 255));
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 55, LONG(m_tInfo.fY) - 190 + 200, LONG(m_tInfo.fX) + iChange - 20, LONG(m_tInfo.fY) - 280 + 200);
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 145, LONG(m_tInfo.fY) - 190 + 200, LONG(m_tInfo.fX) + iChange - 110, LONG(m_tInfo.fY) - 280 + 200);

		//´«µ¿ÀÚ
		SetDCBrushColor(m_hDC, RGB(0, 0, 0));
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 50, LONG(m_tInfo.fY) - 235 + 200, LONG(m_tInfo.fX) + iChange - 25, LONG(m_tInfo.fY) - 275 + 200);
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 140, LONG(m_tInfo.fY) - 235 + 200, LONG(m_tInfo.fX) + iChange - 115, LONG(m_tInfo.fY) - 275 + 200);

		
		//ÀÔ
		SetDCBrushColor(m_hDC, RGB(255, 255, 255));
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 160, LONG(m_tInfo.fY) - 190 + 200, LONG(m_tInfo.fX) + iChange - 10, LONG(m_tInfo.fY) - 90 + 200);
		Ellipse(m_hDC, LONG(m_tInfo.fX) + iChange - 145, LONG(m_tInfo.fY) - 160 + 200, LONG(m_tInfo.fX) + iChange - 25, LONG(m_tInfo.fY) - 93 + 200);

		
		
		m_tRect.left = LONG(m_tInfo.fX) - 100;
		m_tRect.right = LONG(m_tInfo.fX) + 100;
		m_tRect.top = LONG(m_tInfo.fY) - 100;
		m_tRect.bottom = LONG(m_tInfo.fY) + 100;

		//Rectangle(m_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
		
		break;

	case BOOM:
	{
		int iChange = -20;
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 10 + iChange, LONG(m_tInfo.fY) + 1 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 30 + iChange, LONG(m_tInfo.fY) + 1 + iChange);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 30 + iChange, LONG(m_tInfo.fY) + 1 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 20 + iChange, LONG(m_tInfo.fY) + 20 + iChange);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 20 + iChange, LONG(m_tInfo.fY) + 20 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 10 + iChange, LONG(m_tInfo.fY) + 1 + iChange);


		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 16 + iChange, LONG(m_tInfo.fY) + 30 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 32 + iChange, LONG(m_tInfo.fY) + 30 + iChange);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 32 + iChange, LONG(m_tInfo.fY) + 30 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 25 + iChange, LONG(m_tInfo.fY) + 40 + iChange);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 25 + iChange, LONG(m_tInfo.fY) + 40 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 3 + iChange, LONG(m_tInfo.fY) + 40 + iChange);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 3 + iChange, LONG(m_tInfo.fY) + 40 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 17 + iChange, LONG(m_tInfo.fY) + 30 + iChange);

		Ellipse(m_hDC, LONG(m_tInfo.fX) + 0 + iChange, LONG(m_tInfo.fY) + 10 + iChange, LONG(m_tInfo.fX) + 45 + iChange, LONG(m_tInfo.fY) + 35 + iChange);
		Ellipse(m_hDC, LONG(m_tInfo.fX) + 2 + iChange, LONG(m_tInfo.fY) + 15 + iChange, LONG(m_tInfo.fX) + 20 + iChange, LONG(m_tInfo.fY) + 31 + iChange);

		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 30 + iChange, LONG(m_tInfo.fY) + 20 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 45 + iChange, LONG(m_tInfo.fY) + 34 + iChange);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 45 + iChange, LONG(m_tInfo.fY) + 34 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 15 + iChange, LONG(m_tInfo.fY) + 34 + iChange);
		MoveToEx(m_hDC, LONG(m_tInfo.fX) + 15 + iChange, LONG(m_tInfo.fY) + 34 + iChange, nullptr);
		LineTo(m_hDC, LONG(m_tInfo.fX) + 30 + iChange, LONG(m_tInfo.fY) + 20 + iChange);

		m_tRect.left = LONG(m_tInfo.fX) - 15;
		m_tRect.right = LONG(m_tInfo.fX) + 15;
		m_tRect.top = LONG(m_tInfo.fY) - 15;
		m_tRect.bottom = LONG(m_tInfo.fY) + 15;

		//Rectangle(m_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}	
		break;
	}
}

void CPaint::Item(HDC m_hDC, INFO& m_tInfo, RECT& m_tRect, TYPE _ItemType)
{
	m_tRect.left = LONG(m_tInfo.fX) - 15;
	m_tRect.right = LONG(m_tInfo.fX) + 15;
	m_tRect.top = LONG(m_tInfo.fY) - 15;
	m_tRect.bottom = LONG(m_tInfo.fY) + 15;


	SelectObject(m_hDC, GetStockObject(DC_BRUSH));
	if (_ItemType == SHIELD) {//ÆÄ¶û
		SetDCBrushColor(m_hDC, RGB(0, 0, 255));
	}
	else if (_ItemType == PORTION)
	{//»¡°­
		SetDCBrushColor(m_hDC, RGB(255, 0, 0));
	}
	else if (_ItemType == QUANTITY)
	{//ÃÊ·Ï
		SetDCBrushColor(m_hDC, RGB(0, 255, 0));
	}
	else if (_ItemType == ATSPEED)
	{//³ë¶û
		SetDCBrushColor(m_hDC, RGB(255, 212, 0));
	}

	Rectangle(m_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SetDCBrushColor(m_hDC, RGB(255, 255, 255));
}

void CPaint::ItemShield(HDC m_hDC, INFO& m_tInfo, INFO* PlayerInfo, RECT& m_tRect, float& fShieldAngle)
{

	m_tRect.left = LONG(m_tInfo.fX) - 10;
	m_tRect.right = LONG(m_tInfo.fX) + 10;
	m_tRect.top = LONG(m_tInfo.fY) - 10;
	m_tRect.bottom = LONG(m_tInfo.fY) + 10;
	
	Ellipse(m_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//¸®¾ó È÷Æ®¹Ú½º.
	Ellipse(m_hDC, m_tRect.left + 3, m_tRect.top + 3, m_tRect.right - 3, m_tRect.bottom - 3);//¾È¿¡ÀÛÀº¿ø
}