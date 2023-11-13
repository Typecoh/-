#ifndef __SERVO_H_
#define __SERVO_H_
// 舵机调用

extern int duty_;
extern int mid;
extern int left;
extern int right;
extern double p;
extern double d;
extern double place;
extern double s_error;
extern double s_a;
extern double s_b;
extern double s_c;
extern double tuo;
extern double tuo_l;
extern double last_dy;
extern double cha2;
extern double cha1;
extern int out;

void my_dead();  //打死函数
void Servoinit(); //舵机输出值
int PID_servo();
int circle_pid_Right(); // 右圆环的 pid
int circle_pid_Left();  // 左圆环的 pid

#endif