#include "Mathematics.h"

float MapRangeClamped(float value, float inRangeMin, float inRangeMax, float outRangeMin, float outRangeMax)
{
	value = FMath::Clamp(value, inRangeMin, inRangeMax);	//Clamp the inputed value to the range of the inRange values.
	float PercentageIn = ((value - inRangeMin) / std::abs(inRangeMax - inRangeMin)) * 100;	//Get the Percentage of the inputed value
	float outValue = (PercentageIn / 100) * std::abs(outRangeMax - outRangeMin);	//Get the percentage Equivalent in the Range of Output Expectation.
	int *x = new int();
	return outValue;
}

