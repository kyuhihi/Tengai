#include "stdafx.h"
#include "ClearPage.h"


CClearPage::CClearPage()
{
	random_device rd;
	mt19937_64 rng(rd());
	uniform_int_distribution<__int64> dist1(10, 1200);
	uniform_int_distribution<__int64> dist2(10, 700);

	for (int i = 0; i < 20; ++i)
	{
		m_Random_XY.x = long(dist1(rng));
		m_Random_XY.y = long(dist2(rng));
		Random_Rect_Set(i);
	}
}


CClearPage::~CClearPage()
{
}


void CClearPage::Update(void)
{
	Random_Rect_Update();
}

void CClearPage::Render()
{
	HDC hDC = GetDC(g_hWnd);
	ShowCursor(true);
	Rectangle(hDC, 0, 0, WINCX, WINCY);//초기화
	for (int i = 0; i < 20; ++i)
	{
		Rectangle(hDC, m_Random_Rect[i].left, m_Random_Rect[i].top, m_Random_Rect[i].right, m_Random_Rect[i].bottom);
	}

	MoveToEx(hDC, 330, 250, nullptr);
	LineTo(hDC, 380, 200);
	MoveToEx(hDC, 380, 200, nullptr);
	LineTo(hDC, 380, 350);
	MoveToEx(hDC, 330, 350, nullptr);
	LineTo(hDC, 430, 350);
	Ellipse(hDC, 480, 200, 530, 350);
	MoveToEx(hDC, 580, 200, nullptr);
	LineTo(hDC, 680, 200);
	MoveToEx(hDC, 680, 200, nullptr);
	LineTo(hDC, 580, 350);
	MoveToEx(hDC, 700, 200, nullptr);
	LineTo(hDC, 700, 350);
	MoveToEx(hDC, 700, 250, nullptr);
	LineTo(hDC, 730, 250);
	Ellipse(hDC, 780, 200, 830, 350);
	MoveToEx(hDC, 880, 200, nullptr);
	LineTo(hDC, 880, 350);

	TextOut(hDC, 620, 585, TEXT("감사합니다"), 5);

}

void CClearPage::Random_Rect_Set(int iNumber)
{
	m_Random_Rect[iNumber].left = m_Random_XY.x - 10;
	m_Random_Rect[iNumber].top = m_Random_XY.y - 10;
	m_Random_Rect[iNumber].right = m_Random_XY.x + 10;
	m_Random_Rect[iNumber].bottom = m_Random_XY.y + 10;
}

void CClearPage::Random_Rect_Update()
{
	for (int i = 0; i < 20; ++i) {
		m_Random_Rect[i].left -= 3;
		m_Random_Rect[i].right -= 3;
		m_Random_Rect[i].top += 3;
		m_Random_Rect[i].bottom += 3;
		if ((m_Random_Rect[i].left <= 0) || (m_Random_Rect[i].bottom > WINCY)) {
			m_Random_Rect[i].left = WINCX;
			m_Random_Rect[i].right = WINCX + 20;
			m_Random_Rect[i].top = WINCY;
			m_Random_Rect[i].bottom = WINCY + 20;

		}
	}
}
