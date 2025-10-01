#pragma once
#include "Scene.h"

class StageAL3_02: public Scene
{
public:
	StageAL3_02(kEngine* system);
	~StageAL3_02();

	void Update() override;
	void Draw() override;

private:
	kEngine* system_;

};

