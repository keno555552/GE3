#define NOMINMAX
#include "Player.h"
#include "Math.h"
#include "../ShadowArea/ShadowArea.h"
#include "../Map/Map.h"
#include "../Collision/Collision.h"
#include "../FallingBlock/FallingBlock.h"
#include <algorithm>
#include <numbers>
#include <dinput.h>
#include "../../kEngine/tool/mathsUnit/Matrix3x3.h"

void Player::Initialize(kEngine* system, Map* map) {
	position_ = { 0.0f, 0.0f };
	speed_ = { 4.0f, 4.0f };
	radius_ = { 20.0f, 20.0f };
	health_ = 2;
	isAlive_ = true;
	velocity_ = { 0.0f, 0.0f };
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

	// ShadowAreaを生成し、初期化する
	shadowArea_ = new ShadowArea();
	shadowArea_->Initialize(system_);
	isShadowDirection_ = ShadowDirection::Down;

	// 受け取ったmapのポインタをメンバ変数に保存
	map_ = map;
}

void Player::Update(std::vector<FallingBlock>& fallingBlocks) {

	// 落ちるブロックとの当たり判定
	for (auto& block : fallingBlocks) {
		ResolveCollision(block);
	}

	// 移動処理
	Move();

	// 影の方向を決める
	bool upInput = system_->GetTriggerOn(DIK_UP);
	bool downInput = system_->GetTriggerOn(DIK_DOWN);
	bool leftInput = system_->GetTriggerOn(DIK_LEFT);
	bool rightInput = system_->GetTriggerOn(DIK_RIGHT);

	if(upInput) {
		isShadowDirection_ = ShadowDirection::Up;
	} else if(downInput) {
		isShadowDirection_ = ShadowDirection::Down;
	} else if(leftInput) {
		isShadowDirection_ = ShadowDirection::Left;
	} else if(rightInput) {
		isShadowDirection_ = ShadowDirection::Right;
	}

	// 1. ShadowAreaの状態を更新
	shadowArea_->Update(isShadowDirection_);

	// 2. Mapの状態を更新
	map_->ApplyShadowEffect(*shadowArea_);
}

void Player::Draw() const {

	float left = (position_.x - radius_.x);
	float right = (position_.x + radius_.x);
	float bottom = (position_.y + radius_.y);
	float top = (position_.y - radius_.y);

	system_->DrawSprite(position_, materialConfig_, {left, top}, {left, bottom}, {right, top}, {right, bottom}, radius_.x * 2, radius_.y * 2, {0, 0}, {1, 1});

	//Shape::DrawQuad(left, top, right, top, left, bottom, right, bottom, 0, 0, 1, 1, 0, WHITE);
	// 当たり判定可視化
	//Shape::DrawBox(left, top, radius_.x * 2.0f, radius_.y * 2.0f, 0.0f, BLACK, kFillModeWireFrame);
}

void Player::Move() {
	// A. 毎フレーム重力を適用
	velocity_.y += kGravity;
	// 最大落下速度を超えないように制限
	if(velocity_.y > kMaxFallSpeed) {
		velocity_.y = kMaxFallSpeed;
	}

	// B. 左右移動の処理
	// 左右の入力で横方向の速度を決める
	if(system_->GetIsPush(DIK_D) || system_->GetGamepadLStick01X()) {
		velocity_.x = speed_.x;
	} else if (system_->GetIsPush(DIK_A) || !system_->GetGamepadLStick01X()) {
		velocity_.x = -speed_.x;
	} else {
		velocity_.x = 0; // 入力がなければ横移動は止まる
	}

	// C. ジャンプ処理
	// 地面にいるときだけジャンプできる
	if (isOnGround_ && ((system_->GetTriggerOff(DIK_W)) || system_->GetGamepadTriggerOn(3))) {
		velocity_.y = kJumpVelocity;
		isOnGround_ = false; // ジャンプしたら地面から離れる
	}

	// D. X軸（横）の当たり判定と座標補正
	position_.x += velocity_.x;

	float left = position_.x - radius_.x;
	float right = position_.x + radius_.x;
	float top = position_.y - radius_.y;
	float bottom = position_.y + radius_.y;

	int leftCol = static_cast<int>(left / map_->GetTileSize());
	int rightCol = static_cast<int>((right - 0.01f) / map_->GetTileSize());
	int topRow = static_cast<int>(top / map_->GetTileSize());
	int bottomRow = static_cast<int>((bottom - 0.01f) / map_->GetTileSize());

	if(velocity_.x > 0) {
		if(map_->GetTileType(topRow, rightCol) == 1 || map_->GetTileType(bottomRow, rightCol) == 1) {
			position_.x = float(rightCol * map_->GetTileSize()) - radius_.x;
			velocity_.x = 0; // 壁にぶつかったら横方向の速度を0に
		}
	} else if(velocity_.x < 0) {
		if(map_->GetTileType(topRow, leftCol) == 1 || map_->GetTileType(bottomRow, leftCol) == 1) {
			position_.x = float((leftCol + 1) * map_->GetTileSize()) + radius_.x;
			velocity_.x = 0; // 壁にぶつかったら横方向の速度を0に
		}
	}

	// E. Y軸（縦）の当たり判定と座標補正
	position_.y += velocity_.y;

	// F. 接地フラグを一旦リセット
	isOnGround_ = false;

	left = position_.x - radius_.x;
	right = position_.x + radius_.x;
	top = position_.y - radius_.y;
	bottom = position_.y + radius_.y;

	leftCol = static_cast<int>(left / map_->GetTileSize());
	rightCol = static_cast<int>((right - 0.01f) / map_->GetTileSize());
	topRow = static_cast<int>(top / map_->GetTileSize());
	bottomRow = static_cast<int>((bottom - 0.01f) / map_->GetTileSize());

	if(velocity_.y > 0) { // 下に落下中
		if(map_->GetTileType(bottomRow, leftCol) == 1 || map_->GetTileType(bottomRow, rightCol) == 1) {
			position_.y = float(bottomRow * map_->GetTileSize()) - radius_.y;
			velocity_.y = 0; // 地面に着いたら縦方向の速度を0に
			isOnGround_ = true; // 接地フラグを立てる
		}
	} else if(velocity_.y < 0) { // 上に上昇中
		if(map_->GetTileType(topRow, leftCol) == 1 || map_->GetTileType(topRow, rightCol) == 1) {
			position_.y = float((topRow + 1) * map_->GetTileSize()) + radius_.y;
			velocity_.y = 0; // 天井にぶつかったら縦方向の速度を0に
		}
	}
}

Player::~Player() {
	delete shadowArea_;
}

ShadowDirection Player::GetShadowDirection() const {
	return isShadowDirection_;
}

void Player::ResolveCollision(FallingBlock& fallingBlock) {
	UpdateRect();
	Rect p = rect_;
	Rect b = fallingBlock.GetRect();

	if (!Collision::Intersect(p, b))
		return;

	float overlapX = std::min(p.right, b.right) - std::max(p.left, b.left);
	float overlapY = std::min(p.bottom, b.bottom) - std::max(p.top, b.top);

	if (overlapX < overlapY) {
		// X方向補正
		if (p.left < b.left) {
			position_.x -= overlapX; // 左から当たった
		} else {
			position_.x += overlapX; // 右から当たった
		}
		velocity_.x = 0;
	} else {
		// Y方向補正
		if (p.top < b.top) {
			position_.y -= overlapY; // 上から当たった
			isOnGround_ = true;
		} else {
			position_.y += overlapY; // 下から当たった
		}
		velocity_.y = 0;
	}
}

void Player::UpdateRect() {
	rect_ = {
	    position_.x - radius_.x,
	    position_.x + radius_.x,
	    position_.y - radius_.y,
	    position_.y + radius_.y,
	};
}
