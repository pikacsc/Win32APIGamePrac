#include "StaticObj.h"

StaticObj::StaticObj()
{
}

StaticObj::StaticObj(const StaticObj & _obj)
	:Obj(_obj)
{
}

StaticObj::~StaticObj()
{
}

void StaticObj::Input(const float & _fDeltaTime)
{
}

int StaticObj::Update(const float & _fDeltaTime)
{
	return 0;
}

int StaticObj::LateUpdate(const float & _fDeltaTime)
{
	return 0;
}

void StaticObj::Collision(const float & _fDeltaTime)
{
}

void StaticObj::Render(HDC _hDC, const float & _fDeltaTime)
{
}
