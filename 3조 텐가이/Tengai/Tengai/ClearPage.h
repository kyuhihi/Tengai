#pragma once
#include <random>

class CClearPage
{
public:
	CClearPage();
	~CClearPage();
public:
	void    Update(void);
	void    Render();

	void    Random_Rect_Set(int);
	void    Random_Rect_Update();
private:


	RECT    m_Random_Rect[20];
	POINT    m_Random_XY;

};

