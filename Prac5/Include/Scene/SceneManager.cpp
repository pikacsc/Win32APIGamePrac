#include "SceneManager.h"
#include "InGameScene.h"


DEFINITION_SINGLE(SceneManager)

SceneManager::SceneManager()
	:m_pScene(NULL),
	m_pNextScene(NULL)
{
}


SceneManager::~SceneManager()
{
	SAFE_DELETE(m_pScene);
}

bool SceneManager::Init()
{
	CreateScene<InGameScene>(eSC_CURRENT);
	return true;
}

void SceneManager::Input(const float& fDeltaTime)
{
	m_pScene->Input(fDeltaTime);
}

int SceneManager::Update(const float& fDeltaTime)
{
	m_pScene->Update(fDeltaTime);
	return 0;
}

int SceneManager::LateUpdate(const float& fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);
	return 0;
}

void SceneManager::Collision(const float& fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);
}

void SceneManager::Render(HDC hDC, const float& fDeltaTime)
{
	m_pScene->Render(hDC, fDeltaTime);
}

