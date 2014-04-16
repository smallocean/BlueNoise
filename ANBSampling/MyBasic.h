#ifndef _BASIC_H
#define _BASIC_H

#include <vector>

#pragma warning( disable : 4267 )
#pragma warning( disable : 4018 )


//统一参数类型
#define DOUBLE_PRECISION 0  //1: double; 
//0: float

#if DOUBLE_PRECISION
typedef double real;
const real PI = 3.1415926535;
#else
typedef float real;
const real PI = 3.1415926535f;
#endif



#define EPSILON 1e-7      //误差限
#define INF 1e+10         //溢出标志

class Point3{
public:
	std::vector<real> _position;   //点坐标
	std::vector<real> _normal;     //点法相

public:
	Point3(void);                   //点
	Point3(std::vector<real> this_position);
	Point3(std::vector<real> this_position, std::vector<real> this_normal);
	//virtual~ Point3(void);

	real x(){return _position[0];}  //坐标x
	real y(){return _position[1];}  //坐标y
	real z(){return _position[2];}  //坐标z

};




#endif