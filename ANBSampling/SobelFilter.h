#pragma once
#include "Filter.h"
class SobelFilter:public Filter
{
public:

	int _orientation;          //����


public:
	SobelFilter(void);
	int setOrientation(const int orientation);  //����ͼ�����
	real Query(const Array<float> & image, const vector<int> & index) const;

	~SobelFilter(void);
};

