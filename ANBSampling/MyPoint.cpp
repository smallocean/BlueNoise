#include "MyPoint.h"


MyPoint::MyPoint(void)
{
	//
}
MyPoint::MyPoint(bool _posi, bool _norm)
{
	if(_posi)
		_position=std::vector<real>(3);
	if(_norm)
		_normal=std::vector<real>(3);

}

MyPoint::MyPoint(int p_dim, int n_dim)
{
	_position=std::vector<real>(p_dim);
	_normal=std::vector<real>(n_dim);
}


MyPoint::~MyPoint(void)
{
	//
}


int MyPoint::printPoint(void)
{
	// printf out the point information
	if (_position.size()>0)
	{
		printf("\t position:[%f, %f, %f]\n", _position[0],  _position[1], _position[2]);
	}
	else
	{
		printf(" Empty point!\n");
		return 0;
	}
	if (_normal.size()>0)
	{
		printf("\t normal:[%f, %f, %f]\n", _normal[0],  _normal[1], _normal[2]);
	}
	
	return 1;

}

real MyPoint::distance(MyPoint *a)
{
	if(a->_position.size()!=_position.size())
	{
		printf("dimension in consistent!\n");
		return -1;
	}

	real dist(0);
	for (unsigned di=0; di<_position.size(); di++)
	{
		dist+=(_position[di]-a->_position[di])*(_position[di]-a->_position[di]);
	}

	return sqrt(dist);
}


real MyPoint::distance_sq(MyPoint *a)
{
	if(a->_position.size()!=_position.size())
	{
		printf("dimension in consistent!\n");
		return -1;
	}

	real dist(0);
	for (unsigned di=0; di<_position.size(); di++)
	{
		dist+=(_position[di]-a->_position[di])*(_position[di]-a->_position[di]);
	}

	return dist;
}
real MyPoint::distance_geo_normal(MyPoint *a)
{
	real geodist(0), normal_diff2(0);

	// approximated geodesic distance
	std::vector<real> posi_diff_dir(3,0);

	for (int di=0; di<3; di++)
	{
		posi_diff_dir[di]=_position[di]-a->_position[di];
	}
	geodist=distance(a);
	Normalize(posi_diff_dir,posi_diff_dir);
	real c1,c2;
	c1=DotProduct(_normal,posi_diff_dir);
	c2=DotProduct(a->_normal,posi_diff_dir);

	geodist=geodist*(asin(c1)-asin(c2))/(c1-c2);

	return geodist;
}

//-------utility functions------//

int Normalize(std::vector<real> d, std::vector<real> &nd)
{
	nd=d;
	real l=length(d);
	for (unsigned int i=0; i<nd.size(); i++)
	{
		nd[i]=nd[i]/l;
	}
	return 1;
}

real DotProduct(std::vector<real> v1, std::vector<real> v2)
{
	real dotp(0);
	if(v1.size()!=v2.size())
	{
		cerr<<"DotProduct::not equivalent size!\n";
		return 0;
	}

	for(unsigned int di=0; di<v1.size(); di++)
	{
		dotp+=v1[di]*v2[di];
	}

	return dotp;

}

real length(std::vector<real> L)
{
	real l=0; 
	for (unsigned int i=0; i<L.size(); i++)
	{
		l+=(L[i]*L[i]);
	}

	return (sqrt(l));
}