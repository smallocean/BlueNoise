#include "My3DGrid.h"


using namespace std;

My3DGrid::My3DGrid(){
	//
}

My3DGrid::~My3DGrid(){
	//
}


int My3DGrid::CreateGrid(int size_x, int size_y, int size_z){
	_size[0]=size_x;
	_size[1]=size_y;
	_size[2]=size_z;

	_grid=alloc3D<std::vector<int> > (_size[0], _size[1],_size[2]);
	return 1;
}

int My3DGrid::CleanGrid(void){
	for(int xi=0; xi<_size[0]; xi++)
		for (int yi=0; yi<_size[1]; yi++)
			for (int zi=0; zi<_size[2]; zi++){
				_grid[xi][yi][zi].clear();
			}
		return 1;
}

int My3DGrid::Insert(int xi, int yi, int zi, int ele_id)
{
	_grid[xi][yi][zi].push_back(ele_id);
	return 1;
}

int My3DGrid::SetCellValue(int xi, int yi, int zi, int ele_id)
{
	//Íø¸ñÔªËØ¸³Öµ
	_grid[xi][yi][zi].clear();
	_grid[xi][yi][zi].push_back(ele_id);
	return 1;
}

int My3DGrid::remove(int xi, int yi, int zi, int ele_id)
{
	for (int ei=0; ei<_grid[xi][yi][zi].size(); ei++)	{
		if (_grid[xi][yi][zi][ei]==ele_id){
			_grid[xi][yi][zi].erase(_grid[xi][yi][zi].begin()+ei);
		}
	}
	
	return 1;
}

std::vector<int> My3DGrid::GetNeighbor(int xi, int yi, int zi, int xr, int yr, int zr)
{
	std::vector<int> neighbor_list;
	for (int ri=max(0, xi-xr); ri<=min(_size[0]-1,xi+xr); ri++)
		for (int ci=max(0, yi-yr); ci<=min(_size[1]-1,yi+yr); ci++)
			for (int ai=max(0, zi-zr); ai<=min(_size[2]-1,zi+zr); ai++){
				neighbor_list.insert(neighbor_list.end(),_grid[ri][ci][ai].begin(), _grid[ri][ci][ai].end());
			}

		return neighbor_list;

}

int My3DGrid::SetUpOnionOrder(int radius)
{
	onion_order.clear();
	for (int xi=-radius; xi<=radius; xi++){
		for (int yi=-radius; yi<=radius; yi++){
			for (int zi=-radius; zi<=radius; zi++){

				sort_ele ele;
				ele.key=(real)max(abs(xi), max(abs(yi),abs(zi)));
				ele.prop[0]=(real)xi;
				ele.prop[1]=(real)yi;
				ele.prop[2]=(real)zi;
				onion_order.push_back(ele);
			}
		}
	}
	sort(onion_order.begin(),onion_order.end(),sort_key_greater_than());

	return 1;
}

std::vector<int> My3DGrid::GetNeighbor_Onion(int xi, int yi, int zi) // !!! pre-requirement: SetUpOnionOrder(int radius) !!!
{
	std::vector<int> neighbor_list;
	for (unsigned int ei=0; ei<onion_order.size(); ei++){
		int xii=max(min( (int)(xi+onion_order[ei].prop[0]), (int)(_size[0]-1) ), 0);
		int yii=max(min( (int)(yi+onion_order[ei].prop[1]), (int)(_size[1]-1) ), 0);
		int zii=max(min( (int)(zi+onion_order[ei].prop[2]), (int)(_size[2]-1) ), 0);
	
		neighbor_list.insert(neighbor_list.end(),_grid[xii][yii][zii].begin(), _grid[xii][yii][zii].end());
	}

	return neighbor_list;

}


int My3DGrid::DeleteGrid(void)
{
	free3D(_grid);
	return 1;
}