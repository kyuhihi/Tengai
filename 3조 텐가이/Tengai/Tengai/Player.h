#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:

	virtual        void    Initialize(void);
	virtual        int     Update(void);
	virtual        void    Late_Update(void);
	virtual        void    Render(HDC _hDC);
	virtual        void    Release(void);
	
public:
	void Set_BulletList(list<CObj*>* pBullet) { m_Bulletlist = pBullet; }
	void Set_Shield_List(list<CObj*>* pShield) { m_ShieldList = pShield; }
	void Key_Input();
	void PickItem(TYPE _Type);

	

private:

	int m_iAtSpeed;
	float m_fShieldAngle;
	int m_iBullet_Quantity;

	list<CObj*>* m_Bulletlist;
	list<CObj*>* m_ShieldList;
	INFO m_Posin;
	DWORD Time;

};

