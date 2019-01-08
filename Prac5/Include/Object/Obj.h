#pragma once
#include "../Game.h"

class Obj
{
protected:
	Obj();
	virtual ~Obj();

protected:
	int		m_iRef;
public:
	void AddRef()
	{
		++m_iRef;
	}

	int Release()
	{
		--m_iRef;
		if (m_iRef == 0)
		{
			delete this;
			return 0;
		}
		return m_iRef;
	}

protected:
	string	 m_strTag;
	POSITION m_tPos;
	_SIZE	 m_tSize;

public:
	string GetTag() const
	{
		return m_strTag;
	}

	POSITION GetPos() const
	{
		return m_tPos;
	}

	_SIZE	GetSize() const
	{
		return m_tSize;
	}

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	void SetPos(const POSITION& _pos)
	{
		m_tPos = _pos;
	}


	void SetPos(const POINT& _pt)
	{
		m_tPos = _pt;
	}

	void SetPos(const float& _fX, const float& _fY)
	{
		float f[] = { _fX, _fY };
		m_tPos = f;
	}

	void SetSize(const _SIZE& _tSize)
	{
		m_tSize = _tSize;
	}

	void SetSize(const float& _fX, const float& _fY)
	{
		float f[] = { _fX, _fY };
		m_tSize = f;
	}


public:
	virtual bool Init();
	virtual void Input(const float& fDeltaTime);
	virtual int Update(const float& fDeltaTime);
	virtual int LateUpdate(const float& fDeltaTime);
	virtual void Collision(const float& fDeltaTime);
	virtual void Render(HDC hDC,const float& fDeltaTime);

};
