#include "ResourceManager.h"

ResourceManager::ResourceManager(ID3D12Device* device) {

	Bdevice_ = device;

	materialResourceSprite_->CreateResource_(Bdevice_, sizeof(Material));

	vertexResourceTriangle_->CreateVertexResource_(Bdevice_);
	vertexResourceTriangle_->CreateVertexBufferView_(6);

	Sprite2D* vertexResourceSprite_ = new Sprite2D;
	vertexResourceSprite_->CreateVertexResource_(Bdevice_);
	vertexResourceSprite_->CreateVertexBufferView_(5);
	vertexResourceSprite_->CreateIndexResource_(Bdevice_);
	vertexResourceSprite_->CreateIndexBufferView_(12);
	vertexResourceSprite_->SetKeep(true);
	vertexResourceSpriteGroup_.push_back(vertexResourceSprite_);

	vertexResourceCube_->CreateVertexResource_(Bdevice_);
	vertexResourceCube_->CreateVertexBufferView_(24);
	vertexResourceCube_->CreateIndexResource_(Bdevice_);
	vertexResourceCube_->CreateIndexBufferView_(36);

}

ResourceManager::~ResourceManager() {
	///ID3D12Resource*の解放する
	//lightingResource_->Release();
	vertexResourceTriangle_->ClearVertexResource();
	if (!vertexResourceSpriteGroup_.empty()) {
		for (auto ptr : vertexResourceSpriteGroup_) {
			ptr->ClearAllResource();
			delete ptr;
		}
	}
	vertexResourceCube_->ClearAllResource();
	vertexResourceSphere_->ClearAllResource();
	textureResource_->ClearResource();
	intermediateResource_->ClearResource();

	materialResourceTriangle_->ClearResource();
	materialResourceSprite_->ClearResource();
	materialResourceCube_->ClearResource();
	materialResourceSphere_->ClearResource();

	if (!materialResourceModelGroup_.empty()) {
		for (auto& material : materialResourceModelGroup_) {
			if (material) {
				delete material;
				material = nullptr;
			}
		}
		materialResourceModelGroup_.clear();

		for (auto& modelGroup : vertexResourceModelGroup_) {
			//for (int model = 0; model < modelGroup->GetModelNum(); model++) {
			//}
			if (modelGroup) {
				delete modelGroup;
				modelGroup = nullptr;
			}
		}
		vertexResourceModelGroup_.clear();
	}


	delete textureResource_;
	delete vertexResourceTriangle_;
	delete vertexResourceCube_;
	delete vertexResourceSphere_;
}

void ResourceManager::CreateTurnResource() {
	lightingResource_ = CreateResource(Bdevice_, sizeof(DirectionalLight));
}

void ResourceManager::ClearTurnResource() {
	deleteParameter++;

	intermediateResource_->ClearResource();

	materialResourceTriangle_->ClearResource();
	//materialResourceSprite_->ClearResource();
	materialResourceCube_->ClearResource();
	materialResourceSphere_->ClearResource();

	lightingResource_->Release();

	vertexResourceTriangle_->ClearWVPResource();

	if (!vertexResourceSpriteGroup_.empty()) {
		int i = 0;
		auto ptr = vertexResourceSpriteGroup_.begin();

		while (ptr != vertexResourceSpriteGroup_.end()) {
			(*ptr)->ClearWVPResource();

			if (deleteParameter % 100 == 0) {
				if ((*ptr)->GetKeep() != true && i != 0) {
					(*ptr)->ClearAllResource();
					delete* ptr; // 釋放 Sprite2D 實例
					ptr = vertexResourceSpriteGroup_.erase(ptr); // 從容器移除指標
					++i;
					continue; // 跳過 ++it
				} else {
					(*ptr)->SetKeep(false);
				}
			}

			++ptr;
			++i;
		}
	}

	vertexResourceCube_->ClearWVPResource();
	vertexResourceSphere_->ClearWVPResource();

	if (!materialResourceModelGroup_.empty()) {
		for (auto& material : materialResourceModelGroup_) {
			material->ClearResource();
		}
		for (auto& modelGroup : vertexResourceModelGroup_) {
			for (int model = 0; model < modelGroup->GetModelNum(); model++) {
				modelGroup->GetModel(model)->ClearWVPResource();
			}
		}
	}

}