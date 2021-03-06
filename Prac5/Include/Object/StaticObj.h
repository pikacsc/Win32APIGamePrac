#pragma once
#include "Obj.h"

class StaticObj : public Obj
{
protected:
	StaticObj();
	StaticObj(const StaticObj& _obj);
	virtual ~StaticObj();

public:
	virtual bool Init() = 0;
	virtual void Input(const float &_fDeltaTime);
	virtual int Update(const float &_fDeltaTime);
	virtual int LateUpdate(const float &_fDeltaTime);
	virtual void Collision(const float &_fDeltaTime);
	virtual void Render(HDC _hDC, const float &_fDeltaTime);
};