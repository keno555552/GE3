#pragma once
#include "DircetXBase.h"

class DircetXCommen:public DirectXBase
{
public:
	~DircetXCommen();
	void StartFrame();
	void EndFrame();
private:
	D3D12_RESOURCE_BARRIER barrier{};
};

