#include "InGameScene.h"
#include "../Object/Player.h"
#include "Layer.h"


InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

bool InGameScene::Init()
{
	//call bass class Scene's Init()
	if (!Scene::Init())
		return false;

	Layer* pLayer = FindLayer(eLAY_DEFAULT);

	Player* pPlayer = Obj::CreateObj<Player>(eOBJ_PLAYER, pLayer);

	SAFE_RELEASE(pPlayer);

	return true;
}
