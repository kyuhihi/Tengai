#include "stdafx.h"
#include "InitPage.h"
#include "Paint.h"

CInitPage::CInitPage()
{
	Initialize();
}


CInitPage::~CInitPage()
{

}

void CInitPage::Initialize(void)
{
	m_bStart = 0;
	m_START_RECT = { 540,550,740,630 };
	m_Information_Rect = { 830,550,950,630 };
	m_Back_Rect = { 340,550,440,630 };
	m_Mouse_Info.fCX = 20;
	m_Mouse_Info.fCY = 20;
	m_Mouse_Info.fAngle = 1.f;

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

void CInitPage::Update(void)
{
	POINT    pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_MouseXY.x = (LONG)pt.x;
	m_MouseXY.y = (LONG)pt.y;
	m_Mouse_Info.fAngle += 5.f;
	Mouse_Rect_Update();
	Random_Rect_Update();
	if (GetAsyncKeyState(VK_LBUTTON)) {
		if ((m_MouseXY.x > m_START_RECT.left) && (m_MouseXY.x < m_START_RECT.right) && (m_MouseXY.y > m_START_RECT.top) && (m_MouseXY.y < m_START_RECT.bottom))
		{//��ŸƮ
			m_bStart = 1;
		}
		else if ((m_MouseXY.x > m_Information_Rect.left) && (m_MouseXY.x < m_Information_Rect.right) && (m_MouseXY.y > m_Information_Rect.top) && (m_MouseXY.y < m_Information_Rect.bottom))
		{//�������̼� â ������
			m_bStart = 2;

		}
		else if ((m_MouseXY.x > m_Back_Rect.left) && (m_MouseXY.x < m_Back_Rect.right) && (m_MouseXY.y > m_Back_Rect.top) && (m_MouseXY.y < m_Back_Rect.bottom))
		{//�������̼� â �����ٰ� �ڷΰ���
			m_bStart = 0;

		}

	}
}

void CInitPage::Render()
{
	HDC hDC = GetDC(g_hWnd);
	ShowCursor(false);
	Rectangle(hDC, 0, 0, WINCX, WINCY);//�ʱ�ȭ
	if (m_bStart == 0) {
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

		Rectangle(hDC, m_START_RECT.left, m_START_RECT.top, m_START_RECT.right, m_START_RECT.bottom);//��ŸƮ �׸�


		Rectangle(hDC, m_Information_Rect.left, m_Information_Rect.top, m_Information_Rect.right, m_Information_Rect.bottom);//�����ۼ��� �׸�
		TextOut(hDC, 860, 585, TEXT("ITEM INFO"), 9);
		TextOut(hDC, 620, 585, TEXT("START"), 5);
	}
	else if (m_bStart == 2)
	{//����â
		Rectangle(hDC, 150, 100, 250, 200);
		Rectangle(hDC, 170, 120, 230, 180);//������
		TextOut(hDC, 173, 140, TEXT("������"), 3);

		SelectObject(hDC, GetStockObject(DC_BRUSH));
		if (SetDCBrushColor(hDC, RGB(255, 0, 0)))
		{
			TextOut(hDC, 290, 112, TEXT(": �÷��̾� hp��ȸ���Ѵ�"), 14);
			Rectangle(hDC, 265, 110, 285, 130);
			SetDCBrushColor(hDC, RGB(255, 255, 255));
		}
		if (SetDCBrushColor(hDC, RGB(0, 0, 255)))
		{
			TextOut(hDC, 290, 132, TEXT(": �÷��̾� ������ ���带 �����Ѵ�"), 19);
			Rectangle(hDC, 265, 131, 285, 151);
			SetDCBrushColor(hDC, RGB(255, 255, 255));
		}
		if (SetDCBrushColor(hDC, RGB(255, 212, 0)))
		{
			TextOut(hDC, 290, 154, TEXT(": �Ѿ��� �ӵ��� 2���̴�"), 14);
			Rectangle(hDC, 265, 152, 285, 172);
			SetDCBrushColor(hDC, RGB(255, 255, 255));
		}
		if (SetDCBrushColor(hDC, RGB(29, 219, 22)))
		{
			TextOut(hDC, 290, 175, TEXT(": �Ѿ��� ������ �����Ѵ�"), 14);
			Rectangle(hDC, 265, 174, 285, 194);
			SetDCBrushColor(hDC, RGB(255, 255, 255));
		}


		Rectangle(hDC, 150, 280, 250, 380);//Ű���弳��
		TextOut(hDC, 173, 325, TEXT("Ű�Է�"), 3);
		TextOut(hDC, 275, 290, TEXT("Z: �ѱ��� �ϴ��� ���� �ö󰩴ϴ�."), 20);
		TextOut(hDC, 275, 310, TEXT("X: �ѱ��� �ٴ��� ���� �������ϴ�."), 20);
		TextOut(hDC, 275, 330, TEXT("SPACE��: �Ѿ��� �������ϴ�."), 18);
		TextOut(hDC, 275, 350, TEXT("R: ������ �Ͻ����� �մϴ�."), 16);

		INFO Temp;
		RECT Dummy;
		Temp.fX = 800.f;
		Temp.fY = 150.f;
		CPaint::Monster(hDC, Temp, Dummy, NOMAL, -1);
		TextOut(hDC, 900, 145, TEXT("����"), 3);

		Temp.fX = 800.f;
		Temp.fY = 350.f;
		CPaint::Player(hDC, Temp, Dummy);
		MoveToEx(hDC, Temp.fX, Temp.fY, nullptr);
		LineTo(hDC, 830, 320);
		TextOut(hDC, 900, 350, TEXT("�÷��̾�"), 4);


		Rectangle(hDC, m_START_RECT.left, m_START_RECT.top, m_START_RECT.right, m_START_RECT.bottom);//��ŸƮ �׸�
		TextOut(hDC, 600, 585, TEXT("�����غ���"), 5);


		Rectangle(hDC, m_Back_Rect.left, m_Back_Rect.top, m_Back_Rect.right, m_Back_Rect.bottom);//�ڷΰ���
		TextOut(hDC, 355, 585, TEXT("�ڷΰ���?"), 5);


	}
	Ellipse(hDC, m_Mouse_Rect.left, m_Mouse_Rect.top, m_Mouse_Rect.right, m_Mouse_Rect.bottom);//���콺
}


int CInitPage::GetStart()
{
	return m_bStart;
}

void CInitPage::Mouse_Rect_Update()
{
	m_Mouse_Rect.left = long(m_MouseXY.x - m_Mouse_Info.fCX * cosf((m_Mouse_Info.fAngle * PI) / 180.f));
	m_Mouse_Rect.top = long(m_MouseXY.y - m_Mouse_Info.fCX * sinf((m_Mouse_Info.fAngle * PI) / 180.f));
	m_Mouse_Rect.right = long(m_MouseXY.x + m_Mouse_Info.fCX * cosf((m_Mouse_Info.fAngle * PI) / 180.f));
	m_Mouse_Rect.bottom = long(m_MouseXY.y + m_Mouse_Info.fCX * sinf((m_Mouse_Info.fAngle * PI) / 180.f));
}

void CInitPage::Random_Rect_Set(int iNumber)
{
	m_Random_Rect[iNumber].left = m_Random_XY.x - 10;
	m_Random_Rect[iNumber].top = m_Random_XY.y - 10;
	m_Random_Rect[iNumber].right = m_Random_XY.x + 10;
	m_Random_Rect[iNumber].bottom = m_Random_XY.y + 10;
}

void CInitPage::Random_Rect_Update()
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