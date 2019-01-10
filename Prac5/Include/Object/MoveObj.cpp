#include "MoveObj.h"

MoveObj::MoveObj()
	:m_fAngle(constants::MoveObj_DefaultAngle),
	m_fSpeed(constants::MoveObj_DefaultSpeed)
{
}

MoveObj::MoveObj(const MoveObj & _obj)
	:Obj(_obj) //parent's copy constructor
{
	m_fAngle = _obj.m_fAngle;
}

MoveObj::~MoveObj()
{
}

void MoveObj::SetAngle(const float & _fAngle)
{
	m_fAngle = _fAngle;
}

void MoveObj::SetSpeed(const float & _fSpeed)
{
	m_fSpeed = _fSpeed;
}

float MoveObj::GetAngle() const
{
	return m_fAngle;
}

float MoveObj::GetSpeed() const
{
	return m_fSpeed;
}

void MoveObj::Move(const float & _fX, const float & _fY)
{
	float f[] = { _fX,_fY };
	m_tPos + f;
}

void MoveObj::Move(const float & _fX, const float & _fY, const float & _fDeltaTime)
{
	float f[] = { (_fX * _fDeltaTime) ,(_fY * _fDeltaTime) };
	m_tPos + f;
}

void MoveObj::Move(const POSITION & _tMove)
{
	m_tPos += _tMove;
}

void MoveObj::Move(const POSITION & _tMove, const float & _fDeltaTime)
{
	m_tPos += _tMove * _fDeltaTime;
}

void MoveObj::MoveX(const float & _fX)
{
	float newX = m_tPos.GetX() + _fX;
	m_tPos.SetX(newX);
}

void MoveObj::MoveX(const float & _fX, const float & _fDeltaTime)
{
	float newX = (m_tPos.GetX() + _fX) * _fDeltaTime;
	m_tPos.SetX(newX);
}

void MoveObj::MoveXFromSpeed(const float & _fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.SetX(m_tPos.GetX() + (m_fSpeed * _fDeltaTime * eDir));
}


void MoveObj::MoveY(const float & _fY)
{
	float newY = m_tPos.GetY() + _fY;
	m_tPos.SetY(newY);
}

void MoveObj::MoveY(const float & _fY, const float & _fDeltaTime)
{
	float newY = (m_tPos.GetY() + _fY) * _fDeltaTime;
	m_tPos.SetY(newY);
}

void MoveObj::MoveYFromSpeed(const float & _fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.SetY(m_tPos.GetY() + (m_fSpeed * _fDeltaTime * eDir));
}


void MoveObj::MoveAngle(const float & _fSpeed)
{
	float newX = m_tPos.GetX() + (cosf(m_fAngle) * _fSpeed);
	float newY = m_tPos.GetY() + (sinf(m_fAngle) * _fSpeed);
	m_tPos.SetX(newX);
	m_tPos.SetY(newY);
}

void MoveObj::MoveAngle(const float & _fSpeed, const float & _fDeltaTime)
{
	float newX = m_tPos.GetX() + (cosf(m_fAngle) * _fSpeed * _fDeltaTime);
	float newY = m_tPos.GetY() + (sinf(m_fAngle) * _fSpeed * _fDeltaTime);
	m_tPos.SetX(newX);
	m_tPos.SetY(newY);
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
