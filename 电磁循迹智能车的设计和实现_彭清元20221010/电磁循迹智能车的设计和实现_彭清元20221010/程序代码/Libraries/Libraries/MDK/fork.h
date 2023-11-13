#ifndef __FORK_H_
#define __FORK_H_

extern int s_flag1;
extern int s_flag2;
extern int s_flag3;
extern int s_flag4;
extern int s_flag5;

extern int process;

extern int in_left;
extern int in_right;

extern int maichong;
extern int sc;

extern int enter_fork;
extern int leave_fork;

extern int duty_fork;

extern int cnt_fork;

extern int in_forks;

extern int fork_left;
extern int fork_right;

extern int in_forks_left;
extern int in_forks_right;

extern int leave_step;
extern int leave_pid;
extern int sancha;

extern int switch_cnt;
extern int recording;

extern int pansancha;

extern int left_podao;
extern int step_podao ;

void forks();


#endif