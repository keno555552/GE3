#pragma once
#include "kEngine.h"

class Scene
{
public:
	virtual void Update();
	virtual void Draw();

protected:
	kEngine* system_ = nullptr;

};

