#ifndef __ICM_H_
#define __ICM_H_

extern double sum_angle; //角度累加
extern float w_angle;  //角速度
extern float w_angle_y; //y方向角速度
extern double sum_angle_y; //y方向角度
extern int flag_po;
extern int speed_yuan;

extern void angle();
extern void angle_y();
extern void podao();

#endif