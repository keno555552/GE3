#pragma once
#include "../../kEngine/kEngine.h"
#include "../../kEngine/material/MaterialConfig.h"
#include "../Actor/Actor.h"
#include "../Map/Map.h"
#include "../Utility/Vector2Int.h"
#include <memory>

class Player;

class FallingBlock : public Actor {
public:
	void Initialize(kEngine* system);

	void Update(Map* map);

	void Draw() const override;

	// Getter
	Vector2 GetPos() { return position_; }
	Vector2 GetRadius() { return radius_; }
	bool IsAlive() { return isAlive_; }
	Rect GetRect() { return rect_; }

	// Setter
	void SetPos(Vector2 pos) { position_ = pos; }

private:
	bool IsSolidTile(Vector2Int tilePos);

	void UpdateFallingBlock();

	void UpdateRect();

private:
	Map* map_;

	MaterialConfig materialConfig_;

	kEngine* system_;
};
