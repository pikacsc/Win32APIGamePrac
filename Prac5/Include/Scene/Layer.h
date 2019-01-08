#pragma once
#include "../Game.h"

class Layer
{
private:
	friend class Scene;
	Layer();

public:
	~Layer();

private:
	class Scene*		m_pScene;
	string				m_strTag;
	int					m_iZOrder;
	list<class Obj*>	m_ObjList;

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	string GetTag() const
	{
		return m_strTag;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	int GetZOrder() const
	{
		return m_iZOrder;
	}

	void SetScene(class Scene* pScene)
	{
		m_pScene = pScene;
	}

	Scene* GetScene() const
	{
		return m_pScene;
	}

public:
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
};
