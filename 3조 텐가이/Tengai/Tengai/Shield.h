#pragma once
#include "Obj.h"
class CShield :
	public CObj
{
public:
	CShield();
	virtual ~CShield();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;
	void	SetPlayerInfo(INFO* _tPlayer, float Angle);
private:
	INFO* m_PlayerXY;
	float m_PlayerAngle;

	float fDiagonalTemp;
};

