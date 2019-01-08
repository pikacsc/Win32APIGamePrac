#pragma once
#include "../Game.h"

class Scene
{
protected:
	friend class SceneManager;

protected:
	Scene();
	virtual ~Scene() = 0; //abstract class

protected:
	list<class Layer*> m_LayerList;

public:
	class Layer* CreateLayer(const string& strTag, const int &iZorder = 0);
	
	virtual bool Init();
	virtual void Input(const float& fDeltaTime);
	virtual int Update(const float& fDeltaTime);
	virtual int LateUpdate(const float& fDeltaTime);
	virtual void Collision(const float& fDeltaTime);
	virtual void Render(HDC hdc, const float& fDeltaTime);

	static bool LayerSort(class Layer* pL1, class Layer* pL2);

};
