#pragma once
#include "DircetXBase.h"
#include "externals/DirectXTex/DirectXTex.h"
#include "externals/DirectXTex/d3dx12.h"
#include <vector>
#include "shader_compile.h"
#include "PSO.h"
#include "ResourceManager.h"
#include "Vector4.h"
#include "VertexData.h"
#include "Material.h"
#include "DirectionalLight.h"

#include "Matrix4x4.h"
#include "TransformationMatrix.h"
#include "ConvertString.h"
#include "LightModelType.h"
#include "MaterialConfig.h"
#include "VertexIndex.h"



class DrawEngine
{
public:
	~DrawEngine();

	void Initialize(const char* kClientTitle, int kClientWidth, int kClientHeight, DirectXBase* directXDirver);

	void PreDraw();

	void SetDirectionalLight(DirectionalLight* light);

	/// 三角形関連
	void DrawTriangle(TransformationMatrix* wvpData, MaterialConfig material);
	/// 2D図形関連
	void CollectSprite(Vector2 pos, MaterialConfig material);
	void DrawSprite();
	void DrawSpriteDirect(Vector2 pos, MaterialConfig material);
	void DrawSpriteDirect(Vector2 pos, MaterialConfig material, Vector2 LTpos, Vector2 LBpos, Vector2 RTpos, Vector2 RBpos, float TsizeX, float TsizeY, Vector2 TCLTPos, Vector2 TCRBPos);

	void CollectTile(Vector2* pos, MaterialConfig material);
	void DrawTile(Vector2 pos, MaterialConfig material);
	
	/// 立方体関連
	void DrawCube(TransformationMatrix* wvpData, MaterialConfig material);
	/// 球体関連
	void DrawSphere(TransformationMatrix* wvpData, MaterialConfig material, int sudivision);
	/// モデル関連
	void DrawModel(TransformationMatrix* wvpData, std::vector<MaterialConfig> material,int modelHandle);
	void DrawModel(TransformationMatrix* wvpData, std::vector<MaterialConfig> material);
	bool SetModelTexture(Model* model);
	bool SetModelGroupTexture(Model* model);
	int SetModel(std::string Path);
	int readCommonTextureHandle(int Handle);
	int readModelTextureHandle(int Handle);
	int GetMuitModelNum(int modelHandle);

	int LoadTexture(const std::string& filePath);
	int LoadModelTexture(const std::string& filePath);

	void CompoDraw();

	void EndDraw();

private:
	Shader_compile* shader_compile_ = new Shader_compile;
	PSO* pso_ = new PSO;
	ResourceManager* resourceManager_ = nullptr;
	int modelHandle_ = 0;
	int modelGroupHandle_ = 0;
	DirectXBase* directXDriver_ = nullptr;

	int kClientWidth_ = 0;
	int kClientHeight_ = 0;

	int kMaxSudivision_ = 18;
	int kSudivision_ = 0;

private:
	LightModelType defaultLightModel_ = LightModelType::Lambert;
	LightModelType currentLightModel_ = defaultLightModel_;

private:
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;
	std::vector<ID3D12PipelineState*> PSO_;
	ID3D12RootSignature* rootSignature_ = nullptr;
	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};
	
	/// Textrue関連
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_{};
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_{};
	uint32_t textrueCounter = 1;
	std::vector<int> commonTextureSRVMap_;
	std::vector<int> modelTextureSRVMap_;
	int defaultTextureHandle_ = 0;						// white5x5
	ID3D12Resource* depthStencilResource = nullptr;

	///Lighting関連
	DirectionalLight* directionalLightData = {};

	int kParticleNumInstance_ = 10;

private:
	struct RenderResourceGroup {
		int resourceID;

		MaterialConfig* material;
		VertexResource* vertex;

	};

private:
	D3D12_VIEWPORT createViewport(int kClientWidth, int kClientHeight);
	D3D12_RECT createScissorRect(int kClientWidth, int kClientHeight);
	void SetMaterial(ID3D12Resource* resource, Matrix4x4 uvTransform, Vector4 color, int isLighting);
	void SetLighting(ID3D12Resource* resource, DirectionalLight* directionalLight);

	DirectX::ScratchImage LoadTextrueLow(const std::string& filePath);
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	ID3D12Resource* UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
	int MakeTextureShaderResourceView(const DirectX::TexMetadata& metadata, ID3D12Resource* textureResource);
	int MakeModelShaderResourceView(const DirectX::TexMetadata& metadata, ID3D12Resource* textureResource);
	int MakeParticleShaderResourceView(const DirectX::TexMetadata& metadata, ID3D12Resource* textureResource);
	ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);
	void MakeDepthStencilView();

	//Vector2 calTextruePos(Vector2 pos);

private:
	bool isFinish = false;
};

