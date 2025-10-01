#pragma once
#include "./kEngine.h"
#include "../StageManager/Scene.h"
#include <memory>
#include <vector>

class Stage : public Scene {
public:
	Stage(kEngine* system);
	~Stage();

	void Update() override;
	void Draw() override;

private:
	kEngine* system_;
};
