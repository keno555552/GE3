#include "Collision.h"
#include <cmath>

bool Collision::Intersect(const Rect& aRect, const Rect& bRect) { return (aRect.left < bRect.right && aRect.right > bRect.left && aRect.top < bRect.bottom && aRect.bottom > bRect.top); }
