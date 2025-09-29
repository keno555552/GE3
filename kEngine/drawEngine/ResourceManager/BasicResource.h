#pragma once
#include "DircetXBase.h"
#include <vector>

ID3D12Resource* CreateResource(ID3D12Device* device, size_t sizeInBytes);

class BasicResource
{
public:
	~BasicResource();
	
	ID3D12Resource* CreateResource_(ID3D12Device* device, size_t sizeInBytes);
	ID3D12Resource* SaveResource_(ID3D12Resource* resource);
	ID3D12Resource* GetResource(int Index = -1);

	void ClearResource();

private:
	std::vector<ID3D12Resource*> resource_;
	int resourceCounter = 0;
};

