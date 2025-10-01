#pragma once
#include <vector>
#include "MathsIncluder.h"

class InstanceManager
{
public:
	void AddSpriteInstance();
	void ResmoveSpriteInstance();
	void UpdateTileInstance();
	void AddModelInstance();
	void ResmoveModelInstance();
	void UpdateModelInstance();

public:
	struct SpriteInstance {
		Vector2 position;
		Vector2 scale;
		int tileType;
		Vector4 uvOffset;
		int layer;
	};

	struct ModelInstance {
		Vector2 postion;
		Vector2 rotation;
		Vector2 scale;
		int modelID;
		int layer;
	};


private:
	std::vector<SpriteInstance> spriteList;
	std::vector<ModelInstance> modelList;


};

