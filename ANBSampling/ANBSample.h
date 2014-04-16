/*
copyright owned by Hong xiaoyang(CQUPT VIS LAB)

ANBSample.h
Date:2013.9.11
*/


#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>  //���������������
#include <vector>
#include "My3Dgrid.h"
#include "MyBasic.h"
#include "MyPoint.h"
using namespace std;


#define USING_ONION_ORDER 1         //
#define ORDER_TYPE 0 //���˳��   ORDER_TYPE = 1  ɨ��˳��


struct sample;
struct sample:MyPoint{
	real r;     //�����뾶
	real density; //�����ܶ�
	int acp_ID;   //�������ܱ�־
	sample *pre;   //ǰһ������
	sample *next;  //��һ������
};
class ANBSample
{
public:
	vector<sample*>pt_list; //����������
	real r_global;    //ȫ�ְ뾶
	real rho;         //��С�뾶
	real sigma_P2;    //Blue Noise����
	real sigma_N2;    //feature����
	int expected_stipple_size;  //�����
	int max_trail;   //����Դ���
	string _METHOD_TYPE;//��������


	vector<sample*>dense_pt_list;//������
	real _r_max;//���뾶
	real _r_min;//��С�뾶
	real _r_avg;//ƽ���뾶
	My3DGrid grid;//����
	real boundingbox[6];//����
public:


	ANBSample(void);
	virtual ~ANBSample(void);
	//�������
	real Distance(sample *p1 , sample *p2);   //ŷ�Ͼ���
	real Distance_radius(sample *p1, sample *p2);//����뾶�ľ���
	real Mixture_Distance(sample *p1 , sample *p2);//˫�߾���
	real Anisotropic_Distance(sample *p1 , sample *p2);//�������Ծ���

	int Normalize_BoundingBox();    //��һ��

	vector<int>GridIndex(sample *s); //������������
	int DartThrowing();     //Ͷ���ڲ���
	int Anisotropic_DartThrowing(); //��������Ͷ����

	real Lloyd_Relaxation();    //Lloyd�ɳڵ���

	bool conflict_check(sample *s1,sample *s2);  //��ײ���
	bool mean_metric();       //ƽ������
	bool max_metric();         //������
	bool conflict_Radius(sample *s1 , sample *s2); //�뾶���
	bool conflict_Bilateral(sample *s1,sample *s2);//˫�߼��

	//��д
	int ReadinPt(char *file_in ,string INPUT_TYPE);//�����
	int WritePt(char *filename ,string OUTPUT_TYPE,bool _WITH_RADIUS,bool NORMAL);//���

	int cleanUpPoints();   //��ղ���
	
	//����
	real Fourier_Radial_AVG(); //���㾶���ֵ��
	real Fourier_Anisotropy_AVG(); //����������

	int process();//�������



};

