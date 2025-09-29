#pragma once
#include <vector>
#include "../Utility/Vector2Int.h"
#include "../../kEngine/tool/mathsUnit/Vector2.h"
#include "../../kEngine/kEngine.h"
#include "../../kEngine/material/MaterialConfig.h"

class ShadowArea;

class Map {
public:
	// コンストラクタ
	Map();

	// 初期化（CSVファイルとタイルセット画像を読み込む）
	void Initialize(const char *mapFilePath, const char *tileSetFilePath, kEngine* system);

	// 更新処理（マップが動く場合などに使用）
	void Update();

	// 描画処理
	void Draw();

	// 影の効果をマップに適用する関数を宣言
	void ApplyShadowEffect(const ShadowArea &shadow);

	// 指定した座標のタイル番号を返すゲッターを追加
	int GetTileType(int row, int col) const;
	// タイルサイズを返すゲッターを追加
	int GetTileSize() const;

	int GetRows() { return rows_; }

	int GetCols() { return cols_; }

	// ワールド座標をマップチップのグリッド座標に変換する関数
	Vector2Int ToTileCoord(const Vector2& worldPos);

private:
	// マップデータを保持する2次元配列
	std::vector<std::vector<int>> mapData_;

	// 元のマップデータを保持する2次元配列を追加
	std::vector<std::vector<int>> originalMapData_;

	// タイルセットのテクスチャハンドル
	int tileSetTexture_;

	// 1マスのサイズ（64）
	int tileSize_;

	// マップの行数と列数
	int rows_;
	int cols_;

	kEngine* system_;

	MaterialConfig materialConfig_;
};
