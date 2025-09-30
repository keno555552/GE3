#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include <dxgidebug.h>
#pragma comment(lib,"dxguid.lib")

#include <dxcapi.h>
#pragma comment(lib,"dxcompiler.lib")
#include "DircetXBase.h"
#include "PSO.h"


class Shader_compile{
public:
	~Shader_compile();

	void Initialize();
	IDxcUtils* getDxcUtils() { return dxcUtils; }
	IDxcCompiler3* getDxcCompiler() { return dxcCompiler; }
	IDxcIncludeHandler* getIncludeHandler() { return includeHandler; }

private:
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;
private:
};
