#pragma once
class CGameOver
{
public:
	CGameOver();
	~CGameOver();

	int    Update(void);
	void    Render();
	void    Mouse_Rect_Update();
	void    Random_Rect_Set(int);
	void    Random_Rect_Update();
private:
	RECT    m_RESTART_RECT;
	RECT    m_Mouse_Rect;
	INFO    m_Mouse_Info;

	RECT    m_Random_Rect[20];
	POINT    m_Random_XY;
};

