#pragma once
#include "Vector2.h"
#include "MaterialConfig.h"

class SpriteData
{
public:
	Vector2 pos;
	MaterialConfig material;
	Vector2 LTpos;
	Vector2 LBpos;
	Vector2 RTpos;
	Vector2 RBpos;
	float TsizeX; 
	float TsizeY;
	Vector2 TCLTPos; 
	Vector2 TCRBPos;

public:
	void dataUpdate(SpriteData* machData);
};

