#ifndef _MYPOINT_H
#define _MYPOINT_H

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

#include "MyBasic.h"
//#include "MyBasicFunction_real.h"

class MyPoint{
public:
	int _ID;          //������
	std::vector<real> _position;//������   
	std::vector<real> _normal;  //�㷨��
	//std::vector<real> _velocity;
	//std::vector<real> _acc;
	std::vector<real> _moving_dir;
	std::vector<real> _pNx, _pNy, _pNz;// _pNx �Ǹ�������Ԫ�ص�����: partial Nx partial x, partial Nx partial y, partial Nx partial z;
									
	std::vector<int> _id; 
	std::vector<int> _nb_list; // in relaxation, in site list, this vector records the underlying point list 
	real _radius;       //�뾶
	real _weight;       //Ȩ��
	bool _active;       //�����־

public:
	MyPoint(void);
	MyPoint(int p_dim, int n_dim);
	MyPoint(bool _posi, bool _norm); // initialize Point
	virtual~MyPoint(void);

	int printPoint();
	real distance(MyPoint *a);       //ŷ�Ͼ���
	real distance_sq(MyPoint *a);
	real distance_geo_normal(MyPoint *a); // ����߾������ "Parallel Poisson Disk Sampling with Spectrum Analysis on Surfaces",  (SIGGRAPH Asia 2010)
	

};

//-------����������------//
real length(std::vector<real> L);
int Normalize(std::vector<real> d, std::vector<real> &nd);
real DotProduct(std::vector<real> v1, std::vector<real> v2);
#endif
