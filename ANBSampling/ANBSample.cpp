#include "ANBSample.h"
#include <math.h>

/*
copyright owned by Hong xiaoyang(CQUPT VIS LAB)
ANBSample.cpp
Date:2013.9.11 - 2013.9.12
*/


ANBSample::ANBSample(void)
{
}


ANBSample::~ANBSample(void)
{
}

int ANBSample::Normalize_BoundingBox(){

	//���ӻ�

	real width[3] = {  //������Χ�������
		boundingbox[1] - boundingbox[0],
		boundingbox[3] - boundingbox[2],
		boundingbox[5] - boundingbox[4],
	};
	real scale_ratio  = max(width[0],max(width[1],width[2]));  //����

	//�������꣬������ӳ�䵽������
	unsigned int vi = 0,di = 0; 
	for(vi = 0;vi<dense_pt_list.size();vi++){

		for(di = 0; di<dense_pt_list[vi]->_position.size();di++){

			dense_pt_list[vi]->_position[di] = dense_pt_list[vi]->_position[di]/scale_ratio;

		}

	}
	return 1;


}

vector<int>ANBSample::GridIndex(sample *p){

	//������������
	vector<int>_index(3);

	for(int i = 0; i < 3; i++){

		_index[i]=min( (int)grid._size[i]-1, (int)max(0, (int)floor((p->_position[i]-boundingbox[i*2])/grid._bin_width[i])) );

	}

	return  _index;
}
bool ANBSample::conflict_check(sample *s1 ,sample *s2){

	//��ײ���

	if(conflict_Radius(s1,s2)){
		return true;
	}
	else 
		return false;
}
bool ANBSample::conflict_Radius(sample *s1 , sample *s2){

	//�뾶���
	if(Mixture_Distance(s1,s2)<1.0f){
		return true;
	}
	else 
		return false;
	/*

	if(Anisotropic_Distance(s1,s2)<1.0f){
	return true;
	else
	return false;
	}	
	*/
}

real ANBSample::Distance(sample *p1,sample *p2){

	//������֮��ŷ�Ͼ���
	return p1->distance(p2);
}

real ANBSample::Distance_radius(sample *p1 ,sample *p2){

	//����뾶�ľ���
	real d = p1->distance(p2);
	return d/(0.5 * (p1->r + p2->r ));
}

real ANBSample::Mixture_Distance(sample *p1,sample *p2){
	//��Ͼ���
	real dp(0.0f),dn(0.0f);

	dp=p1->distance_sq(p2);
	dp/=sigma_P2;              //��׼����  ����1��
	for (unsigned di=0; di<p1->_normal.size(); di++)
	{
		dn+=(p1->_normal[di]-p2->_normal[di])*(p1->_normal[di]-p2->_normal[di])/sigma_N2;
	}

	return sqrt(dp+dn)/(0.5f*(p1->r+p2->r));

}

real ANBSample::Anisotropic_Distance(sample *p1,sample *p2){

	//�������Ծ���
	real dp(0.0),dn(0.0);
	dp = p1->distance_sq(p2);
	dp /= sigma_N2;
	for (unsigned di=0; di<p1->_normal.size(); di++)
	{
		dn+=(p1->_normal[di]-p2->_normal[di])*(p1->_normal[di]-p2->_normal[di])/sigma_N2;
	}

	return sqrt(dp+dn)/(0.5f*(p1->r+p2->r));
}
int ANBSample::DartThrowing(){

	//Dart-Throwing��

	int trail = 0;
	int neighbor_range = 3; //�ֲ�����Χ
	int rand_pt_ind;        //���������
	if(USING_ONION_ORDER){
		grid.SetUpOnionOrder(neighbor_range);  //��ʼ����
	}

#if ORDER_TYPE == 0
	random_shuffle(dense_pt_list.begin(),dense_pt_list.end());
	int id_counter = 0;
	vector<sample *>::iterator it;      //���õ������
	for (it=dense_pt_list.begin();it!=dense_pt_list.end();++it){

		(*it)->_ID = id_counter;    //��ȡ�������id

	}

	for(int i = 0 ; i < dense_pt_list.size(); i++){

		rand_pt_ind = i;
#elif ORDER_TYPE == 1
	for(int i = 0 ; i < dense_pt_list.size(); i++){
		rand_pt_ind = i;
#else
#endif
	sample *s = dense_pt_list[rand_pt_ind];  //�����㼯
	if(pt_list.empty()){

		s->acp_ID = pt_list.size();
		pt_list.push_back(s);

		//����������뵽������
		vector<int> g_ind = GridIndex(s);
		grid.SetCellValue(g_ind[0],g_ind[1],g_ind[2],s->acp_ID);

		trail = 0;
		continue;
	}
	else{
		vector<int>g_ind =GridIndex(s); 
		vector<int>neighbor;
		if(USING_ONION_ORDER){

			neighbor = grid.GetNeighbor_Onion(g_ind[0],g_ind[1],g_ind[2]);

		}
		else{
			neighbor = grid.GetNeighbor(g_ind[0],g_ind[1],g_ind[2],neighbor_range, neighbor_range,neighbor_range);
		}
		int neighbor_ind;
		bool conflict = false;
		for (unsigned int nsi=0; nsi<neighbor.size(); nsi++){
			neighbor_ind=neighbor[nsi];
			while(true)
			{ 
				if(conflict_check(pt_list[neighbor_ind], s))
				{

					conflict=true;
					trail++;


					nsi=neighbor.size();
					break;
				}



				if(pt_list[neighbor_ind]->next==NULL)// arrive the end of current grid cell
				{
					break;
				}
				else
				{
					neighbor_ind=pt_list[neighbor_ind]->next->acp_ID;
				}
			}// end while(true)
		}//end for (unsigned nsi=0; nsi<neigbor.size(); nsi++)

		if (!conflict){
			s->acp_ID=pt_list.size();
			pt_list.push_back(s);

			// �������������
			std::vector<int> g_ind=GridIndex(s);
			if(!grid._grid[g_ind[0]][g_ind[1]][g_ind[2]].empty())
			{
				s->next=pt_list[ grid._grid[g_ind[0]][g_ind[1]][g_ind[2]][0] ];
				pt_list[ grid._grid[g_ind[0]][g_ind[1]][g_ind[2]][0] ]->pre=s;
			}

			grid.SetCellValue(g_ind[0], g_ind[1], g_ind[2], s->acp_ID);

			trail=0;				
			}
		}
	}
	return 1;
}
int ANBSample::process(){
	
	//��������
	int grid_size[3];
	grid_size[0]=grid_size[1]=grid_size[2]=1.0f/r_global;
	
	

	real model_width[3]={
		boundingbox[1]-boundingbox[0],
		boundingbox[3]-boundingbox[2],
		boundingbox[5]-boundingbox[4]};

	real cell_wid=(model_width[0])/( grid_size[0]*1.0f );
	grid_size[1]=max((int)floor(model_width[1]/cell_wid),1);
	grid_size[2]=max((int)floor(model_width[2]/cell_wid),1);


	grid.CreateGrid(grid_size[0],grid_size[1],grid_size[2]);
	for (int i=0; i<3; i++)
	{
		grid._bin_width[i]=model_width[i]/(grid._size[i]*1.0f);
	}


	DartThrowing();
	grid.CleanGrid();
	grid.DeleteGrid();
	return 1;
}

int ANBSample::ReadinPt(char *file_in,string INPUT_TYPE){
	
	//�����
	ifstream infile(file_in);
	if(!infile.is_open()){
		cout<<"�޷����ļ�:"<<file_in<<endl;
		return  0 ;
	}
	cout<<"���ڶ�ȡ"<<file_in << "..."<<endl;
	boundingbox[0]=boundingbox[2]=boundingbox[4]=INF;
	boundingbox[1]=boundingbox[3]=boundingbox[5]=-INF;
	int NumV;   //ģ�͵���
	if (INPUT_TYPE=="TXT")
	{
		infile>>NumV;
	}
	else{
		//����������ʽ
		//��.off,.obj�ȸ�ʽ�ļ�
	}

	for (int i=0; i<NumV; i++)
	{
		sample* this_pt= new sample;
		this_pt->_position=std::vector<real>(3);
		this_pt->_normal=std::vector<real>(3);
		for(int di=0; di<3; di++)
		{
			infile>>this_pt->_position[di];
			if(boundingbox[di*2]>this_pt->_position[di])
				boundingbox[di*2]=this_pt->_position[di];
			if(boundingbox[di*2+1]<this_pt->_position[di])
				boundingbox[di*2+1]=this_pt->_position[di];

		}

		for(int di=0; di<3; di++)
		{
			infile>>this_pt->_normal[di];
		}
		
		this_pt->r=r_global;
		this_pt->pre=NULL;
		this_pt->next=NULL;

		dense_pt_list.push_back(this_pt);
	}

	infile.close();

	cout<<"ģ�͹���"<<dense_pt_list.size()<<"����"<<endl;
	printf("Box����Χ =[ %f, %f, %f ]\n", boundingbox[1]-boundingbox[0],boundingbox[3]-boundingbox[2],boundingbox[5]-boundingbox[4]);

	return 1;
}
int ANBSample::WritePt(char *filename ,string OUTPUT_TYPE,bool _WITH_RADIUS,bool NORMAL){

	//д�������
	//ply�ļ�������������Ͳ���
	std::ofstream outfile(filename);
	if(!outfile.is_open())
	{
		printf("�޷����ļ�: %s\n",filename);
		return(0);
	}

	if(OUTPUT_TYPE == "OFF")
	{
		outfile<<"OFF"<<endl;
		outfile<<pt_list.size()<<"  "<<"0"<<"   "<<"0"<<endl;
	}
	else if(OUTPUT_TYPE == "TXT")
	{
		outfile<<pt_list.size()<<endl;
	}
	else if(OUTPUT_TYPE == "PLY")
	{
		outfile<<"ply"<<endl;
		outfile<<"format ascii 1.0"<<endl;
		outfile<<"comment VCGLIB generated"<<endl;
		outfile<<"element vertex "<<pt_list.size()<<endl;
		outfile<<"property float x"<<endl
			<<"property float y"<<endl
			<<"property float z"<<endl;
		if (NORMAL)
		{
			outfile<<"property float nx"<<endl
				<<"property float ny"<<endl
				<<"property float nz"<<endl;
		}		
		outfile<<"element face 0"<<endl<<"property list uchar int vertex_indices"<<endl<<"end_header"<<endl;
	}

	for (unsigned int i=0; i<pt_list.size(); i++)
	{
		for (int di=0; di<3; di++)
		{
			outfile<<pt_list[i]->_position[di]<<"  ";
		}
		if(_WITH_RADIUS)
		{
			outfile<<pt_list[i]->r<<"  ";
		}

		if (NORMAL)
		{
			for (int di=0; di<3; di++)
			{
				outfile<<pt_list[i]->_normal[di]<<"  ";
			}

		}

		outfile<<endl;
	}
	outfile.close();
}

int ANBSample::cleanUpPoints(){
	
	//��ղ���
	for (unsigned int i = 0 ; i < dense_pt_list.size();i++){
		
		delete dense_pt_list[i];

	}
	dense_pt_list.clear();
	return 1;
}