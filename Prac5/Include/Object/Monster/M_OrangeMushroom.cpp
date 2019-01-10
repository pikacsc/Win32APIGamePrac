#include "M_OrangeMushroom.h"

M_OrangeMushroom::M_OrangeMushroom()
{
}

M_OrangeMushroom::M_OrangeMushroom(const M_OrangeMushroom & _M_OrangeMushroom)
	:MoveObj(_M_OrangeMushroom)
{
}

M_OrangeMushroom::~M_OrangeMushroom()
{
}

bool M_OrangeMushroom::Init()
{
	using namespace constants;
	SetPos(M_OrangeMushroom_DefaultPosX, M_OrangeMushroom_DefaultPosY);
	SetSize(M_OrangeMushroom_DefaultSizeWidth, M_OrangeMushroom_DefaultSizeHeight);
	SetSpeed(M_OrangeMushroom_DefaultSpeed);

	m_eDir = MD_FRONT;
	return true;
}

int M_OrangeMushroom::Update(const float & _fDeltaTime)
{
	MoveObj::Update(_fDeltaTime);

	MoveYFromSpeed(_fDeltaTime, m_eDir);

	//Moving Up and Down
	if (m_tPos.GetY() + m_tSize.GetY() >= GETRESOLUTION.iH)
	{
		m_tPos.SetY(GETRESOLUTION.iH - m_tSize.GetY());
		m_eDir = MD_BACK;
	}
	else if (m_tPos.GetY() <= 0.f)
	{
		m_tPos.SetY(0.f);
		m_eDir = MD_FRONT;
	}


	return 0;
}

int M_OrangeMushroom::LateUpdate(const float & _fDeltaTime)
{
	MoveObj::LateUpdate(_fDeltaTime);
	return 0;
}

void M_OrangeMushroom::Collision(const float & _fDeltaTime)
{
	MoveObj::Collision(_fDeltaTime);
}

void M_OrangeMushroom::Render(HDC _hDC, const float & _fDeltaTime)
{
	MoveObj::Render(_hDC, _fDeltaTime);
	Rectangle(_hDC,
		static_cast<int>(m_tPos.GetX()),
		static_cast<int>(m_tPos.GetY()),
		static_cast<int>(m_tPos.GetX() + m_tSize.GetX()),
		static_cast<int>(m_tPos.GetY() + m_tSize.GetY()));
}
