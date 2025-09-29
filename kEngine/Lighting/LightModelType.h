#pragma once
#include <string>

enum class LightModelType {
    Lambert,
    HalfLambert,
    NumLightModels
};

std::string GetLightModelMacro(LightModelType model);