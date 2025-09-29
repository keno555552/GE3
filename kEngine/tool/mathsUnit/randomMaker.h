#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
//#include "myMath.h"

inline int randomMaker = 0;

/// <summary>
/// int形上下限によるの乱数生成
/// </summary>
/// <param name="min">int形上限</param>
/// <param name="max">int形下限</param>
/// <returns>int数値</returns>
int randomInt(int min, int max);

/// <summary>
/// float形上下限によるの乱数生成
/// </summary>
/// <param name="min">float形上限</param>
/// <param name="max">float形下限</param>
/// <param name="numAfterPoint">小数点後の位数</param>
/// <returns>float乱数</returns>
float randomFloat(float min, float max, float numAfterPoint);

/// <summary>
/// 数位によるの乱数生成
/// </summary>
/// <param name="numAfterPoint">Int形数位</param>
/// <returns>int乱数</returns>
int randomNum(int numAfterPoint = 9);
