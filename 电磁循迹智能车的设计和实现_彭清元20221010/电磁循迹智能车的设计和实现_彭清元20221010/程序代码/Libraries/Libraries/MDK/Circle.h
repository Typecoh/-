#ifndef __CIRCLE_H_
#define __CIRCLE_H_
extern int circle_count; // 清除圆环的次数
extern long run_step; //运行的步数
extern int normal_left;
extern int enter_flag; //进环标志
extern int leave_flag; //出环标志
extern int soon_leave; //立刻离开标志
extern int open;       //打开角度计数标志
extern int enter_Left;  // 判断为左圆环
extern int enter_Right; // 判断为右圆环
extern int enter_step_left; //进入左圆环的步数
extern int enter_step_right; //进入右圆环的步数
extern int flag[10];

extern int vary_pulse; // 变化的 限幅 指标
extern int duty_min[11]; // 变化的 限幅
extern int vary_num;
extern int cir_sancha;
extern int next;

extern int iscir;
void Left_circle();  //进入左圆环
void Right_circle(); //进入右圆环
void pre_dir_circle(); // 判断圆环的方向
void clear_count(); //清除进圆环的次数

void pulse();

#endif