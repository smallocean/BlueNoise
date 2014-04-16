//sample.cpp
#include <iostream>
#include <vector>
#include "ANBSample.h"
#include "MyBasic.h"
#include "MyClock.h"
using namespace std;

int main(int argc,char **argv){
	
	cout <<"�����ʽ��ANBSample.exe  input.txt output.ply sigmaP  sigmaN radius \n"<<endl;
	if(argc!=6){
		cout <<"�����ʽ��ANBSample.exe  input.txt output.ply sigmaP  sigmaN radius \n"<<endl;
		return 0;
	}
	int arg_count = 1;
	char *infile = argv[arg_count++];     //�����ļ���
	char *outfile = argv[arg_count++];    //����ļ���

	real sigma_P = atof(argv[arg_count++]); //Blue Noise����
	real sigma_N = atof(argv[arg_count++]); //Feature����
	real radius = atof(argv[arg_count]);    //�����뾶

	real rho = 0.75;  //��ʵ�����뾶ϵ��(һ����0.75  A comparision method of Poisson Disk Generation)
	int max_trail = 55000; //����������
	 
	ANBSample AnisotropicDartThrowing;
	MyClock timer;
	srand (time(NULL));
	AnisotropicDartThrowing.r_global = radius;
	AnisotropicDartThrowing.rho = rho;
	AnisotropicDartThrowing.max_trail = max_trail;
	AnisotropicDartThrowing.sigma_P2 = sigma_P * sigma_P;
	AnisotropicDartThrowing.sigma_N2 = sigma_N * sigma_N;
	AnisotropicDartThrowing.ReadinPt(infile,"TXT");
	timer.tic();
	AnisotropicDartThrowing.process();
	timer.toc();
	cout<<"������ʱ:"<<timer.seconds<<endl;
	cout<<"���ɵĲ�������:"<<AnisotropicDartThrowing.pt_list.size()<<endl;
	AnisotropicDartThrowing.WritePt(outfile,"PLY",false,true);
	AnisotropicDartThrowing.cleanUpPoints();
	return 1;

}