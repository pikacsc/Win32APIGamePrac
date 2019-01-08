#include "InGameScene.h"



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
	return true;
}
