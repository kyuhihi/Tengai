#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "CAbstractFactory.h"
#include "Functor.h"
#include "Monster.h"

DWORD WTime = GetTickCount();
TCHAR mName[30];
TCHAR tScore[10];
TCHAR Stop[30]; 
TCHAR PlayerHp[30];
TCHAR BOSSHp[60];
int Count;
int hit = 0;


CMainGame::CMainGame()
	: m_bStop(false)
{
}

CMainGame::~CMainGame()
{
}

void CMainGame::Initialize(void)
{
	m_Time = 0;
	m_Score = 0;
	m_Gen = 0;
	m_MTMax = 0;
	Count = 0;
	m_Obj_List[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	static_cast<CPlayer*>(m_Obj_List[OBJ_PLAYER].front())->Set_BulletList(&(m_Obj_List[OBJ_BULLET]));
	static_cast<CPlayer*>(m_Obj_List[OBJ_PLAYER].front())->Set_Shield_List(&(m_Obj_List[OBJ_PLAYER_SHIELD]));
	m_hDC = GetDC(g_hWnd);
}

int CMainGame::Update(void)
{
	KeyInput();
	
	if (!m_bStop)
	{
		Count += 1;
		if (Count == 64)
		{
			SetTime();
			SetGen();
			Count = 0;
		}
		if (m_Gen >= 1 && m_MTMax <= 5)
		{

			random_device random;
			mt19937 rd(random());
			uniform_int_distribution<int> range(1, 4);
			int Spon = random();

			random_device random_2;
			mt19937 rd_2(random_2());
			uniform_int_distribution<int> range_2(100, WINCY - 100);
			int _rand = range_2(random_2);


			if (Spon % 2 == 0 && m_Score < 500)
			{
				m_Obj_List[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(WINCX + 50, _rand, NOMAL));				
				dynamic_cast<CMonster*>(m_Obj_List[OBJ_MONSTER].back())->Set_BulletList(&(m_Obj_List[OBJ_MON_BULLET]));				
				dynamic_cast<CMonster*>(m_Obj_List[OBJ_MONSTER].back())->Set_ItemList(&(m_Obj_List[OBJ_ITEM]));
				m_Gen = 0;
				m_MTMax += 1;
			}
			else if(Spon % 2 == 1 && m_Score < 500)
			{
				m_Obj_List[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(WINCX + 50, _rand, BOOM));
				dynamic_cast<CMonster*>(m_Obj_List[OBJ_MONSTER].back())->Set_BulletList(&(m_Obj_List[OBJ_MON_BULLET]));
				dynamic_cast<CMonster*>(m_Obj_List[OBJ_MONSTER].back())->Set_ItemList(&(m_Obj_List[OBJ_ITEM]));
				m_Gen = 0;
				m_MTMax += 1;
			}

			else if (m_Score >= 500)
			{
				m_Obj_List[OBJ_MON_BULLET].clear();
				m_Obj_List[OBJ_MONSTER].clear();
				m_Obj_List[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(WINCX + 50, 300, BOSS));
				dynamic_cast<CMonster*>(m_Obj_List[OBJ_MONSTER].back())->Set_BulletList(&(m_Obj_List[OBJ_MON_BULLET]));
				m_Gen = 0;
				m_MTMax = 6;
			}


			
		}
	
		for (int i = 0; i < OBJ_END; ++i)
		{
			for (list<CObj*>::iterator& iter = m_Obj_List[i].begin(); iter != m_Obj_List[i].end();)
			{
				if ((*iter)->Update() == OBJ_DEAD)
				{
					if (i == OBJ_PLAYER)
					{
						return GAMEOVER; 
					}
					if (i == OBJ_MONSTER)
					{
						m_MTMax -= 1;
						switch ((*iter)->Get_Type())
						{
						case NOMAL:
							m_Score += 20;
							break;
							
						case BOOM:
							m_Score += 20;
							break;
						case BOSS:
							return GAMECLEAR;
							break;
						}
					}

					Safe_Delete<CObj*>(*iter);
					iter = m_Obj_List[i].erase(iter);

				}
				else
				{
					++iter;
				}
			}
		}
	}
	return	OBJ_ALIVE;
}

void CMainGame::Late_Update(void)
{
	if (!m_bStop)
	{
		CCollisionMgr::Collision_Rect(m_Obj_List[OBJ_BULLET], m_Obj_List[OBJ_MONSTER]);
		CCollisionMgr::Collision_Player_Rect(m_Obj_List[OBJ_MON_BULLET], m_Obj_List[OBJ_PLAYER]);
		CCollisionMgr::Collision_Mon_Rect(m_Obj_List[OBJ_PLAYER], m_Obj_List[OBJ_MONSTER]);
		CCollisionMgr::Collision_Item_Player_Rect(m_Obj_List[OBJ_PLAYER], m_Obj_List[OBJ_ITEM]);

		CCollisionMgr::Collision_Rect(m_Obj_List[OBJ_MON_BULLET], m_Obj_List[OBJ_PLAYER_SHIELD]);
		CCollisionMgr::Collision_Rect(m_Obj_List[OBJ_MONSTER], m_Obj_List[OBJ_PLAYER_SHIELD]);

		for (int i = 0; i < OBJ_END; ++i)
		{
			for (list<CObj*>::iterator& iter = m_Obj_List[i].begin(); iter != m_Obj_List[i].end(); ++iter)
			{
				if (i != OBJ_MON_BULLET)
				{
					(*iter)->Set_ToPos(m_Obj_List[OBJ_PLAYER].front()->Get_Info());
				}				
				(*iter)->Late_Update();
			}
		}
	}
	
	

}

void CMainGame::Render(void)
{
	if (!m_bStop)
	{
		Rectangle(m_hDC, 0, 0, WINCX, WINCY);
		Rectangle(m_hDC, WINCX, 0, WINCX + 100, WINCY);

		for (int i = 0; i < OBJ_END; ++i)
		{
			for (list<CObj*>::iterator& iter = m_Obj_List[i].begin(); iter != m_Obj_List[i].end(); ++iter)
			{
				(*iter)->Render(m_hDC);
			}
		}

		wsprintf(mName, TEXT("시간 : %d초"), m_Time);
		TextOut(m_hDC, 10, 10, mName, lstrlen(mName));

		wsprintf(tScore, TEXT("점수 : %d점"), m_Score);
		TextOut(m_hDC, 10, 30, tScore, lstrlen(tScore));

		SetBkColor(m_hDC, RGB(255, 0, 0));
		wsprintf(PlayerHp, TEXT("                    "));
		TextOut(m_hDC, LONG(m_Obj_List[OBJ_PLAYER].front()->Get_Info().fX-40), LONG(m_Obj_List[OBJ_PLAYER].front()->Get_Info().fY-70), PlayerHp, lstrlen(PlayerHp +(hit*2)));
		SetBkColor(m_hDC, RGB(255, 255, 255));

	}
	else
	{//m_bStop이 트루이면 그림은 다른걸그린다.
		Rectangle(m_hDC, 0, 0, WINCX, WINCY);
		TextOut(m_hDC, WINCX/2 -100, WINCY/2, TEXT("시간 정지입니다"), 8);
		TextOut(m_hDC, WINCX / 2 - 150, WINCY / 2 + 20 , TEXT("다시 재개하려면 R을 누르세요"), 16);


	}
}

void CMainGame::Release(void)
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator& iter = m_Obj_List[i].begin(); iter != m_Obj_List[i].end(); ++iter)
		{
			Safe_Delete<CObj*>(*iter);
		}
	}
	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::KeyInput()
{
	if (WTime + 150 < GetTickCount())
	{
		if (GetAsyncKeyState('R'))
		{
			if (m_bStop)
				m_bStop = false;
			else
				m_bStop = true;
		}
		WTime = GetTickCount();
	}
}