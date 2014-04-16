/*
copyright owned by Hong xiaoyang(CQUPT VIS LAB)

ANBSample.h
Date:2013.9.11
*/


#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>  //用来生成随机采样
#include <vector>
#include "My3Dgrid.h"
#include "MyBasic.h"
#include "MyPoint.h"
using namespace std;


#define USING_ONION_ORDER 1         //
#define ORDER_TYPE 0 //随机顺序   ORDER_TYPE = 1  扫描顺序


struct sample;
struct sample:MyPoint{
	real r;     //采样半径
	real density; //采样密度
	int acp_ID;   //采样接受标志
	sample *pre;   //前一个采样
	sample *next;  //后一个采样
};
class ANBSample
{
public:
	vector<sample*>pt_list; //点序列容器
	real r_global;    //全局半径
	real rho;         //最小半径
	real sigma_P2;    //Blue Noise属性
	real sigma_N2;    //feature属性
	int expected_stipple_size;  //点绘制
	int max_trail;   //最大尝试次数
	string _METHOD_TYPE;//采样方法


	vector<sample*>dense_pt_list;//点序列
	real _r_max;//最大半径
	real _r_min;//最小半径
	real _r_avg;//平均半径
	My3DGrid grid;//网格
	real boundingbox[6];//坐标
public:


	ANBSample(void);
	virtual ~ANBSample(void);
	//距离度量
	real Distance(sample *p1 , sample *p2);   //欧氏距离
	real Distance_radius(sample *p1, sample *p2);//融入半径的距离
	real Mixture_Distance(sample *p1 , sample *p2);//双边距离
	real Anisotropic_Distance(sample *p1 , sample *p2);//各向异性距离

	int Normalize_BoundingBox();    //归一化

	vector<int>GridIndex(sample *s); //建立网格索引
	int DartThrowing();     //投飞镖采样
	int Anisotropic_DartThrowing(); //各向异性投飞镖

	real Lloyd_Relaxation();    //Lloyd松弛迭代

	bool conflict_check(sample *s1,sample *s2);  //碰撞检测
	bool mean_metric();       //平均度量
	bool max_metric();         //最大度量
	bool conflict_Radius(sample *s1 , sample *s2); //半径检测
	bool conflict_Bilateral(sample *s1,sample *s2);//双边检测

	//读写
	int ReadinPt(char *file_in ,string INPUT_TYPE);//读入点
	int WritePt(char *filename ,string OUTPUT_TYPE,bool _WITH_RADIUS,bool NORMAL);//输出

	int cleanUpPoints();   //清空采样
	
	//分析
	real Fourier_Radial_AVG(); //计算径向均值谱
	real Fourier_Anisotropy_AVG(); //各向异性谱

	int process();//处理过程



};

