#include "headfile.h"
#include "shizi.h"

int shizi = 0;
int enter_shizi = 0;
int leave_shizi = 0;
int shizi_step = 0;
int die = 0;
int shizi_angle = 0;
int shizi_cnt = 100;
int shizi_bu = 0;

void pd_shizi() 
{
	if(shizi == 0)
	{
		left = 760;
	}
	if(!shizi && (((ad[0] >70 && ad[1] > 70) || (ad[0] + ad[1] > 150)) && 
		((ad[2] > 60 && ad[3] > 60) || (ad[2] + ad[3]) > 120) && my_divide(ad[2],ad[3]) < 2) && shizi_cnt > 90 && !flag[1])
	{
	   buzzer(true);
	   shizi = 1;
		 open = 1;
		 sum_angle = 0;
		 left = 753;
	}
	if(shizi_cnt < 100) shizi_cnt = shizi_cnt+1;
	if(shizi && shizi_bu < 20100) shizi_bu = shizi_bu + (nowspeed_L + nowspeed_R) / 2;
	if((abs(sum_angle) > 260 || shizi_bu > 20000)&& shizi && iscir == 0)
	{
		 buzzer(false);
	   shizi = 0;
		 open = 0;
		 sum_angle = 0;
		 left = 760;
		 shizi_cnt = 0;
	 	 shizi_bu = 0;
	}
}
