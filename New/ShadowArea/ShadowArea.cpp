#include "ShadowArea.h"
#include "../Map/Map.h"
#include "../../kEngine/tool/mathsUnit/Matrix3x3.h"
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

void ShadowArea::Initialize(kEngine* system) {
	// 画面の下半分に表示されるように設定
	width_ = float(kWindowWidth);                 // 横幅は画面いっぱい
	height_ = float(kWindowHeight) / 2.0f;       // 高さは画面の半分
	position_ = { 0.0f, float(kWindowHeight) / 2.0f }; // 表示位置は画面中央下から

	map_ = new Map;

	system_ = system;

	intMaterialConfig(&materialConfig_);
	materialConfig_.uvTransformMatrix = MakeAffineMatrix(materialConfig_.uvScale, materialConfig_.uvRotate, materialConfig_.uvTranslate);
	materialConfig_.textureHandle = system_->LoadTextrue("resources/white5x5.png");
}

void ShadowArea::Update(ShadowDirection direction) {
	// 毎フレーム、一旦サイズを0にリセット
	width_ = 0.0f;
	height_ = 0.0f;

	// --- 座標計算のための基本情報を定義 ---
	const float kTileSize = float(map_->GetTileSize());

	// 影を作るエリア
	const float kPlayableAreaWidth = kTileSize * 18.0f;
	const float kPlayableAreaHeight = kTileSize * 10.0f;

	const float kOffsetX = (kPlayableAreaWidth - kPlayableAreaWidth) / 2.0f;
	const float kOffsetY = (kPlayableAreaHeight - kPlayableAreaHeight) / 2.0f;

	const float kInnerMargin = kTileSize; // 上下の余白として使用

	// --- 指示に応じてBOXの状態を決定 ---
	switch(direction) {
	case ShadowDirection::Up:
		// 上半分に表示（左右ピッタリ、上下にマージン）
		position_ = { kOffsetX + kInnerMargin, kOffsetY + kInnerMargin };
		width_ = kPlayableAreaWidth;
		height_ = (kPlayableAreaHeight / 2.0f) - kInnerMargin;
		break;

	case ShadowDirection::Down:
		// 下半分に表示（左右ピッタリ、上下にマージン）
		position_ = { kOffsetX + kInnerMargin, kOffsetY + (kPlayableAreaHeight / 2.0f) };
		width_ = kPlayableAreaWidth;
		height_ = (kPlayableAreaHeight / 2.0f);
		break;

	case ShadowDirection::Left:
		// 左半分に表示（上下にマージン）
		position_ = { kOffsetX + kInnerMargin, kOffsetY + kInnerMargin };
		width_ = kPlayableAreaWidth / 2.0f;
		height_ = kPlayableAreaHeight - (kInnerMargin);
		break;

	case ShadowDirection::Right:
		// 右半分に表示（上下にマージin）
		position_ = { kOffsetX + (kPlayableAreaWidth / 2.0f) + kInnerMargin, kOffsetY + kInnerMargin };
		width_ = kPlayableAreaWidth / 2.0f;
		height_ = kPlayableAreaHeight - (kInnerMargin);
		break;

	case ShadowDirection::None:
	default:
		// 何もしない（BOXは非表示のまま）
		break;
	}
}


void ShadowArea::Draw() {
	// Noviceの描画関数を使って矩形を描画
	/*Novice::DrawBox(
		int(position_.x), int(position_.y),
		int(width_), int(height_),
		0.0f,
		BLACK,
		kFillModeSolid);*/

	//system_->DrawSprite(position_, materialConfig_);

	float top = position_.y - height_;
	float bottom = position_.y + height_;
	float right = position_.x + width_;
	float left = position_.x - width_;

	system_->DrawSprite(position_, materialConfig_, {left, top}, {left, bottom}, {right, top}, {right, bottom}, width_, height_, {0, 0}, {1, 1});
}

ShadowArea::~ShadowArea() {
	delete map_;
}
