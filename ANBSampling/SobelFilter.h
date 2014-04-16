#pragma once
#include "Filter.h"
class SobelFilter:public Filter
{
public:

	int _orientation;          //对象


public:
	SobelFilter(void);
	int setOrientation(const int orientation);  //设置图像对象
	real Query(const Array<float> & image, const vector<int> & index) const;

	~SobelFilter(void);
};

