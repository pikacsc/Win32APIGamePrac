#pragma once
#include "../Game.h"

class SceneManager
{
private:
	class Scene* m_pScene;
	class Scene* m_pNextScene;

public:
	bool	Init();
	void	Input(const float& _fDeltaTime);
	int		Update(const float& _fDeltaTime);
	int		LateUpdate(const float& _fDeltaTime);
	void	Collision(const float& _fDeltaTime);
	void	Render(HDC _hDC, const float& _fDeltaTime);

public:
	template<typename T>
	T* CreateScene(eSCENE_CREATE _eSC)
	{
		T* pScene = new T;

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}

		switch (_eSC)
		{
		case eSC_CURRENT:
			SAFE_DELETE(m_pScene);
			m_pScene = pScene;
			break;
		case eSC_NEXT:
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = pScene;
			break;
		}

		return pScene;
	}

	DECLARE_SINGLE(SceneManager);
};
