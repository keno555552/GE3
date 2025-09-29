#pragma once
#include "Scene.h"
#include "MathsIncluder.h"
#include "config.h"

class StageTestForGE :public Scene
{
public:
	StageTestForGE(kEngine* system);
	~StageTestForGE();
	void Update() override;
	void Draw() override;

private:
	kEngine* system_ = nullptr;


};

