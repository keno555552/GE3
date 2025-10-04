#pragma once
#include "Scene.h"
#include "SceneTester.h"
#include "StageTestForGE.h"
#include "SceneTestForPG.h"
#include "MaterialConfig.h"
#include "Stage.h"

class SceneManager
{
public:
	SceneManager(kEngine* system);
	~SceneManager();

	void Update();
	void Render();

public:
	enum class SceneNum {
		NONE = -2,
		TESTER = -1,
		TITLE,
		STAGE,
		WIN,
		GAMEOVER,
	};
	SceneNum sceneUsingHandle_ = SceneNum::NONE;
	void SceneChanger();

private:
	Scene* sceneUsing_ = nullptr;
	Scene* sceneOld_ = nullptr;
	MaterialConfig materialConfig_;
	int nullptrSceneHandle_ = 0;

private:
	kEngine* system_ = nullptr;//借り

	//Vector2 LT = {0,0};
	//Vector2 LB = {0,64 };
	//Vector2 RT = {64,0};
	//Vector2 RB = {64,64};
};

