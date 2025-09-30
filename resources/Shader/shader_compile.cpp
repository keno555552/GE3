#include "shader_compile.h"
#include "ConvertString.h"
#include <cassert>

Shader_compile::~Shader_compile()
{
	dxcUtils->Release();
	dxcCompiler->Release();
	includeHandler->Release();
}

void Shader_compile::Initialize()
{
	///dxcCompilerを初期化
	//IDxcUtils* dxcUtils = nullptr;
	//IDxcCompiler3* dxcCompiler = nullptr;
	dxcUtils = nullptr;
	dxcCompiler = nullptr;
	HRESULT hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));
	assert(SUCCEEDED(hr));
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
	assert(SUCCEEDED(hr));

	/// 現時点でincludeはしないが、includeに対応するための設定を行っておく
	//IDxcIncludeHandler* includeHandler = nullptr;
	hr = dxcUtils->CreateDefaultIncludeHandler(&includeHandler);
	assert(SUCCEEDED(hr));

}

