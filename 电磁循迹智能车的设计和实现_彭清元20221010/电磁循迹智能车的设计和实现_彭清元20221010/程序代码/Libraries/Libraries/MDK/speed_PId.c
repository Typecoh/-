#include "headfile.h"
#include "speed.h"

int speed1;
int speed2;
int all_speed;
int now_speed;
int nowspeed_L;
int nowspeed_R;
int old_speed;
int duty_L;
int duty_R;
int motor_out;
int motor_out1;
int motor_out2;
int run = 1;

int temp_duty_L;
int temp_duty_R;

// 给左轮使用 的pid
struct PID1_ {

        int error;
        int last_error;   
        int pre_error;   
        int last_speed;

}pid1;

// 给右轮使用的pid
struct PID2_{

        int error;
        int last_error;   
        int pre_error;    
        int last_speed;

}pid2;


float kp_l = 50, ki_l = 0.5,  kd_l = 0;
float kp_r = 50, ki_r = 0.5,  kd_r = 0;
// 获取当前速度
void getspeed();
// 给左轮调pid
int PID_Increase1(int ActualSpeed,int SetSpeed);
// 给右轮调pid
int PID_Increase2(int ActualSpeed,int SetSpeed);
// 左轮 电机输出
void Motor_rotation_L(int L);
// 右轮电机输出
void Motor_rotation_R(int R);

void getspeed()
{
  // 获取编码器的值
    nowspeed_L = ctimer_count_read(CTIM0_P34);  
    nowspeed_R = ctimer_count_read(CTIM3_P04);   
  // 将编码器的值清空
    ctimer_count_clean(CTIM0_P34);
    ctimer_count_clean(CTIM3_P04);
}


int PID_Increase1(int ActualSpeed,int SetSpeed)
{
    int32 ierror;

    ierror = SetSpeed - ActualSpeed;

        pidinc1 =  kp_* ( ierror - pid1.last_error )
                + ki_* ierror
                + kd_*(ierror - 2 * pid1.last_error + pid1.pre_error);

        pid1.pre_error=pid1.last_error;

        pid1.last_error=ierror;

        pid1.last_speed=ActualSpeed;

        if(pidinc1>=5600){

            pidinc1=5600;

        }
        if(pidinc1<=-5600){

            pidinc1=-5600;

        }

        return pidinc1;
}


void cal_speed()
{

   now_speed = (nowspeed_L + nowspeed_R) * 0.5;  
   now_speed = now_speed * 0.9 + old_speed * 0.1;

   old_speed = now_speed;

    motor_out1 += PID_Increase1(now_speed,all_speed);  //????????????????pid????
    motor_out2 += PID_Increase2(now_speed,all_speed);

    duty_L = motor_out1 
    duty_R = motor_out2 

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



void Motor_rotation_L(int duty_l)
{
    if(duty_l < 0)//???
    {
        if( duty_l < -5000)
        {
            duty_l = -5000;
        }

        pwm_duty(PWMA_CH1P_P60, 0);

        pwm_duty(PWMA_CH2P_P62, -duty_l);

        temp_duty_L = -duty_l;
    }
    else if(duty_l > 0 )//???
    {

        if(duty_l > 5000)
        {
            duty_l = 5000;
        }

        pwm_duty(PWMA_CH1P_P60, duty_l);

        pwm_duty(PWMA_CH2P_P62, 0);

    }
    else
    {
        pwm_duty(PWMA_CH1P_P60, 0);

        pwm_duty(PWMA_CH2P_P62, 0);
    }
}

void Motor_rotation_R(int duty_r)
{
    if(duty_r < 0)//???
    {

        if( duty_r < -5000)
        {
            duty_r = -5000;
        }

        pwm_duty(PWMA_CH3P_P64, 0);

        pwm_duty(PWMA_CH4P_P66, -duty_r);

        temp_duty_R = -duty_r;
    }
    else if(duty_r > 0)//???
    {

       if(duty_r > 5000)
       {
           duty_r = 5000;
       }

        pwm_duty(PWMA_CH3P_P64, duty_r);

        pwm_duty(PWMA_CH4P_P66, 0);

    }
    else
    {
        pwm_duty(PWMA_CH3P_P64, 0);

        pwm_duty(PWMA_CH4P_P66, 0);
    }
}
