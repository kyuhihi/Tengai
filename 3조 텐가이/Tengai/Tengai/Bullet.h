#pragma once
#include "Obj.h"
#include "Paint.h"

class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	void Set_Turn() { m_bTurn = true; };
	void Set_Shot(float _X, float _Y) { m_BossShot_X = _X; m_BossShot_Y = _Y; };

private:
	bool m_bTurn;

	bool m_bPlayer_Bullet;

	float m_BossShot_X;
	float m_BossShot_Y;

	float _sinseta;
	float _cosseta;
};