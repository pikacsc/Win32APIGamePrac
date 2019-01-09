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

void SceneManager::Input(const float& _fDeltaTime)
{
	m_pScene->Input(_fDeltaTime);
}

int SceneManager::Update(const float& _fDeltaTime)
{
	m_pScene->Update(_fDeltaTime);
	return 0;
}

int SceneManager::LateUpdate(const float& _fDeltaTime)
{
	m_pScene->LateUpdate(_fDeltaTime);
	return 0;
}

void SceneManager::Collision(const float& _fDeltaTime)
{
	m_pScene->Collision(_fDeltaTime);
}

void SceneManager::Render(HDC _hDC, const float& _fDeltaTime)
{
	m_pScene->Render(_hDC, _fDeltaTime);
}

