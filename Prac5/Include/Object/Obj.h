#pragma once
#include "../Scene/Layer.h"
#include "../Ref.h"

class Obj : public Ref
{
protected:
	Obj();
	Obj(const Obj& _obj);
	virtual ~Obj();

protected:
	class Scene* m_pScene;
	class Layer* m_pLayer;

public:
	void SetScene(class Scene* _pScene)
	{
		m_pScene = _pScene;
	}

	void SetLayer(class Layer* _pLayer)
	{
		m_pLayer = _pLayer;
	}

	class Scene* GetScene() const
	{
		return m_pScene;
	}

	class Layer* GetLayer() const
	{
		return m_pLayer;
	}

protected:
	eOBJ_CREATE	 m_eObjTag;
	POSITION	 m_tPos;
	_SIZE		 m_tSize;
	POSITION	 m_tPivot;

public:
	eOBJ_CREATE GetObjTag() const
	{
		return m_eObjTag;
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
	void SetObjTag(eOBJ_CREATE _eObjTag)
	{
		m_eObjTag = _eObjTag;
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
	virtual bool Init() = 0;
	virtual void Input(const float& _fDeltaTime);
	virtual int Update(const float& _fDeltaTime);
	virtual int LateUpdate(const float& _fDeltaTime);
	virtual void Collision(const float& _fDeltaTime);
	virtual void Render(HDC hDC,const float& _fDeltaTime);

public:
	template <typename T>
	static T* CreateObj(eOBJ_CREATE _eObj, class Layer* _pLayer = NULL)
	{
		T* pObj = new T;

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return NULL;
		}

		if (_pLayer)
		{
			_pLayer->AddObject(pObj);
		}

		return pObj;
	}

};
