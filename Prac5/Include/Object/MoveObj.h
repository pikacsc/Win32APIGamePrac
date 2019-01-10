#pragma once
#include "Obj.h"

class MoveObj : public Obj
{
protected:
	MoveObj();
	MoveObj(const MoveObj& _obj);
	virtual ~MoveObj();

private:
	float	m_fAngle;
	float	m_fSpeed;

public:
	void SetAngle(const float& _fAngle);
	void SetSpeed(const float& _fSpeed);
	float GetAngle() const;
	float GetSpeed() const;

	void Move(const float& _fX, const float& _fY);
	void Move(const float& _fX, const float& _fY, const float& _fDeltaTime);
	void Move(const POSITION& _tMove);
	void Move(const POSITION& _tMove, const float& _fDeltaTime);
	void MoveX(const float& _fX);
	void MoveX(const float& _fX, const float& _fDeltaTime);
	void MoveXFromSpeed(const float& _fDeltaTime, MOVE_DIR eDir);
	void MoveY(const float& _fY);
	void MoveY(const float& _fY, const float& _fDeltaTime);
	void MoveYFromSpeed(const float& _fDeltaTime, MOVE_DIR eDir);
	void MoveAngle(const float& _fSpeed);
	void MoveAngle(const float& _fSpeed, const float& _fDeltaTime);


public:
	virtual bool Init() = 0;
	virtual void Input(const float & _fDeltaTime);
	virtual int Update(const float & _fDeltaTime);
	virtual int LateUpdate(const float & _fDeltaTime);
	virtual void Collision(const float & _fDeltaTime);
	virtual void Render(HDC _hDC,const float & _fDeltaTime);
};