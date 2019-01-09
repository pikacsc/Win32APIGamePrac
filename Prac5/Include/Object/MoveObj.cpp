#include "MoveObj.h"

MoveObj::MoveObj()
{
}

MoveObj::MoveObj(const MoveObj & _obj)
	:Obj(_obj) //parent's copy constructor
{
}

MoveObj::~MoveObj()
{
}

void MoveObj::Input(const float & _fDeltaTime)
{
}

int MoveObj::Update(const float & _fDeltaTime)
{
	return 0;
}

int MoveObj::LateUpdate(const float & _fDeltaTime)
{
	return 0;
}

void MoveObj::Collision(const float & _fDeltaTime)
{
}

void MoveObj::Render(HDC _hDC, const float & _fDeltaTime)
{
}
