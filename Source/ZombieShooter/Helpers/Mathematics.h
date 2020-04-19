#pragma once

#include "CoreMinimal.h"
#include <cstdlib>
#include <cmath>

/**
 * This Function is meant to return a value which is based on some conditions.
 * The in Range Values represent the range of value that the input value is expected to be.
 * The out Range values represent the range of value that the return value is meant to be 
 * So this function Clamps the input to the range of input values and returns the equivalent in the range of output values
 **/
float MapRangeClamped(float value, float inRangeA, float inRangeB, float outRangeA, float outRangeB);