#include "Obj.h"



Obj::Obj()
	:m_iRef(1)
{
}


Obj::~Obj()
{
}

bool Obj::Init()
{
	return true;
}

void Obj::Input(const float& fDeltaTime)
{
}

int Obj::Update(const float& fDeltaTime)
{
	return 0;
}

int Obj::LateUpdate(const float& fDeltaTime)
{
	return 0;
}

void Obj::Collision(const float& fDeltaTime)
{
}

void Obj::Render(HDC hDC, const float& fDeltaTime)
{
}
