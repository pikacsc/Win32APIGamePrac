#include "Obj.h"

Obj::Obj()
{
}

Obj::Obj(const Obj & _obj)
{
	*this = _obj;
}


Obj::~Obj()
{
}


void Obj::Input(const float& _fDeltaTime)
{
}

int Obj::Update(const float& _fDeltaTime)
{
	return 0;
}

int Obj::LateUpdate(const float& _fDeltaTime)
{
	return 0;
}

void Obj::Collision(const float& _fDeltaTime)
{
}

void Obj::Render(HDC _hDC, const float& _fDeltaTime)
{
}
