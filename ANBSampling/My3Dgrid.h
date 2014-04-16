#ifndef _MY_3D_GRID_H_
#define _MY_3D_GRID_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include "MyBasic.h"
#include "MyUtility.h"

using namespace std;

class My3DGrid{
public:
	int _size[3];             //�����С
	real _bin_width[3];
	std::vector<int> ***_grid;
protected:
	std::vector<sort_ele> onion_order;

public:
	My3DGrid(void);
	virtual~My3DGrid(void);

	
	int Insert(int xi, int yi, int zi, int ele_id); //����Ԫ��
	int remove(int xi, int yi, int zi, int ele_id); //ɾ��Ԫ��
	int SetCellValue(int xi, int yi, int zi, int ele_id);//�޸�ֵ
	int CleanGrid(void);       //�������
	int DeleteGrid(void);      //ɾ������
	int CreateGrid(int size_x, int size_y, int size_z); //��������
	int SetUpOnionOrder(int radius); //��������˳��
	std::vector<int> GetNeighbor(int xi, int yi, int zi, int xr, int yr, int zr); //��ȡ����
	std::vector<int> GetNeighbor_Onion(int xi, int yi, int zi); // radius and orders are set up in "SetUpOnionOrder(int radius)"


};

#endif

