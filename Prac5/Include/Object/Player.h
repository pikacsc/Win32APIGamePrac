#pragma once
#include "MoveObj.h"
class Player : public MoveObj
{
private:
	friend class Obj;

private:
	Player();
	Player(const Player& _player);
	~Player();

public:
	virtual bool Init();
	virtual void Input(const float& _fDeltaTime);
	virtual int Update(const float& _fDeltaTime);
	virtual int LateUpdate(const float& _fDeltaTime);
	virtual void Collision(const float& _fDeltaTime);
	virtual void Render(HDC _hDC, const float& _fDeltaTime);
};