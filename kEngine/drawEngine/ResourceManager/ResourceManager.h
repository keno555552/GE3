#pragma once
#include "BasicResource.h"
#include "VertexResource.h"
#include "VertexData.h"
#include "Material.h"
#include "VertexIndex.h"

class ResourceManager
{
public:
	struct TextureInfo {
		ID3D12Resource* texture;    
		int width;                 
		int height;                
		Vector4 uvOffset;           
	};

public:
	void AddSpriteInstance();
	void ResmoveSpriteInstance();
	void UpdateTileInstance();
	void AddModelInstance();
	void ResmoveModelInstance();
	void UpdateModelInstance();

public:
	struct SpriteInstance {
		Vector2 position;
		Vector2 scale;
		int tileType;
		Vector4 uvOffset;
		int layer;
	};

	struct ModelInstance {
		Vector2 postion;
		Vector2 rotation;
		Vector2 scale;
		int modelID;
		int layer;
	};

private:
	std::vector<SpriteInstance> spriteList;
	std::vector<ModelInstance> modelList;

public:
	/// 一回だけ作成するResource
	ResourceManager(ID3D12Device* device);
	/// 最後で解放するResource
	~ResourceManager();

	/// ランクこと作成するResource
	void CreateTurnResource();
	/// ランクこと解放するResource
	void ClearTurnResource();

	/// 借りのDevice
	ID3D12Device* Bdevice_ = nullptr;

	/// Material関係
	BasicResource* materialResourceTriangle_ = new BasicResource;
	BasicResource* materialResourceSprite_ = new BasicResource;
	BasicResource* materialResourceCube_ = new BasicResource;
	BasicResource* materialResourceSphere_ = new BasicResource;
	std::vector<BasicResource*> materialResourceModelGroup_;

	/// テクスチャ関係
	std::vector<std::string> commonTextureFilePath_;
	std::vector<TextureInfo> textureData_;
	BasicResource* textureResource_ = new BasicResource;
	BasicResource* intermediateResource_ = new BasicResource;/*EndDrawでTextrueを作ったら解放する*/

	/// Lighting関係
	ID3D12Resource* lightingResource_ = nullptr;

	/// 図形関係
	Triangle* vertexResourceTriangle_ = new Triangle;
	std::vector<Sprite2D*> vertexResourceSpriteGroup_;
	Cube* vertexResourceCube_ = new Cube;
	Sphere* vertexResourceSphere_ = new Sphere;
	std::vector<ModelGroup*> vertexResourceModelGroup_;

	/// 無用もの消し関連
	int deleteParameter = 0;
};

