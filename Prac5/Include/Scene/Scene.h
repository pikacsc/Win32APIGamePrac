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
	class Layer* CreateLayer(eLAYER_CREATE _eLayTag, const int & _iZorder = 0);

	class Layer* FindLayer(eLAYER_CREATE _eLayTag);
	
	virtual bool Init();
	virtual void Input(const float& _fDeltaTime);
	virtual int Update(const float& _fDeltaTime);
	virtual int LateUpdate(const float& _fDeltaTime);
	virtual void Collision(const float& _fDeltaTime);
	virtual void Render(HDC _hdc, const float& _fDeltaTime);

	static bool LayerSort(class Layer* _pL1, class Layer* _pL2);

};
