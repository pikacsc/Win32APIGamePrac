#pragma once


typedef struct _tagResolution
{
	unsigned int iW;
	unsigned int iH;
} RESOLUTION, *PRESOLUTION;

class Position
{
private:
	float m_fX;
	float m_fY;
public:
	float GetX() const
	{
		return m_fX;
	}

	float GetY() const
	{
		return m_fY;
	}

	void SetX(const float& _fX) {
		m_fX = _fX;
	}

	void SetY(const float& _fY) {
		m_fY = _fY;
	}

public:
	Position()
		:m_fX(0.f), m_fY(0.f)
	{
	}

	Position(const float& _fX, const float& _fY)
		:m_fX(_fX), m_fY(_fY)
	{
	}


	Position(const Position& _pos)
	{
		m_fX = _pos.m_fX;
		m_fY = _pos.m_fY;
	}

	Position(const POINT& _pt)
	{
		m_fX = static_cast<float>(_pt.x);
		m_fY = static_cast<float>(_pt.y);
	}

	void operator = (const Position& _pos)
	{
		m_fX = _pos.m_fX;
		m_fY = _pos.m_fY;
	}

	void operator = (const POINT& _pt)
	{
		m_fX = static_cast<float>(_pt.x);
		m_fY = static_cast<float>(_pt.y);
	}

	void operator = (float f[2])
	{
		m_fX = f[0];
		m_fY = f[1];
	}

	//operator +
	Position operator + (const Position& _pos) const
	{
		Position	tPos;
		tPos.m_fX += _pos.m_fX;
		tPos.m_fY += _pos.m_fY;
		return tPos;
	}

	Position operator + (const POINT& _pt) const
	{
		Position	tPos;
		tPos.m_fX += static_cast<float>(_pt.x);
		tPos.m_fY += static_cast<float>(_pt.y);
		return tPos;
	}

	Position operator + (float _f[2]) const
	{
		Position	tPos;
		tPos.m_fX += _f[0];
		tPos.m_fY += _f[1];
		return tPos;
	}

	Position operator + (const float& _f) const
	{
		Position	tPos;
		tPos.m_fX += _f;
		tPos.m_fY += _f;
		return tPos;
	}

	void operator += (const Position& _pos)
	{
		m_fX += _pos.GetX();
		m_fY += _pos.GetY();
	}


	//operator -
	Position operator - (const Position& _pos) const
	{
		Position	tPos;
		tPos.m_fX -= _pos.m_fX;
		tPos.m_fY -= _pos.m_fY;
		return tPos;
	}

	Position operator - (const POINT& _pt) const
	{
		Position	tPos;
		tPos.m_fX -= static_cast<float>(_pt.x);
		tPos.m_fY -= static_cast<float>(_pt.y);
		return tPos;
	}

	Position operator - (float _f[2]) const
	{
		Position	tPos;
		tPos.m_fX -= _f[0];
		tPos.m_fY -= _f[1];
		return tPos;
	}

	Position operator - (const float& _f) const
	{
		Position	tPos;
		tPos.m_fX -= _f;
		tPos.m_fY -= _f;
		return tPos;
	}

	//operator *
	Position operator * (const Position& _pos) const
	{
		Position	tPos;
		tPos.m_fX *= _pos.m_fX;
		tPos.m_fY *= _pos.m_fY;
		return tPos;
	}

	Position operator * (const POINT& _pt) const
	{
		Position	tPos;
		tPos.m_fX *= static_cast<float>(_pt.x);
		tPos.m_fY *= static_cast<float>(_pt.y);
		return tPos;
	}

	Position operator * (float _f[2]) const
	{
		Position	tPos;
		tPos.m_fX *= _f[0];
		tPos.m_fY *= _f[1];
		return tPos;
	}

	Position operator * (const float& _f) const
	{
		Position	tPos;
		tPos.m_fX *= _f;
		tPos.m_fY *= _f;
		return tPos;
	}


	//operator /
	Position operator / (const Position& _pos) const
	{
		Position	tPos;
		tPos.m_fX /= _pos.m_fX;
		tPos.m_fY /= _pos.m_fY;
		return tPos;
	}

	Position operator / (const POINT& _pt) const
	{
		Position	tPos;
		tPos.m_fX /= static_cast<float>(_pt.x);
		tPos.m_fY /= static_cast<float>(_pt.y);
		return tPos;
	}

	Position operator / (float _f[2]) const
	{
		Position	tPos;
		tPos.m_fX /= _f[0];
		tPos.m_fY /= _f[1];
		return tPos;
	}

	Position operator / (const float& _f) const
	{
		Position	tPos;
		tPos.m_fX /= _f;
		tPos.m_fY /= _f;
		return tPos;
	}

};
typedef Position POSITION, *PPOSITION, _SIZE, *_PSIZE;
