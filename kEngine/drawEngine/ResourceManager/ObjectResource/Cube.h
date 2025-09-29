#pragma once
#include "VertexData.h"
#include "Transform.h"
#include "TransformationMatrix.h"
#include "VertexResource.h"
#include "Config.h"

class Cube :public VertexResource
{
public:
	ID3D12Resource* CreateVertexResource_(ID3D12Device* device)override;
	ID3D12Resource* CreateIndexResource_(ID3D12Device* device)override;
	ID3D12Resource* SetWVPResource_(ID3D12Device* device, TransformationMatrix* wvpData);

private:
	enum {
		FRONT_TOP_LEFT = 0,
		FRONT_TOP_RIGHT,
		BACK_TOP_RIGHT,
		BACK_TOP_LEFT,
		FRONT_BOTTOM_LEFT,
		FRONT_BOTTOM_RIGHT,
		BACK_BOTTOM_RIGHT,
		BACK_BOTTOM_LEFT
	};
	void SetWVP(TransformationMatrix* wvpData);
};