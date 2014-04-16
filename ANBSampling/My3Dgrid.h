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
	int _size[3];             //网格大小
	real _bin_width[3];
	std::vector<int> ***_grid;
protected:
	std::vector<sort_ele> onion_order;

public:
	My3DGrid(void);
	virtual~My3DGrid(void);

	
	int Insert(int xi, int yi, int zi, int ele_id); //插入元素
	int remove(int xi, int yi, int zi, int ele_id); //删除元素
	int SetCellValue(int xi, int yi, int zi, int ele_id);//修改值
	int CleanGrid(void);       //清空网格
	int DeleteGrid(void);      //删除网格
	int CreateGrid(int size_x, int size_y, int size_z); //创建网格
	int SetUpOnionOrder(int radius); //建立采样顺序
	std::vector<int> GetNeighbor(int xi, int yi, int zi, int xr, int yr, int zr); //获取领域
	std::vector<int> GetNeighbor_Onion(int xi, int yi, int zi); // radius and orders are set up in "SetUpOnionOrder(int radius)"


};

#endif

