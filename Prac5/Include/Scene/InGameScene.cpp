#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Monster/M_OrangeMushroom.h"
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

	M_OrangeMushroom* pM_OrangeMushroom = Obj::CreateObj<M_OrangeMushroom>(eOBJ_MONSTER, pLayer);

	SAFE_RELEASE(pM_OrangeMushroom);

	return true;
}
