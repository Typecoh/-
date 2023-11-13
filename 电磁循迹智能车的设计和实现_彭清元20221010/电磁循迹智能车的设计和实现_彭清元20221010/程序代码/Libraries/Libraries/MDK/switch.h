#ifndef __SWITCH_H_
#define __SWITCH_H_

#define only_left 1
#define only_right 2
#define not_open_cir 3
#define all_open 4

extern int Dial_Switch[4];
extern int state;

void Dial();

#endif