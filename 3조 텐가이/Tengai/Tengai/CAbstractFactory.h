#pragma once
#include "Obj.h"

template <typename T>
class CAbstractFactory
{
public:
	CAbstractFactory()
	{
	}

	~CAbstractFactory()
	{
	}

public:
	static CObj* Create()
	{
		CObj* _Temp = new T;
		_Temp->Initialize();
		return _Temp;
	}

	static CObj* Create(float _fX, float _fY, TYPE _eType)
	{
		CObj* _Temp = new T;
		_Temp->Set_Type(_eType);
		_Temp->Set_Pos(_fX, _fY);
		_Temp->Initialize();
		return _Temp;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle, bool _bPlayer_Bullet)
	{
		CObj* _Temp = new T;
		_Temp->Set_Angle(_fAngle);
		_Temp->Set_Pos(_fX, _fY);
		_Temp->Set_Player_Bullet(_bPlayer_Bullet);
		_Temp->Initialize();
		return _Temp;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle)
	{
		CObj* _Temp = new T;
		_Temp->Initialize();
		_Temp->Set_Angle(_fAngle);
		_Temp->Set_Pos(_fX, _fY);
		return _Temp;
	}
};