#ifndef _MYCLOCK_H
#define _MYCLOCK_H


#include <ctime>
#include <cmath>

using namespace std;

class MyClock{
protected:
	clock_t t1,t2;    //ʱ��
	
public:
	float seconds;   //����ʱ��

public:
	MyClock(void);
	virtual ~MyClock(void);

	void tic(void);   //��ʼʱ��
	void toc(void);   //����ʱ��

};

#endif