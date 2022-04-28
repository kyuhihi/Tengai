#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Player_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Mon_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void     Collision_Item_Player_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
};

