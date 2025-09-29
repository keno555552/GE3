#pragma once
#include "../Utility/Rect.h"

class Collision {
public:
	static bool Intersect(const Rect& aRect, const Rect& bRect);
};