#pragma once
#include "Model.h"
#include <vector>

std::vector<ModelData> LoadMuitObjFile(const std::string& directoryPath, const std::string& filename);

class ModelGroup
{
public:
	~ModelGroup();

	Model* GetModel(int handle){return modelGroup_[handle];}
	void pushModel(Model* model);
	void SetModelObj(std::string Path);
	std::string GetDirectoryPath() { return directoryPath_; }
	std::string GetObjName_() { return objName_; }
	void PushModelHandle(int handle) { modelHandle_.push_back(handle); }
	int GetModelHandle(int handle) { return modelHandle_[handle]; }
	int GetModelNum() { return (int)modelGroup_.size();}


private:
	std::string directoryPath_ = "resources/object/plane";
	std::string objName_ = "plane.obj";
	std::vector<Model*> modelGroup_;
	std::vector<int> modelHandle_;
};

