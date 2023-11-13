#include "headfile.h"
#include "servo.h"
#include "math.h"
#include "stdlib.h"


double place = 0;
double cha1;
double he1;
double cha2;
double he2;
double p;
double i;
double d;
double s_error;
int duty_ = 670;
int mid = 670; //650 730
int left = 760;   
int right = 585;
int n_s = 0;
double s_last_error;
double tuo;
double tuo_l = 0;

double cha_s;
double he_s;
double error_s;
double place_s;
double ps;
double is;
double ds;

double s_a;
double s_b;
double s_c;
int out = 0;
int compensate = 0; // 补偿
int Magnetic = 270; // 磁场强度

double smooth[20] = { 0 }; // 读取10 个 终端中的 误差 作为 偏差
double last_dy;
void my_dead()
{

}

void cal_compensate()
{
	int sum_ad = ad[4] + ad[5] + ad[9];
	
	if(sum_ad  < Magnetic)
	{
		compensate = (Magnetic - sum_ad) * 0.5;
	}
	
	else 
	{
		compensate = 0;
	}
	
	if(compensate > 20)
	{
		compensate = 20;
	}
	
	else 
	{
		compensate = compensate;
	}
}

void Servoinit()
{

	if(out == 0)
	{
		duty_ = 580;
	}
	if(open == 0 && out == 0)
	{
	   open = 1;
		 sum_angle = 0;
	}
	
	if((( ((ad[0] > 70 && ad[1] > 70 )|| (ad[0] + ad[1] > 140)) && (ad[7] + ad[8]) < 50) || (abs(sum_angle)>60 )) && !out)
	{
		out = 1;
		open = 0;
		sum_angle = 0;
	}

	
	if (soon_leave == 1)
	{
		duty_ = 752;
	}
	
	// 判断圆环第一个标志点 矫正姿态
	if(enter_Left == 1 && iscir == 0)
	{
		if(duty_ <= mid) duty_ += 4;
		else duty_ -= 4;
	}
	
  pwm_duty(PWMB_CH1_P74, duty_);
}


int PID_servo(){

//			在圆环里

			if(s_flag3)  //在三岔内部
			{
				
				if(in_forks_left == 1)  //在三岔左边
				{
					
					temp_ad[4] = ad[4];  // 对 ad 进行处理
					temp_ad[5] = ad[5];	 // 对 ad 进行处理
					if(ad[4] < 15 && ad[5] < 15)
					{
						
						// 引入 temp_ad 防止误判出三叉
						temp_ad[4] = ad[4] * 0.8 +  ad[0] * 0.5;
						temp_ad[5] = ad[5] * 0.8 +  ad[1] * 0.5;
					}
					
					if(abs(sqrt(ad[7]) - sqrt(ad[8])) > abs(sqrt(ad[2]) - sqrt(ad[3])))
					{
						cha2 = sqrt(ad[7]) - sqrt(ad[8]);
					}
					
					else 
					{
						cha2 = sqrt(ad[2]) - sqrt(ad[3]);
					}
					
					cha1 = ( sqrt(temp_ad[4])  - sqrt(temp_ad[5]) ) ; //水平电感差

//				cha2 = (sqrt(ad[7]) - sqrt(ad[8])) ; // 竖直电感差
					

					he1 =  (temp_ad[4] + temp_ad[5]); // 水平电感和
					
				}
				
				if(in_forks_right == 1) //在三岔右边
				{
					
					temp_ad[4] = ad[4];  // 对 ad 进行处理
					temp_ad[5] = ad[5];	 // 对 ad 进行处理
					
					if(ad[4] < 15 && ad[5] < 15)
					{
						temp_ad[4] = ad[4] * 0.7 +  ad[0] * 0.5;
						temp_ad[5] = ad[5] * 0.7 +  ad[1] * 0.5;
					}
					
					cha1 =   sqrt(temp_ad[4]) - sqrt(temp_ad[5]) ; //水平电感差
					
					cha2 =  sqrt(ad[7]) - sqrt(ad[8]); // 竖直电感差
					
					he1 =  (temp_ad[4] + temp_ad[5]); // 水平电感和
				
				}
	
			}
			
			else 
			{
			
//				if(normal_left == 1)
//				{
//						
//					cha1 = ( (ad[4]) - (ad[5]) ) ; //水平电感差
//		
//					he1 =   (ad[4] + ad[5]) ; // 水平电感和
//		
//					cha2 =  ((ad[7]) - (ad[8])); //竖直电感差
//				}

//				else
				{
				
					if(cir_sancha == 1)
					{
						
					if(ad[4] < 15 && ad[5] < 15)
					{
						ad[4] = ad[4] * 0.3 +  ad[0] * 0.7;
						ad[5] = ad[5] * 0.3 +  ad[1] * 0.7;
						cha2  = sqrt(ad[2]) - sqrt(ad[3]);
					}
					
					else if(ad[4] < 35 && ad[5] < 35)
					{
						ad[4] = ad[4] * 0.5 +  ad[0] * 0.5;
						ad[5] = ad[5] * 0.5 +  ad[1] * 0.5;
						cha2  = sqrt(ad[2]) - sqrt(ad[3]);
					}
					
					else
					{
					
						if(((ad[4] - ad[5]) > 20 && (ad[7] - ad[8]) > 10) || ((ad[4] - ad[5]) < -20 && (ad[7] - ad[8]) < -10) )
						{
								if(abs(sqrt(ad[7]) - sqrt(ad[8])) > abs(sqrt(ad[2]) - sqrt(ad[3])))
								{
										cha2 = sqrt(ad[7]) - sqrt(ad[8]);
								}
								
								else 
								{
										cha2 = sqrt(ad[2]) - sqrt(ad[3]);
								}
					 }
					 
						else 
						{
               cha2 = 0;
						}
	
					}
						cha1 = sqrt(ad[4] + 0.3 * ad[0] + ad[9]) - sqrt(ad[5]  + 0.3 * ad[1] + ad[9]) ; //水平电感差

						he1 =  ad[4] + ad[5] + ad[9]; // 水平电感和
					}
					
					else 
					{
						if(ad[4] < 15 && ad[5] < 15)
						{
							temp_ad[4] = ad[4] +  ad[0];
							temp_ad[5] = ad[5] +  ad[1];
							
//							cha2  = sqrt(ad[2]) - sqrt(ad[3]);
						}
						
						else if(ad[4] < 35 && ad[5] < 35)
						{
							temp_ad[4] = ad[4] +  ad[0] * 0.5;
							temp_ad[5] = ad[5] +  ad[1] * 0.5;
							
//							cha2  = sqrt(ad[2]) - sqrt(ad[3]);
						}
						else 
						{
						
							temp_ad[4] = ad[4];
							temp_ad[5] = ad[5];
							
//							cha2  = sqrt(ad[7]) - sqrt(ad[8]);
						}
							
							cha1 = sqrt(temp_ad[4]) - sqrt(temp_ad[5]); 	

							he1 =  temp_ad[4] + temp_ad[5] + ad[7] + ad[8]; // 水平电感和
							
							if( (sqrt(ad[7]) - sqrt(ad[8])) > (sqrt(ad[4]) - sqrt(ad[5])) )
							
							cha2 = sqrt(ad[7]) - sqrt(ad[8]);
							
							else cha2 = sqrt(ad[4]) - sqrt(ad[5]);
						
						}
			}
		}

	    s_a = 1;     //水平电感比例

			if( my_abs(cha2) > 50  )
			{
				s_b = 0.45;
			}
			
			if( my_abs(cha2) > 30 )
			{
				s_b = 0.35;
			}
			
			else 
			{
				s_b = 0.25;  //竖直电感比例
			}
			
			if(in_left) s_b = 0.8; // 左边三岔内
			
			s_c = 0.1;  //竖直电感和的比例
			
			if(cha2 == 0)
			{
				 s_error	= 10000 * ( 1 * cha1 + 0.17 * cha2 ) / ( he1);
			}
			
			else 
			{
					if(cir_sancha == 1)
					{
						s_error	= 8000 * ( 1.25 * cha1 + 0.15 * cha2 ) / ( he1 + my_abs(ad[7] - ad[8]));
					}
					
					else s_error	= 10000 * ( 0.83 * cha1 + 0.165 * cha2 ) / ( he1);
			}	
	
	    tuo = w_angle * 0.6 + 0.4 * tuo_l; //一阶惯性滤波
			
			if(tuo > 100)
			{
				tuo = 100;
			}
			
			if(tuo < -100)
			{
				tuo = -100;
			}
	
			if(!s_flag3 )  // 在正常轨道上循迹	
			{
					// 修改
					if(s_error > 500) s_error = 500;
					
					else if(s_error < - 500) s_error = -500;
					
					else 
					{
						s_error = s_error;
					}
					
					if(cir_sancha == 1)
					{
						
						p = 0.11 + log10(abs(s_error) + 1) * 0.028;

						d = 0.1 + 1 / ( sqrt(abs(s_error) * 2 ) + 1000);
					}
					else 
					{
					
//						p = s_error * s_error * 0.000002 + 0.11; 76 挺好


						// 摆出去 加常数

						p = s_error * s_error * 0.00000165 + 0.125;
						
						if( p >= 0.45)
						{
							p = 0.45;
						}

//            d = 0.2; // 76 挺好

							d = 0.22;
					}
			}
			
			if(s_flag3)  //在三岔内部
			{
				
				if(in_forks_left == 1)  //在三岔左边
				{
					
					tuo = w_angle;	

					p = 0.12;
					
					d = 0.19;
					
					s_error	= 8000 * ( ( cha1 * 0.85 + 0.35 * cha2  ) + s_b * cha2 ) / ( he1 + s_c * my_abs(cha2));
					
				}
				
				if(in_forks_right == 1)
				{
				
					tuo = w_angle;

					p = 0.15;
					
					d = 0.19;
					
					s_error	= 8000 * ( ( cha1 * 0.8 + 0.35 * cha2  ) + s_b * cha2 ) / ( he1 + s_c * my_abs(cha2));
					
				}
				
			}
			
//		在圆环中
			if(normal_left == 1)
			{	
					p = s_error * s_error * 0.00000165 + 0.126;
					d = 0.2;
					
//					cha1 = sqrt(ad[4] + ad[0] * 0.5) - sqrt(ad[5] + 0.5 * ad[1]);
//					
//					cha2 = (sqrt(ad[7]) - sqrt(ad[8]));
//					
//					he1 = (ad[4] + ad[5]);
//					
//				  s_error	= 8000 * ( cha1 +  cha2 ) / ( he1);
			}
	
      place = p * s_error -  d * (tuo);  //进行pid 转向
		
      s_last_error = s_error;
			
			if(normal_left == 1)
			{
					if(place < (right - mid))
					{
							place = right - mid;
					}
					if(place > (left + 10 - mid))
					{
							place = left + 10 - mid;
					}
			}
			
			else 
			{
				
				if(place < (right - mid))
				{
						place = right - mid;
				}
				if(place > (left - mid))
				{
						place = left - mid;
				}
			
			}

      place = (place + mid);
			
      tuo_l = tuo;
			
      return (int)place;

}

int circle_pid_Right()
{
			ps = 2.1;
	
			ds = 0.265;
			
			cha_s = ad[0] - ( ad[1] * 0.1 + 0.9 * ad[2] );
			
			he_s = ad[0] + ad[1];
			
			error_s = cha_s * 100  / he_s;
			
			place_s = ps * error_s -  ds * (tuo);

      if(place_s > (right - mid))
      {
          place_s = right - mid;
      }
      if(place_s < (left - mid))
      {
          place_s = left - mid;
      }

      place_s = (place_s + mid);
			
			if(place_s > 690 )
			{
				place_s = 690;
			}

      return (int)place_s;
}

int circle_pid_Left()
{
			ps = 1.2;
	
			ds = 0.265;
	
		// 利用 竖直 电感 引入 圆环
			
			error_s	= 100 * ( 1.5 * (ad[4] - ad[5]) + 0.5 * ( ad[2] - ad[3]) ) / ( ( ad[4] + ad[5] ) + my_abs( ad[2] - ad[3])); 
			
			place_s = ps * error_s -  ds * (tuo);

      if(place_s > (right - mid))
      {
          place_s = right - mid;
      }
      if(place_s < (left - mid))
      {
          place_s = left - mid;
      }

      place_s = (place_s + mid);
					
					if( place_s < 710 )
					{
						place_s = 710;
					}

      return (int)place_s;

       
}