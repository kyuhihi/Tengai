#pragma once
#include "Obj.h"
#include "Paint.h"
#include "Bullet.h"
#include "Item.h"

class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

	void Update_Nomal();
	void Update_Boom();
	void Update_Boss();

	void Update_Pattern();

	void Set_BulletList(list<CObj*>* pBullet) { m_Bulletlist = pBullet; }
	void Set_ItemList(list<CObj*>* _Itemlist) { m_Itemlist = _Itemlist; }

	int Get_Random();

	void Set_Turn()
	{
		if (m_bTurn)
			m_bTurn = false;
		else
			m_bTurn = true;
	}

private:
	int m_iBoom;

	bool m_bTurn;
	

	BOSSPATTERN m_BPattern;

	DWORD m_BossPatternTime;

	TCHAR BossHp[60];

	list<CObj*>* m_Bulletlist;

	list<CObj*>* m_Itemlist;
	DWORD MTime;
};