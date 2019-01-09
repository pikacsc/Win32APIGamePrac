#include "Layer.h"
#include "../Object/Obj.h"

Layer::Layer()
	:m_iZOrder(0),
	m_eLayerTag(eLAY_DEFAULT),
	m_pScene(NULL)
{
}


Layer::~Layer()
{
	Safe_Release_VecList(m_ObjList);
}

void Layer::AddObject(Obj * _pObj)
{
	_pObj->SetScene(m_pScene);
	_pObj->SetLayer(this);
	_pObj->AddRef();

	m_ObjList.push_back(_pObj);
}

void Layer::Input(const float & _fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Input(_fDeltaTime);
	}
}

int Layer::Update(const float & _fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update(_fDeltaTime);
	}
	return 0;
}

int Layer::LateUpdate(const float & _fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->LateUpdate(_fDeltaTime);
	}
	return 0;
}

void Layer::Collision(const float & _fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Collision(_fDeltaTime);
	}
}

void Layer::Render(HDC _hDC,const float & _fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(_hDC, _fDeltaTime);
	}
}
