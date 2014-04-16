#ifndef _MYCLOCK_H
#define _MYCLOCK_H


#include <ctime>
#include <cmath>

using namespace std;

class MyClock{
protected:
	clock_t t1,t2;    //时间
	
public:
	float seconds;   //采样时间

public:
	MyClock(void);
	virtual ~MyClock(void);

	void tic(void);   //开始时间
	void toc(void);   //结束时间

};

#endif