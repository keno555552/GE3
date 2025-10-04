#pragma once
#include "BasicResource.h"
#include "VertexResource.h"
#include "VertexData.h"
#include "Material.h"
#include "MaterialConfig.h"
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


#pragma region Instance管理
public:
	void AddSpriteInstance(Vector2 pos, MaterialConfig material);
	//void ResmoveSpriteInstance();
	//void UpdateTileInstance();
	void AddModelInstance();
	//void ResmoveModelInstance();
	//void UpdateModelInstance();

public:
	struct SpriteInstance {
		Vector2 position;
		Vector2 scale;
		int materialConfigIndex;
		int layer;
		bool isDraw;
	};

	struct ModelInstance {
		Vector2 postion;
		Vector2 rotation;
		Vector2 scale;
		int modelID;
		int layer;
	};

public:
	std::vector<MaterialConfig*> materialConfigList_;
	std::vector<SpriteInstance*> spriteList_;
	std::vector<ModelInstance*> modelList_;

#pragma endregion

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

