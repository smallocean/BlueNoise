#include "SobelFilter.h"


SobelFilter::SobelFilter(void){
	_orientation = -1;
}

int SobelFilter::setOrientation(const int orientation){

	if(orientation < 0)
		return 0;
	_orientation = orientation;
}
SobelFilter::~SobelFilter(void)
{

}
real SobelFilter::Query(const Array<float> & image, const vector<int> & query) const
{
    if(image.Dimension() != query.size())
    {
      
		cerr<<"SobelFilter::Query(): dimension mismatch"<<endl;
    }

    if((_orientation < 0) || (_orientation >= image.Dimension()))
    {
     
		cerr<<"SobelFilter::Query(): illegal orientation"<<endl;
    }

    if(image.Dimension() != 2)
    {
       
		cerr<<"SobelFilter::Query(): support only 2D image now!"<<endl;
    }

    float output = 0;
    float value = 0;
    vector<int> index(query);

    // 这里只能处理二维图像
    for(int i = -1; i <= 1; i+=2)
        for(int j = -1; j <= 1; j++)
        {
            index[_orientation] = i + query[_orientation];
            index[1-_orientation] = j + query[1-_orientation];
            
            const float weight = i*(1 + (j==0));

            if(image.Get(index, value))
            {
                output += value*weight;
            }
        }
    
    return output;
}
