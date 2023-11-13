#include "headfile.h"
#include "speed.h"
#include "math.h"

int enter_forks_speed = 0;

int in_left_speed = 0;

int in_right_speed = 0;

int in_normall_speed = 0;

int in_cir_speed = 0;

float lb_speed_l[5];
float lb_speed_r[5];

 double speed1;
 double speed2;
 double all_speed;
 
 double all_speed_L;
 double all_speed_R;
 
 double now_speed;
 
 double nowspeed_L;
 double nowspeed_R;
 
 double old_speed;
 
 double duty_L;
 double duty_R;
 double motor_out1;
 double motor_out2;
 double run = 1;
 double temp;
 
 double pidinc1;
 double pidinc2;

 double temp_duty_L;
 double temp_duty_R;

 double lderror = 0;
 double rderror = 0;
 int i_my = 0;

struct PID1_ {

        double error;
        double last_error;   //?????
        double pre_error;    //?????
        double last_speed;

}pid1;

struct PID2_{

        double error;
        double last_error;   //?????
        double pre_error;    //?????
        double last_speed;

}pid2;

double kp_l = 27, ki_l = 3,  kd_l = 0.05;
double kp_r = 27, ki_r = 3,  kd_r = 0.05;

void getspeed();
double PID_Increase1(double ActualSpeed,double SetSpeed);
double PID_Increase2(double ActualSpeed,double SetSpeed);
void Motor_rotation_L(int duty_l);
void Motor_rotation_R(int duty_r);
double limit_protect(int input,int min,int max);
void cal_speed();



void getspeed()
{
 // 获取编码器的值
 //	切记 不要将速度 反转
 
		if(P53 == 1)
		{
				nowspeed_L = ctimer_count_read(CTIM3_P04);	
		}
		
		else
		{
				nowspeed_L = -1 * ctimer_count_read(CTIM3_P04);
		}
		
		if(P35 == 0)
		{
				nowspeed_R = ctimer_count_read(CTIM0_P34);
		}
		
		else
		{
				nowspeed_R = -1 * ctimer_count_read(CTIM0_P34);
		}

		// 将编码器的值清空
    ctimer_count_clean(CTIM0_P34);
    ctimer_count_clean(CTIM3_P04);	
}


double PID_Increase1(double ActualSpeed,double SetSpeed)
{
    double ierror;

    ierror = SetSpeed - ActualSpeed;

        pidinc1 =  kp_l * ( ierror - pid1.last_error )
                 + ki_l * ierror
                 + kd_l *(ierror - 2 * pid1.last_error + pid1.pre_error);

        pid1.pre_error = pid1.last_error;

        pid1.last_error=ierror;

        pid1.last_speed=ActualSpeed;

        return pidinc1;
}


double PID_Increase2(double ActualSpeed,double SetSpeed)
{
    double ierror;

    ierror = SetSpeed - ActualSpeed;

        pidinc2 =  kp_r * ( ierror - pid2.last_error )
                 + ki_r * ierror
                 + kd_r *(ierror - 2 * pid2.last_error + pid2.pre_error);

        pid2.pre_error=pid2.last_error;

        pid2.last_error=ierror;

        pid2.last_speed=ActualSpeed;

        return pidinc2;
}

void cal_speed()
{

				
//			int encoder =  (nowspeed_L + nowspeed_R) / 2;
//			motor_out1 += PID_Increase1(encoder,all_speed_L); 
//			motor_out2 += PID_Increase2(encoder,all_speed_R); 

//			int encoder =  (nowspeed_L + nowspeed_R) / 2;

			if(s_error >= 0)
			{
						motor_out1 += PID_Increase1(nowspeed_L,all_speed_L - 0.2 * sqrt(abs(s_error))); 
						motor_out2 += PID_Increase2(nowspeed_R,all_speed_R + 0.2 * sqrt(abs(s_error))); 
			}
			
			else 
			{
						motor_out1 += PID_Increase1(nowspeed_L,all_speed_L + 0.27 * sqrt(abs(s_error))); 
						motor_out2 += PID_Increase2(nowspeed_R,all_speed_R - 0.27 * sqrt(abs(s_error))); 
			}
//			motor_out1 += PID_Increase1(nowspeed_L,all_speed_L - 0.2 * sqrt(abs(s_error))); 
//			motor_out2 += PID_Increase2(nowspeed_R,all_speed_R + 0.2 * sqrt(abs(s_error))); 
			
			motor_out1 = limit_protect(motor_out1,-950,950);
			motor_out2 = limit_protect(motor_out2,-950,950);
			
			duty_L = motor_out1 * 10;
			duty_R = motor_out2 * 10;
	
			if(run == 1)
			{
					Motor_rotation_L(duty_L);

					Motor_rotation_R(duty_R);
			}

			else
			{
			
					Motor_rotation_L(0);

					Motor_rotation_R(0);
			}
}

void Motor_rotation_R(int duty_l)
{
    if(duty_l < 0)
    {
        pwm_duty(PWMA_CH1P_P60, -duty_l);

        pwm_duty(PWMA_CH2P_P62, 0);

    }
    else if(duty_l > 0 )
    {

        pwm_duty(PWMA_CH1P_P60, 0);

        pwm_duty(PWMA_CH2P_P62, duty_l);

    }
    else
    {
        pwm_duty(PWMA_CH1P_P60, 0);

        pwm_duty(PWMA_CH2P_P62, 0);
    }
}

void Motor_rotation_L(int duty_r)
{
    if(duty_r < 0)
    {

        pwm_duty(PWMA_CH3P_P64, 0);

        pwm_duty(PWMA_CH4P_P66, -duty_r);

    }
    else if(duty_r > 0)
    {

        pwm_duty(PWMA_CH3P_P64, duty_r);

        pwm_duty(PWMA_CH4P_P66, 0);

    }
    else
    {
        pwm_duty(PWMA_CH3P_P64, 0);                                         

        pwm_duty(PWMA_CH4P_P66, 0);
    }
}

double limit_protect(int input,int min,int max)
{
	if(input > max) return max;
	
	if(input < min) return min;
	
	return input;
}

void speed_analsy()
{
				
				int a = 0;
			  a = w_angle;
			  if(a > 100) a = 100;
			  if(a < -100) a = -100;


			 if(in_forks == 1) {
				 
//				 进岔口减速
				 	all_speed_L = enter_forks_speed;
					all_speed_R =  enter_forks_speed;
				 
//				 在左三岔
				if(in_forks_left == 1)
				{
//				 左三岔内

					all_speed_L = in_left_speed;
					all_speed_R = in_left_speed ;
					
				}
				
				if(in_forks_right == 1)
				{	
//				右三岔内

					all_speed_L = in_right_speed ;
					all_speed_R = in_right_speed ;
					
				}
			}
			 
			else if(iscir == 1) // 在圆环里
			{
					all_speed_L = in_cir_speed;
					all_speed_R = in_cir_speed;
					
					if(soon_leave == 1)
					{
						all_speed_L  = 65;
						all_speed_R  = 65;
					}
					
			}
		 
//			在三岔外面			 
			else if( isend == 0 )
			{
					all_speed_L = 0;		
					all_speed_R = 0;
			}
			
			else 
			{
			
						if( isend == 0 )
						{
								all_speed_L = 0;		
								all_speed_R = 0;
						}
						
						else
						{
						
								if(next == 1)
								{
									all_speed_L = in_normall_speed - 5;		
									all_speed_R = in_normall_speed - 5;
								}
								
								else 
								{
									all_speed_L = in_normall_speed;		
									all_speed_R = in_normall_speed;
								}
						
									
//									if(s_error > 0)
//									{
//										all_speed_L = in_normall_speed - (int)(0.004 * abs(s_error)) ;
//										all_speed_R = in_normall_speed + (int)(0.004 * abs(s_error));
//										
//									}
//									
//									else if(s_error < 0)
//									{
//										all_speed_L = in_normall_speed + (int)(0.004 * abs(s_error)) ;
//										all_speed_R = in_normall_speed - (int)(0.004 * abs(s_error));
//									}
									
//									all_speed_L = in_normall_speed - (int)(0.002 * abs(s_error)) ;
//									all_speed_R = in_normall_speed + (int)(0.002 * abs(s_error));
						}
//			
//						all_speed_L = in_normall_speed - (int)(0.02 * a) ;
//						all_speed_R = in_normall_speed + (int)(0.02 * a);

//					all_speed_L = in_normall_speed - (int)(0.02 * a) ;
//					all_speed_R = in_normall_speed + (int)(0.02* a);
			
					all_speed_L = in_normall_speed;		
					all_speed_R = in_normall_speed;
			}
}



