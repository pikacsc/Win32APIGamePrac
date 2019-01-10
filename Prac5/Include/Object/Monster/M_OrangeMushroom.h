#pragma once
#include "../MoveObj.h"
#include "../../Core.h"

class M_OrangeMushroom : public MoveObj
{
private:
	friend class Obj;

private:
	M_OrangeMushroom();
	M_OrangeMushroom(const M_OrangeMushroom& _M_OrangeMushroom);
	~M_OrangeMushroom();

private:
	MOVE_DIR	m_eDir;

public:
	virtual bool Init();
	virtual int Update(const float& _fDeltaTime);
	virtual int LateUpdate(const float& _fDeltaTime);
	virtual void Collision(const float& _fDeltaTime);
	virtual void Render(HDC _hDC, const float& _fDeltaTime);
};