#include "stdafx.h"
#include "GameOver.h"


CGameOver::CGameOver()
{
	m_RESTART_RECT = { 540,WINCY/2 -20,740,WINCY/2 +20};
	m_Mouse_Info.fCX = 20;
	m_Mouse_Info.fCY = 20;
	m_Mouse_Info.fAngle = 1.f;
}


CGameOver::~CGameOver()
{
}

int CGameOver::Update(void)
{
	POINT    pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_Mouse_Info.fX = (LONG)pt.x;
	m_Mouse_Info.fY = (LONG)pt.y;
	m_Mouse_Info.fAngle += 5.f;
	Mouse_Rect_Update();
	if(GetAsyncKeyState(VK_LBUTTON)) {
		if ((m_Mouse_Info.fX > m_RESTART_RECT.left) && (m_Mouse_Info.fX < m_RESTART_RECT.right) && (m_Mouse_Info.fY > m_RESTART_RECT.top) && (m_Mouse_Info.fY < m_RESTART_RECT.bottom))
		{//스타트
			return GAMERESTART;
		}
	}
}

void CGameOver::Render()
{
	HDC hDC = GetDC(g_hWnd);
	ShowCursor(false);
	Rectangle(hDC, 0, 0, WINCX, WINCY);//초기화
	for (int i = 0; i < 20; ++i)
	{
		Rectangle(hDC, m_Random_Rect[i].left, m_Random_Rect[i].top, m_Random_Rect[i].right, m_Random_Rect[i].bottom);
	}
	Rectangle(hDC, m_RESTART_RECT.left, m_RESTART_RECT.top, m_RESTART_RECT.right, m_RESTART_RECT.bottom);
	TextOut(hDC, (m_RESTART_RECT.left+ m_RESTART_RECT.right)/2-50, 350, TEXT("다시시작할래?"), 7);
	Ellipse(hDC, m_Mouse_Rect.left, m_Mouse_Rect.top, m_Mouse_Rect.right, m_Mouse_Rect.bottom);//마우스

}



void CGameOver::Mouse_Rect_Update()
{
	m_Mouse_Rect.left = long(m_Mouse_Info.fX - m_Mouse_Info.fCX * cosf((m_Mouse_Info.fAngle * PI) / 180.f));
	m_Mouse_Rect.top = long(m_Mouse_Info.fY - m_Mouse_Info.fCX * sinf((m_Mouse_Info.fAngle * PI) / 180.f));
	m_Mouse_Rect.right = long(m_Mouse_Info.fX + m_Mouse_Info.fCX * cosf((m_Mouse_Info.fAngle * PI) / 180.f));
	m_Mouse_Rect.bottom = long(m_Mouse_Info.fY + m_Mouse_Info.fCX * sinf((m_Mouse_Info.fAngle * PI) / 180.f));
}

void CGameOver::Random_Rect_Set(int iNumber)
{
	m_Random_Rect[iNumber].left = m_Random_XY.x - 10;
	m_Random_Rect[iNumber].top = m_Random_XY.y - 10;
	m_Random_Rect[iNumber].right = m_Random_XY.x + 10;
	m_Random_Rect[iNumber].bottom = m_Random_XY.y + 10;
}

void CGameOver::Random_Rect_Update()
{
	for (int i = 0; i < 20; ++i) {
		m_Random_Rect[i].left -= 3;
		m_Random_Rect[i].right -= 3;
		if (m_Random_Rect[i].left <= 0) {
			m_Random_Rect[i].left = WINCX;
			m_Random_Rect[i].right = WINCX + 20;

		}
	}
}
