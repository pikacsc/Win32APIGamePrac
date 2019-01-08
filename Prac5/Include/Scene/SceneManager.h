#pragma once
#include "../Game.h"

class SceneManager
{
private:
	class Scene* m_pScene;
	class Scene* m_pNextScene;

public:
	bool	Init();
	void	Input(const float& fDeltaTime);
	int		Update(const float& fDeltaTime);
	int		LateUpdate(const float& fDeltaTime);
	void	Collision(const float& fDeltaTime);
	void	Render(HDC hDC, const float& fDeltaTime);

public:
	template<typename T>
	T* CreateScene(eSCENE_CREATE eSC)
	{
		T* pScene = new T;

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}

		switch (eSC)
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
