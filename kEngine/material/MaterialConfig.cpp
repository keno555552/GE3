#include "MaterialConfig.h"


void intMaterialConfig(MaterialConfig* materialConfig) {
	 materialConfig->useOriginalTexture = true;
	 materialConfig->textureHandle = 0,
		 materialConfig->uvTranslate = { 0,0,0 },
		 materialConfig->uvScale = { 1,1,1 },
		 materialConfig->uvRotate = { 0,0,0 },
		 materialConfig->uvTransformMatrix = {},
		 materialConfig->textureColor = { 1.0f,1.0f,1.0f,1.0f },
		 materialConfig->lightModelType = LightModelType::HalfLambert,
		 materialConfig->enableLighting = true;
};