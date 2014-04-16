#include "MyClock.h"

MyClock::MyClock(void)
{
	
}

MyClock::~MyClock(void)
{
	
}

void MyClock::tic(void)
{
	t1=clock();
}

void MyClock::toc(void)
{
	t2=clock();
	float diff ((float)t2-(float)t1); 
	seconds = diff / CLOCKS_PER_SEC;
}