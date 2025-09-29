#include "Stage.h"

Stage::Stage(kEngine* system) {
	system_ = system;

	// マップ
	map_ = std::make_unique<Map>();
	map_->Initialize("resources/map/map.csv", "resources/white5x5.png", system_);

	// プレイヤー
	player_ = std::make_unique<Player>();
	player_->Initialize(system_, map_.get());

	// 影
	shadowArea_ = std::make_unique<ShadowArea>();
	shadowArea_->Initialize(system_);

	// 落ちるブロック
	fallingBlocks_ = std::make_unique<std::vector<FallingBlock>>();

	// textureHandle
	whiteHandle_ = system_->LoadTextrue("resources/white5x5.png");

	isFallingBlockSet_ = false;
}

Stage::~Stage() {

}

void Stage::Update() {
	player_->Update(*fallingBlocks_);

	// 影の更新処理
	shadowArea_->Update(player_->GetShadowDirection());

	// マップの更新
	map_->Update();

	// 落下ブロックの生成
	if (!isFallingBlockSet_) {
		for (int row = 0; row < map_->GetRows(); ++row) {
			for (int col = 0; col < map_->GetCols(); ++col) {
				int tileType = map_->GetTileType(row, col);

				// 落下ブロックのマップチップ番号を判別
				if (tileType == 2) {
					FallingBlock block;
					float tileSize = static_cast<float>(map_->GetTileSize());
					Vector2 position = {col * tileSize + tileSize / 2.0f, row * tileSize + tileSize / 2.0f};
					block.SetPos(position);
					block.Initialize(system_);

					// 追加
					fallingBlocks_->push_back(block);
				}
			}
		}

		isFallingBlockSet_ = true;
	}

	// 落ちるブロックの更新処理
	for (auto& block : *fallingBlocks_) {
		block.Update(map_.get());
	}
}

void Stage::Draw() {
	shadowArea_->Draw();
	map_->Draw();
	player_->Draw();

	// 落ちるブロックの描画処理
	for (auto& block : *fallingBlocks_) {
		block.Draw();
	}
}
