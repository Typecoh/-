#ifndef __CIRCLE_H_
#define __CIRCLE_H_
extern int circle_count; // ���Բ���Ĵ���
extern long run_step; //���еĲ���
extern int normal_left;
extern int enter_flag; //������־
extern int leave_flag; //������־
extern int soon_leave; //�����뿪��־
extern int open;       //�򿪽Ƕȼ�����־
extern int enter_Left;  // �ж�Ϊ��Բ��
extern int enter_Right; // �ж�Ϊ��Բ��
extern int enter_step_left; //������Բ���Ĳ���
extern int enter_step_right; //������Բ���Ĳ���
extern int flag[10];

extern int vary_pulse; // �仯�� �޷� ָ��
extern int duty_min[11]; // �仯�� �޷�
extern int vary_num;
extern int cir_sancha;
extern int next;

extern int iscir;
void Left_circle();  //������Բ��
void Right_circle(); //������Բ��
void pre_dir_circle(); // �ж�Բ���ķ���
void clear_count(); //�����Բ���Ĵ���

void pulse();

#endif