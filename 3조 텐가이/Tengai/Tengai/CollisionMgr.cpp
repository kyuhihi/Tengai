#include "stdafx.h"
#include "CollisionMgr.h"
#include "Player.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				if (Dest->Get_Hp() > 0 && Sour->Get_Hp() > 0)
				{
					Dest->Plus_Hp(-1);
					Sour->Plus_Hp(-1);
					if (Sour->Get_Type() == BOSS)
					{
						bosshit += 1;
					}
					Sour->Set_Hit_Color(10);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Player_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				if (Dest->Get_Hp() > 0 && Sour->Get_Hp() > 0)
				{
					Dest->Plus_Hp(-1);
					Sour->Plus_Hp(-1);
					hit += 1;
					Sour->Set_Hit_Color(10);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Item_Player_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT        rc{};

	for (auto& Player : _Dest)
	{
		for (auto& Item : _Sour)
		{
			if (IntersectRect(&rc, &(Player->Get_Rect()), &(Item->Get_Rect())))
			{
				//플레이어 아이템 충돌.
				Item->Set_Dead();
				
				TYPE PlayerNewItem(Item->Get_Type());

				dynamic_cast<CPlayer*> (Player)->PickItem(PlayerNewItem);

			}
		}
	}
}


void CCollisionMgr::Collision_Mon_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				if (Dest->Get_Hp() > 0 && Sour->Get_Hp() > 0)
				{
					if (Sour->Get_Type() == BOOM)
					{
						Dest->Plus_Hp(-1);
						Sour->Plus_Hp(-10);
						hit += 1;
					}
					else
					{
						Dest->Plus_Hp(-1);
						hit += 1;
					}
					Dest->Set_Hit_Color(10);
				}
			}
		}
	}
}