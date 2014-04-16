#pragma once
#include <iostream>
#include <vector>
#include "MyBasic.h"
#include "Array.h"
using namespace std;
class Filter
{
public:
	Filter(void);
	virtual ~Filter(void) = 0 ;    //ÐéÎö¹¹º¯Êý
	virtual real Query(const Array<float>&image , const vector<int>&index)const;

};

