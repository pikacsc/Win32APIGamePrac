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
	eLAYER_CREATE		m_eLayerTag;
	int					m_iZOrder;
	list<class Obj*>	m_ObjList;

public:
	void SetLayerTag(eLAYER_CREATE _eLay)
	{
		m_eLayerTag = _eLay;
	}

	eLAYER_CREATE GetLayerTag() const
	{
		return m_eLayerTag;
	}

	void SetZOrder(int _iZOrder)
	{
		m_iZOrder = _iZOrder;
	}

	int GetZOrder() const
	{
		return m_iZOrder;
	}

	void SetScene(class Scene* _pScene)
	{
		m_pScene = _pScene;
	}

	Scene* GetScene() const
	{
		return m_pScene;
	}

public:
	void AddObject(class Obj* _pObj);

public:
	void Input(const float& _fDeltaTime);
	int Update(const float& _fDeltaTime);
	int LateUpdate(const float& _fDeltaTime);
	void Collision(const float& _fDeltaTime);
	void Render(HDC _hDC,const float& _fDeltaTime);
};
