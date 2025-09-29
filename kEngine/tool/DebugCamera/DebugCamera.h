#pragma once
#include "Matrix4x4.h"
#include "Transform.h"
#include "TransformationMatrix.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include "kEngine.h"
#include "config.h"

class DebugCamera
{
public:
	/// 初期化
	DebugCamera(kEngine* system,float WindowWidth, float WindowHeight);

	/// 更新
	void Update();

	/// スクリーン座標系転換
	TransformationMatrix transformationMatrixTransform(Transform objTransform);

	/// 直接座標指定
	void SetCamera(Transform cameraTransform);

	/// Mouse移動
	void MouseControlUpdate();

	/// 平行移動
	void Move(Vector3 speed);
	void Rotate(Vector3 Theta);

private:
	kEngine* system_ = nullptr;

	/// 累積回転行列
	Matrix4x4 matRot_;

	///カメラ変数を作る
	Transform cameraDefaultTransform_{ {1.0f,1.0f,1.0f},	// scale
									   {0.0f,0.0f,0.0f},	// rotate
									   {0.0f,0.0f,-5.0f} };	// translate

	Transform cameraTransform_{ cameraDefaultTransform_ };


	/// ProjectionMatrix
	Matrix4x4 projectionMatrix_{};
	/// ビュー行列
	Matrix4x4 viewMatrix_{};
};
