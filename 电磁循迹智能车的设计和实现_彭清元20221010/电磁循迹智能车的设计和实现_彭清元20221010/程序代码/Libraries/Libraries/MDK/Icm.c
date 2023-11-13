#include "headfile.h"
#include "Icm.h"

double sum_angle = 0; //????
float w_angle = 0;  //?õ¶?
float w_angle_y = 0;
double sum_angle_y = 0;
int flag_po = 0;
int ang_y_flag = 0;
int speed_yuan;

void angle();
void podao();
	
void angle()
{
	if(fork_right == 1)
	{
		if(w_angle < 0)
		{
			sum_angle += w_angle * 0.005;
		}
	}
	
	else sum_angle += w_angle * 0.005;
}

void angle_y()
{
	sum_angle_y += w_angle_y * 0.005;
	
}

void podao()
{
		angle_y();

		if(sum_angle_y < -6 && flag_po == 0)
		{
				flag_po = 1;
		}
		
		
		if(flag_po)	
		{
			ki_l = 10;
			ki_r = 10;
			if(in_left_speed >40)
			{
				speed_yuan = in_left_speed;
				in_left_speed = 40;
			}	

		}	
	
}