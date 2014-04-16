//sample.cpp
#include <iostream>
#include <vector>
#include "ANBSample.h"
#include "MyBasic.h"
#include "MyClock.h"
using namespace std;

int main(int argc,char **argv){
	
	cout <<"输入格式：ANBSample.exe  input.txt output.ply sigmaP  sigmaN radius \n"<<endl;
	if(argc!=6){
		cout <<"输入格式：ANBSample.exe  input.txt output.ply sigmaP  sigmaN radius \n"<<endl;
		return 0;
	}
	int arg_count = 1;
	char *infile = argv[arg_count++];     //输入文件名
	char *outfile = argv[arg_count++];    //输出文件名

	real sigma_P = atof(argv[arg_count++]); //Blue Noise参数
	real sigma_N = atof(argv[arg_count++]); //Feature参数
	real radius = atof(argv[arg_count]);    //采样半径

	real rho = 0.75;  //真实采样半径系数(一般是0.75  A comparision method of Poisson Disk Generation)
	int max_trail = 55000; //最大采样点数
	 
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
	cout<<"采样耗时:"<<timer.seconds<<endl;
	cout<<"生成的采样点数:"<<AnisotropicDartThrowing.pt_list.size()<<endl;
	AnisotropicDartThrowing.WritePt(outfile,"PLY",false,true);
	AnisotropicDartThrowing.cleanUpPoints();
	return 1;

}