#pragma once
#include "Game.h"

class Ref
{
protected:
	Ref();
	virtual ~Ref() = 0;

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
};