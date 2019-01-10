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
	SetPos(constants::Player_DefaultPosX, constants::Player_DefaultPosY);
	SetSize(constants::Player_DefaultSizeWidth, constants::Player_DefaultSizeHeight);
	SetSpeed(constants::Player_DefaultSpeed);
	return true;
}

void Player::Input(const float & _fDeltaTime)
{
	MoveObj::Input(_fDeltaTime);
	if (KEY_INPUT(VK_UP))
	{
		MoveYFromSpeed(_fDeltaTime, MD_BACK);
	}
	if (KEY_INPUT(VK_DOWN))
	{
		MoveYFromSpeed(_fDeltaTime, MD_FRONT);
	}
	if (KEY_INPUT(VK_LEFT))
	{
		MoveXFromSpeed(_fDeltaTime, MD_BACK);
	}
	if (KEY_INPUT(VK_RIGHT))
	{
		MoveXFromSpeed(_fDeltaTime, MD_FRONT);
	}

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
