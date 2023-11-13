#include "headfile.h"
#include "my_Math.h"
#include "math.h"

int my_abs(int res);
float my_divide(int a,int b);

int my_abs(int res)
{
    if(res > 0) return res;
    return res * -1;
}

float my_divide(int a,int b)
{
    
    int temp1 = my_abs(a);
    
    int temp2 = my_abs(b);
    
    if(temp1 > temp2 ) return (float)( (float)(temp1) / (float)(temp2) );
    
    return (float)( (float)(temp2) / (float)(temp1));
        
}


double my_KP(double x)
{
	double res = 0;
	res = (abs( (exp(-abs(x) ) - 1 ) / (exp(-abs(x) ) + 1 ) / 2 ) + 0.515 ) * 1.34;
	
	return res;
}
