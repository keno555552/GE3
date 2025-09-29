#pragma once
#include "./New/FallingBlock/FallingBlock.h"
#include "./New/Map/Map.h"
#include "./New/Player/Player.h"
#include "./New/ShadowArea/ShadowArea.h"
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

	// プレイヤー
	std::unique_ptr<Player> player_;

	// マップ
	std::unique_ptr<Map> map_;

	// 影
	std::unique_ptr<ShadowArea> shadowArea_;

	// 落ちるブロック
	std::unique_ptr<std::vector<FallingBlock>> fallingBlocks_;

	// textureHandle
	int whiteHandle_ = 0;

	// 落ちるブロックをすべて初期化できたかどうか
	bool isFallingBlockSet_ = false;
};
