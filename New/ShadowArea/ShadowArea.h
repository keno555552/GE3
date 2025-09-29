#pragma once
#include "../Utility/ShadowDirection.h"
#include "../../kEngine/kEngine.h"
#include "../../kEngine/material/MaterialConfig.h"

class Map;

class ShadowArea {
public:
	void Initialize(kEngine* system);
	void Update(ShadowDirection direction);
	void Draw();
	~ShadowArea();

	// 位置、幅、高さを外部から取得するためのゲッターを追加
	Vector2 GetPosition() const { return position_; }
	float GetWidth() const { return width_; }
	float GetHeight() const { return height_; }
private:
	Vector2 position_;
	float width_;
	float height_;
	Map *map_ = nullptr;
	kEngine* system_;
	MaterialConfig materialConfig_;
};

