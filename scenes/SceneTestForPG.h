#pragma once
#include "./kEngine.h"
#include "../StageManager/Scene.h"
#include <memory>
#include <vector>

class SceneTestForPG: public Scene
{
public:
	SceneTestForPG(kEngine* system);
	~SceneTestForPG();

	void Update() override;
	void Draw() override;

private:
	kEngine* system_;



};
