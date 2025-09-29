#pragma once
#include "../Actor/Actor.h"
#include "../Utility/ShadowDirection.h"
#include "../../kEngine/kEngine.h"
#include "../../kEngine/material/MaterialConfig.h"
#include <memory>
#include <vector>

class ShadowArea;
class Map;
class FallingBlock;

class Player : public Actor {
public:
	void Initialize(kEngine* system, Map* map);
	void Update(std::vector<FallingBlock>& fallingBlocks);
	void Draw() const override;
	~Player();

	ShadowDirection GetShadowDirection() const;
	ShadowArea* GetShadowArea() { return shadowArea_; }
	Rect GetRect() { return rect_; }

private:
	// 移動処理
	void Move();

	// 落ちるブロックとの当たり判定
	void ResolveCollision(FallingBlock& fallingBlock);

	// 角の更新
	void UpdateRect();

private:
	kEngine* system_;

	// ShadowAreaのインスタンスを所有する
	ShadowArea* shadowArea_ = nullptr;
	ShadowDirection isShadowDirection_;

	// Mapのインスタンスを所有する
	Map* map_ = nullptr;

	MaterialConfig materialConfig_;

	// 定数定義
	const float kGravity = 0.8f;        // 重力加速度
	const float kJumpVelocity = -15.0f; // ジャンプの初速 (Y軸は下向きが正なので負の値)
	const float kMaxFallSpeed = 20.0f;  // 最大落下速度
};
