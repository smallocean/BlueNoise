

#ifndef _MYUTILITY_H
#define _MYUTILITY_H


#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

#define FOR_EVERY_CELL_3D(maxI,maxJ,maxK)	for( int i=0; i<maxI; i++ ) for( int j=0; j<maxJ; j++ ) for( int k=0; k<maxK; k++ ) {
#define FOR_EVERY_CELL_2D(maxI,maxJ)	for( int i=0; i<maxI; i++ ) for( int j=0; j<maxJ; j++ )  {
#define FOR_EVERY_CELL_CUBE(N)		for( int i=0; i<N; i++ ) for( int j=0; j<N; j++ ) for( int k=0; k<N; k++ ) {
#define FOR_EVERY_X_FLOW(N)	for( int i=0; i<N+1; i++ ) for( int j=0; j<N; j++ ) for( int k=0; k<N; k++ ) {
#define FOR_EVERY_Y_FLOW(N)	for( int i=0; i<N; i++ ) for( int j=0; j<N+1; j++ ) for( int k=0; k<N; k++ ) {
#define FOR_EVERY_Z_FLOW(N)	for( int i=0; i<N; i++ ) for( int j=0; j<N; j++ ) for( int k=0; k<N+1; k++ ) {

#define FOR_EVERY_POINT(maxI) for ( int i=0; i<maxI; i++ ) {
#define FOR_EVERY_DIMENSION(n)for( int di=0; di<n; di++ )  {
#define FOR_EVERY_NEIGHBOR(maxI) for ( int ni=0; ni<maxI; ni++ ) {

#define FOR_EVERY(maxI) for ( int i=0; i<maxI; i++ ) {
#define END_FOR }


//for image
#define FOR_EACH_PIXEL(size_1, size_2) for(int ri=0; ri<size_1; ri++) for (int ci=0; ci<size_2; ci++){
#define FOR_EACH_R_PIXEL(size_1, size_2) for(int ri=0; ri<size_1; ri++) for (int ci=0; ci<size_2; ci++){
#define FOR_EACH_G_PIXEL(size_1, size_2) for(int ri=0; ri<size_1; ri++) for (int ci=0; ci<size_2; ci++){
#define FOR_EACH_B_PIXEL(size_1, size_2) for(int ri=0; ri<size_1; ri++) for (int ci=0; ci<size_2; ci++){

// for sample
#define FOR_EACH_SAMPLE(sample_size) for(int si=0; si<sample_size; si++){

template <class T> T *** alloc3D( int w, int h, int d ) {
	T *** field = new T **[w+1];
	for( int i=0; i<w; i++ ) {
		field[i] = new T*[h+1];
		for( int j=0; j<h; j++ ) {
			field[i][j] = new T[d];
		}
		field[i][h] = NULL;
	}
	field[w] = NULL;	
	return field;
}

template <class T> void free3D( T ***ptr ) {
	for( int i=0; ptr[i]!=NULL; i++ ) {
		for( int j=0; ptr[i][j]!=NULL; j++ ) delete [] ptr[i][j];
		delete [] ptr[i];
	}
	delete [] ptr;
}


template <class T> T ** alloc2D( int w, int h) {
	T ** field = new T *[w+1];
	for( int i=0; i<w; i++ ) {
		field[i] = new T[h];
	}
	field[w] = NULL;	
	return field;
}

template <class T> void free2D( T **ptr ) {
	for( int i=0; ptr[i]!=NULL; i++ ) {
		
		delete [] ptr[i];
	}
	delete [] ptr;
}

//struct sort_ele{
//	real key;
//	real prop[5];
//	int id;
//};

struct sort_ele{
	float key;
	float prop[5];
	int id;
};

// sorting, from smaller to larger
struct sort_key_greater_than {
	bool operator()(sort_ele const& a, sort_ele const& b) const {
		if(a.key != b.key)
			return a.key < b.key;
		return a.id < b.id;
	}
};

// sorting, from larger to small
struct sort_key_smaller_than {
	bool operator()(sort_ele const& a, sort_ele const& b) const {
		if(a.key != b.key)
			return a.key > b.key;
		return a.id > b.id;
	}
};

template <class T>
int sign(T a){
	if (a>0)
	{
		return 1;
	}
	if (a==0)
	{
		return 0;
	}
	if(a<0)
	{
		return -1;
	}

	printf("error::int sign(T a)\n");
	return 0;
}


/*
   Return a RGB colour value given a scalar v in the range [vmin,vmax]
   In this case each colour component ranges from 0 (no contribution) to
   1 (fully saturated), modifications for other ranges is trivial.
   The colour is clipped at the end of the scales if v is outside
   the range [vmin,vmax]
*/

typedef struct {
    double r,g,b;
} COLOUR;

COLOUR GetColour(double v,double vmin,double vmax);



#endif