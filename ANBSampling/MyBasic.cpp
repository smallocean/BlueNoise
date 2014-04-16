#include "MyBasic.h"

Point3::Point3(std::vector<real> this_position, std::vector<real> this_normal)
{
	_position=this_position;
	_normal=this_normal;
}

Point3::Point3(std::vector<real> this_position)
{
	_position=this_position;
}

Point3::Point3(void)
{
	
}




