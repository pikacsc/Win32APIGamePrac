#pragma once
#include "Scene.h"

class InGameScene : public Scene
{
private: 
	friend class SceneManager;
public:
	InGameScene();
	~InGameScene();

public:
	virtual bool Init();
};
