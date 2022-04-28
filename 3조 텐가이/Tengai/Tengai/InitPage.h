#pragma once
#include <random>
class CInitPage
{
public:
	CInitPage();
	~CInitPage();
public:
	void    Initialize(void);
	void    Update(void);
	void    Render();
	int        GetStart();
	void    Mouse_Rect_Update();
	void    Random_Rect_Set(int);
	void    Random_Rect_Update();

private:
	RECT    m_START_RECT;
	RECT	m_Information_Rect;
	RECT	m_Back_Rect;

	RECT    m_Mouse_Rect;
	INFO    m_Mouse_Info;

	RECT    m_Random_Rect[20];
	POINT    m_Random_XY;

	POINT   m_MouseXY;
	int     m_bStart;

};