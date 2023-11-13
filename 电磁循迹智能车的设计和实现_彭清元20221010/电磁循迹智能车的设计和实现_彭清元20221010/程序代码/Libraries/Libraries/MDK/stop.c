#include "headfile.h"
#include "stop.h"

int stop_cnt = 0;
int cheku_flag = 0;
int cheku_flag1 = 0; 
int stop_flag = 0;

void my_stop();
void cheku();
void cheku_plus();

void my_stop()
{
		if(ad[0] < 2 && ad[1] < 2 && ad[2] < 2 && ad[3] < 2 && ad[4]< 2 && ad[5]< 2)
		{ 
			stop_cnt = stop_cnt + 1;
		}
		
		if(ad[0] > 40 && ad[1] > 40)
		{
		 stop_cnt = 0;
		}
		
		if(stop_cnt > 40 && !stop_flag)
		{
//			run = 0;
        stop_flag = 1;
		}
		if(stop_flag)
		{
			all_speed_L = 0;
			all_speed_R = 0;
			ki_l = 20;
			ki_r = 20;
		}

}

int che_cut = 0;
int che_a = 0;
void cheku()
{
	if(!P26 && !cheku_flag && recording == 2)  //改条件
	{
		cheku_flag = 1;
//		run = 0;
		all_speed_L = 0;
		all_speed_R = 0;
		ki_l = 20;
		ki_r = 20;
		che_cut = 0;
	}
	if(cheku_flag == 1 && che_cut <30)
	{
		che_cut = che_cut + 1;
	}
	if(cheku_flag == 1 && che_cut >20)
	{
		che_cut = 0;
		cheku_flag = 2;
	}
	if(cheku_flag == 2) //倒车
	{
		all_speed_L = -30;
		all_speed_R = -30;
		duty_ = mid;
	}
	if(cheku_flag == 2 && che_cut < 1000)
	{
		che_cut = che_cut + 1;
	}

	if(in_normall_speed == 60) che_a = 40;
	if(in_normall_speed == 65) che_a = 55;
	if(in_normall_speed == 70) che_a = 65;
	if(cheku_flag == 2 && che_cut > che_a && !open) //可改
	{
		cheku_flag = 3;
		open = 1;
		sum_angle = 0;
	}
	if(cheku_flag == 3) duty_ = right;
	if(cheku_flag == 3 && (abs(sum_angle) > 90 ))
	{
		cheku_flag = 4;
		open = 0;
		sum_angle = 0;
	}
	if(cheku_flag == 4) 		duty_ = mid;
	if(cheku_flag == 4 && ((ad[2] > 170 && ad[3] > 170  && ad[7] > 40 && ad[8] > 40)  ))
	{
		cheku_flag = 5;

	}
	if(cheku_flag == 5)
	{
		all_speed_L = 0;
		all_speed_R = 0;
		ki_l = 20;
		ki_r = 20;
	}
}

void cheku_plus()
{
	if(recording == 1 && cheku_flag1 == 1 && !cheku_flag)
	{
		cheku_flag = 1;	
		che_cut = 0;
	}
	if(cheku_flag == 1 || cheku_flag == 2)
	{
		che_cut = che_cut + (nowspeed_L + nowspeed_R) / 2;
	}
	if(cheku_flag == 1) 
	{
		all_speed_L = 80;
		all_speed_R = 80;
	}
	if(cheku_flag == 1 && che_cut > 14100)    //前走一段
	{

		cheku_flag = 2;
	}
	if(cheku_flag == 2 && che_cut > 15400)
	{
		che_cut = 0;
		cheku_flag = 3;
	}
	if(cheku_flag == 2)   //开始入库
	{
		all_speed_L = 60;
		all_speed_R = 60;
		ki_l = 10;
		ki_r = 10;
	}
	if(cheku_flag == 3 && !open)
	{
		open = 1;
		sum_angle = 0;
	}
	if(cheku_flag == 3)
	{
		duty_ = right;
	}
	if(cheku_flag == 3 && abs(sum_angle) > 60)
	{
		open = 0;
		sum_angle = 0;
		cheku_flag = 4;
		che_cut = 0;
	}
//	if(cheku_flag == 4)
//	{
//		duty_ = mid; 
//		che_cut = che_cut + 1;
//	}
//	if(cheku_flag == 3 && che_cut > 50)
//	if(cheku_flag == 4)
//	{
//		che_cut = 0;
//		cheku_flag = 4;
//	}
	if(cheku_flag == 4)
	{
		all_speed_L = 0;
		all_speed_R = 0;
		ki_l = 20;
		ki_r = 20;
	}
}