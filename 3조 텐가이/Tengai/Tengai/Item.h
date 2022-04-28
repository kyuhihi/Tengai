#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	~CItem();

public:
	virtual void Initialize(void) override;

	//virtual	void Initialize(TYPE)override;

	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC _hDC) override;
	virtual void Release(void) override;

public:
	void Set_Plist(list<CObj*>* _Plist) { m_Plist = _Plist; }

private:
	list<CObj*>* m_Plist;
};

