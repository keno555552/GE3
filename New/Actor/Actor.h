#pragma once
#include "../../kEngine/tool/mathsUnit/Vector2.h"
#include "../Utility/Rect.h"

// オブジェクトの基底クラス
class Actor {
public:
	//virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;

protected:
	Vector2 position_{}; // 座標
	Vector2 radius_{};   // 半径

	// 物理演算用のメンバ変数を追加
	Vector2 speed_{};  // プレイヤーの基本速度
	bool isOnGround_{};    // 地面に接しているか
	Vector2 velocity_{};   // 速度
	Vector2 acceleration_{}; // 加速度

	Rect rect_{};

	// 体力系
	int health_{}; // HP
	bool isAlive_{}; // 生存フラグ
};
