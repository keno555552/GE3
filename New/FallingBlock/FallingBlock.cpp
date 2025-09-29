#include "FallingBlock.h"
#include "../../kEngine/drawEngine/drawEngine.h"
#include "../../kEngine/tool/mathsUnit/Matrix3x3.h"

void FallingBlock::Initialize(kEngine* system) {
	speed_ = {4.0f, 4.0f};
	radius_ = {32.0f, 32.0f};
	isAlive_ = true;
	velocity_ = {0.0f, 0.0f};
	acceleration_ = {0.0f, 0.98f};
	isOnGround_ = false;
	
	rect_ = {
	    position_.x - radius_.x,
	    position_.x + radius_.x,
	    position_.y - radius_.y,
	    position_.y + radius_.y,
	};

	system_ = system;

	intMaterialConfig(&materialConfig_);
	materialConfig_.uvTransformMatrix = MakeAffineMatrix(materialConfig_.uvScale, materialConfig_.uvRotate, materialConfig_.uvTranslate);
	materialConfig_.textureHandle = system_->LoadTextrue("resources/white5x5.png");
}

void FallingBlock::Update(Map* map) { 
	map_ = map;

	UpdateRect(); // 角の更新
	UpdateFallingBlock(); // 箱の落ちる処理 
}

void FallingBlock::Draw()const {
	float left = (position_.x - radius_.x);
	float right = (position_.x + radius_.x);
	float bottom = (position_.y + radius_.y);
	float top = (position_.y - radius_.y);

	system_->DrawSprite(position_, materialConfig_, {left, top}, {left, bottom}, {right, top}, {right, bottom}, radius_.x * 2, radius_.y * 2, {0, 0}, {1, 1});
	//DrawEngine::DrawSprite(position_, )
	//Shape::DrawQuad(left, top, right, top, left, bottom, right, bottom, 0, 0, 1, 1, 0, RED);
}

bool FallingBlock::IsSolidTile(Vector2Int tilePos) {
	int tileType = static_cast<int>(map_->GetTileType(tilePos.y, tilePos.x));
	return tileType;
}

void FallingBlock::UpdateFallingBlock() {
	if (!isAlive_)
		return;

	// 通常の重力処理
	if (!isOnGround_) {
		velocity_.y += acceleration_.y;
		position_ = position_ + velocity_;
	}

	// 地面との衝突判定
	float left = position_.x - radius_.x;
	float right = position_.x + radius_.x;
	float bottom = position_.y + radius_.y;

	int leftCol = static_cast<int>(left / map_->GetTileSize());
	int rightCol = static_cast<int>((right) / map_->GetTileSize());
	int bottomRow = static_cast<int>((bottom) / map_->GetTileSize());

	if (velocity_.y > 0) {
		if (map_->GetTileType(bottomRow, leftCol) == 1 || map_->GetTileType(bottomRow, rightCol) == 1) {
			position_.y = float(bottomRow * map_->GetTileSize()) - radius_.y;
			velocity_.y = 0;
			isOnGround_ = true;
		}
	} else {
		if (!(map_->GetTileType(bottomRow, leftCol) == 1 || map_->GetTileType(bottomRow, rightCol) == 1)) {
			isOnGround_ = false;
		}
	}
}


void FallingBlock::UpdateRect()
{
	rect_ = {
	    position_.x - radius_.x,
	    position_.x + radius_.x,
	    position_.y - radius_.y,
	    position_.y + radius_.y,
	};
}
