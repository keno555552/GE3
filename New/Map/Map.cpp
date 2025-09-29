#include "Map.h"
#include "../ShadowArea/ShadowArea.h"
#include "../CSVLoader/CsvLoader.h"
#include "../../kEngine/tool/mathsUnit/Matrix3x3.h"

Map::Map() {
	// メンバ変数の初期化
	mapData_.clear();
	tileSetTexture_ = -1;
	tileSize_ = 64; // タイルのサイズを32x32に設定
	rows_ = 0;
	cols_ = 0;
}

void Map::Initialize(const char* mapFilePath, const char* tileSetFilePath, kEngine* system) {
	// エラーを消している。画像読み込みをするならこの処理はいらない。
	tileSetFilePath;
	// CsvLoaderを使ってマップデータを読み込む
	mapData_ = CsvLoader::Load(mapFilePath);
	// 元のマップデータをコピーして保存しておく
	originalMapData_ = mapData_;

	// マップの行数と列数を取得
	rows_ = static_cast<int>(mapData_.size());
	if (rows_ > 0) {
		cols_ = static_cast<int>(mapData_[0].size());
	}

	system_ = system;

	intMaterialConfig(&materialConfig_);
	materialConfig_.uvTransformMatrix = MakeAffineMatrix(materialConfig_.uvScale, materialConfig_.uvRotate, materialConfig_.uvTranslate);
	materialConfig_.textureHandle = system_->LoadTextrue(tileSetFilePath);

	// タイルセット画像を読み込む
	// tileSetTexture_ = Novice::LoadTexture(tileSetFilePath);
}

void Map::Update() {
	// 今は特に何もしない
}

void Map::Draw() {
	// 2重ループでマップデータを1マスずつ見ていく
	for (int y = 0; y < rows_; ++y) {
		for (int x = 0; x < cols_; ++x) {

			// 現在のマスに対応するマップチップ番号を取得
			int tileType = mapData_[y][x];

			// マップ番号が1の時だけ、ブロックを描画する
			if (tileType == 1) {
				// 画面に描画する先の座標を計算
				int destX = x * tileSize_ / 2;
				int destY = y * tileSize_ / 2;

				Vector2 dest = {static_cast<float>(destX), static_cast<float>(destY)};
				int radius = tileSize_ / 2;

				float top = static_cast<float>(destY - radius);
				float bottom = static_cast<float>(destY + radius);
				float right = static_cast<float>(destX + radius);
				float left = static_cast<float>(destX - radius);

				system_->DrawSprite(dest, materialConfig_, {left, top}, {left, bottom}, {right, top}, {right, bottom}, static_cast<float>(tileSize_), static_cast<float>(tileSize_), {0, 0}, {1, 1});
			}
		}
	}
}

void Map::ApplyShadowEffect(const ShadowArea& shadow) {
	// ① まず、現在のマップの状態を、記憶しておいた元の状態に完全に戻す
	mapData_ = originalMapData_;

	// 影のBOXの範囲を取得
	float shadowLeft = shadow.GetPosition().x;
	float shadowRight = shadowLeft + shadow.GetWidth();
	float shadowTop = shadow.GetPosition().y;
	float shadowBottom = shadowTop + shadow.GetHeight();

	// ② 影の範囲内にある「壁(1)」を「影(3)」に書き換える
	for (int y = 0; y < rows_; ++y) {
		for (int x = 0; x < cols_; ++x) {
			// マス目の範囲を計算
			float tileLeft = static_cast<float>(x * tileSize_);
			float tileRight = static_cast<float>((x + 1) * tileSize_);
			float tileTop = static_cast<float>(y * tileSize_);
			float tileBottom = static_cast<float>((y + 1) * tileSize_);

			// 矩形の交差判定
			if (shadowLeft < tileRight && tileLeft < shadowRight && shadowTop < tileBottom && tileTop < shadowBottom) {

				// 重なっているマスの元の番号が「壁(1)」なら「影(3)」に書き換える
				if (originalMapData_[y][x] == 1) {
					mapData_[y][x] = 3;
				}
			}
		}
	}
}

int Map::GetTileType(int row, int col) const {
	// マップの範囲外かどうかをチェック
	if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
		return 1; // 範囲外は壁として扱う
	}
	// 範囲内なら、その場所のタイル番号を返す
	return mapData_[row][col];
}

int Map::GetTileSize() const { return tileSize_; }

Vector2Int Map::ToTileCoord(const Vector2& worldPos) { return static_cast<Vector2Int>(static_cast<int>(worldPos.x / tileSize_), static_cast<int>(worldPos.y / tileSize_)); }
