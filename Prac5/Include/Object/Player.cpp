#include "Player.h"

Player::Player()
{
}

Player::Player(const Player & _player)
	:MoveObj(_player)
{
}

Player::~Player()
{
}

bool Player::Init()
{
	SetPos(100.f, 100.f);
	SetSize(100.f, 100.f);
	return true;
}

void Player::Input(const float & _fDeltaTime)
{
	MoveObj::Input(_fDeltaTime);
}

int Player::Update(const float & _fDeltaTime)
{
	MoveObj::Update(_fDeltaTime);
	return 0;
}

int Player::LateUpdate(const float & _fDeltaTime)
{
	MoveObj::LateUpdate(_fDeltaTime);
	return 0;
}

void Player::Collision(const float & _fDeltaTime)
{
	MoveObj::Collision(_fDeltaTime);
}

void Player::Render(HDC _hDC, const float & _fDeltaTime)
{
	MoveObj::Render(_hDC, _fDeltaTime);
	Rectangle(_hDC,
		static_cast<int>(m_tPos.GetX()),
		static_cast<int>(m_tPos.GetY()),
		static_cast<int>(m_tPos.GetX() + m_tSize.GetY()),
		static_cast<int>(m_tPos.GetY() + m_tSize.GetY()));
}
