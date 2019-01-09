#include "Scene.h"
#include "Layer.h"


Scene::Scene()
{
	Layer* pLayer = CreateLayer(eLAY_DEFAULT);
	pLayer = CreateLayer(eLAY_UI, INT_MAX);
}


Scene::~Scene()
{
	Safe_Delete_VecList(m_LayerList);
}

Layer * Scene::CreateLayer(eLAYER_CREATE _eLayTag, const int & _iZorder)
{
	Layer* pLayer = new Layer;

	pLayer->SetLayerTag(_eLayTag);
	pLayer->SetZOrder(_iZorder);
	pLayer->SetScene(this);

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 2)
		m_LayerList.sort(Scene::LayerSort);
	return pLayer;
}

Layer * Scene::FindLayer(eLAYER_CREATE _eLayTag)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetLayerTag() == _eLayTag)
			return *iter;
	}
	return NULL;
}

bool Scene::Init()
{
	return true;
}

void Scene::Input(const float & _fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Input(_fDeltaTime);
	}
}

int Scene::Update(const float & _fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update(_fDeltaTime);
	}
	return 0;
}	

int Scene::LateUpdate(const float & _fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->LateUpdate(_fDeltaTime);
	}
	return 0;
}

void Scene::Collision(const float & _fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Collision(_fDeltaTime);
	}
}

void Scene::Render(HDC _hDC, const float & _fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(_hDC, _fDeltaTime);
	}
}

bool Scene::LayerSort(Layer * _pL1, Layer * _pL2)
{
	return _pL1->GetZOrder() < _pL2->GetZOrder();
}
