#include "headfile.h"
#include "my_time.h"

double nowtime = 0;
double end_time =0;
double spent1 = 0;
double spent2 = 0;
int isstart = 0;
int isend = 2;

void action();
void finsh();
double cur();
double Endtime();

void action()
{
		if(P26 == 0 && recording == 0)
		{
				isstart = 1;
				isend = 1;
		}
		
}

void finsh()
{
		if(P26 == 0 && recording == 2)
		{
//				isend = 0;
		}
		
}

double cur()
{

	spent2 = spent2 + 1;
	
	return spent2 * 5 / 1000 ;
	
}

double Endtime()
{
	spent1 = spent1 + 1;
	return spent1 * 5 / 1000;
}