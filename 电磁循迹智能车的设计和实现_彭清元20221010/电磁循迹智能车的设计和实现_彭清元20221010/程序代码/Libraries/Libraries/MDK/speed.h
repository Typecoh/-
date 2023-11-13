#ifndef __SPEED_H_
#define __SPEED_H_
#define DIR_left P35
#define DIR_right P53 
extern int setspeed_l;
extern int setspeed_r;
extern double speed1;
extern double speed2;
extern double all_speed;
extern double all_speed_L;
extern double all_speed_R;
extern double now_speed;
extern double nowspeed_L;
extern double nowspeed_R;
extern double old_speed;
extern double duty_L;
extern double duty_R;
extern double motor_out1;
extern double motor_out2;
extern double run;
extern double temp;

extern int in_normall_speed;
extern int enter_forks_speed;
extern int in_left_speed;
extern int in_right_speed;
extern int in_cir_speed;

extern double pidinc1;
extern double pidinc2;

extern float lb_speed_l[5];
extern float lb_speed_r[5];

extern double temp_duty_L;
extern double temp_duty_R;

extern double ki_l;
extern double ki_r;

extern double lderror;
extern double rderror;
extern int i_my;

void Motor_rotation_L(int duty_l);
void Motor_rotation_R(int duty_r);
void getspeed();
void cal_speed();

void speed_analsy();


#endif