#include "headfile.h"
#include "Circle.h"
#include "my_Math.h"

int iscir = 0;

int circle_count = 0; //����Բ���Ĵ���
int enter_flag = 0; // ����Բ���ı�־��
int leave_flag = 0; // �뿪Բ���ı�־��

int normal_left = 0; // �� ���� ������

long run_step = 0; //���еĲ���

int soon_leave = 0; // �����뿪Բ���ı�־��

int flag[10] = {0}; // ��־�����
int open = 0;       // �򿪽Ƕ��ۼ�

int enter_Left = 0;  // �ж�Ϊ��Բ��
int enter_Right = 0; // �ж�Ϊ��Բ��
 
int enter_step_left = 0; //������Բ���Ĳ���
int enter_step_right = 0; //������Բ���Ĳ���

int leave_step_left = 0;  // �뿪��Բ����Ҫ�ߵĲ���
int leave_step_right = 0; // �뿪��Բ����Ҫ�ߵĲ���

int vary_pulse = 0;
int vary_num = 0;

int cir_sancha = 0;

int next = 0 ;


int duty_min[11] = 
{
			724,724,724,727,727,727,727,727,727,727,727
//		710,710,710,710,710,710,710,710,710,710,710
};

void Left_circle();  //������Բ��
void Right_circle(); //������Բ��
void pre_dir_circle(); // �ж�Բ���ķ���
void clear_count();
void pulse();

void pre_dir_circle(){

  if( ad[0] + ad[1] > 270 && ad[6] > 120 &&  ( ad[0] + ad[4] ) > 220 
			&& enter_Left == 0 && enter_Right == 0 && circle_count == 0)
	{
		// Ϊ�˷�ֹ �ظ����� ����һ����־��

//		buzzer(true); // ������
		
//		if((ad[0] + ad[1] + ad[4] + ad[5] > 550))
//		{
//			next = 1;
//		}
		
		 enter_Left = 1;
		
		 circle_count = 1;
	}

}

void Left_circle(){

//	if((ad[0] + ad[1] + ad[4] + ad[5] > 550) && next == 0 && flag[1] == 0)
//	{
//		next = 1;
//	}
	
//  if( ad[6] > 175
//			&& flag[2] == 0  && (ad[1] + ad[0]) > 320  ) {
//if( ((ad[6] > 175 && ad[9] > 170) || 
//		(ad[0] > 135 && ad[1] > 185 && ad[6] > 145 && ad[9] > 155)) 
//	&& flag[2] == 0  && (ad[1] + ad[0]) > 320  ) {
		if(((ad[6] > 175 && ad[9] > 170) || 
		(ad[0] < 175 && ad[1] > 185 && ad[4] < 175 && ad[5] > 185 && ad[6] > 150 && ad[9] > 150) ||
    (ad[0] > 185 && ad[1] < 130 && ad[4] > 180 && ad[5] < 170 && ad[6] > 150 && ad[9] > 150)) 
		&& flag[2] == 0  ){
	
    // ���÷�����
		
		
		iscir = 1;
		
		open = 1;

    flag[1] = 1;
		if(ad[0] > 185 && ad[1] < 130 && ad[4] > 180 && ad[5] < 170 && ad[6] > 150 && ad[9] > 150)  flag[1] = 3;
		if(ad[0] < 175 && ad[1] > 185 && ad[4] < 175 && ad[5] > 185 && ad[6] > 150 && ad[9] > 150) flag[1] = 2;
//    if(flag[1] == 3)buzzer(true);

		
		sum_angle = 0;

  }

  if( flag[1] && flag[3] == 0 ){

    if(((ad[6] < 170 || ad[9] < 170) && flag[1] == 1) || 
			((ad[6] < 143 || ad[9] < 153) && flag[1] == 2) ||
	  	((ad[9] < 151) && flag[1] == 3)){
		
//		buzzer(true);

			enter_flag = 1;
			
      flag[2] = 1;
        // ��ʼ���� Բ��
      enter_step_left = enter_step_left + nowspeed_L;
			
      if(enter_step_left > 4000){

        flag[3] = 1;
				enter_step_left = 0;

      }
    }
  }
  if( flag[3] == 1 && flag[5] == 0 ){
		
		enter_step_left = enter_step_left + nowspeed_L;
		
		enter_flag = 0;
		
    // �ڻ���������
		
		normal_left = 1;
		
		next = 0; // ��� ������

    if(( sum_angle >= 235 || enter_step_left > 8000) && flag[4] == 0){
			
			enter_step_left = 0;
 
     // ��������
		buzzer(true);
		 soon_leave = 1;
			
		 leave_flag = 1;
			
     flag[4] = 1;
			
		 flag[5] = 1;
		 
    }
		
  }

  if(flag[5] == 1 && flag[6] == 0){

    // ��Բ��
		
//		buzzer(true);

    leave_step_left = leave_step_left + nowspeed_L;

    if((leave_step_left > 8000 || sum_angle >= 330)){

      flag[6] = 1;
			
			buzzer(false);

    } 

  }

  if(flag[6] == 1)
  {
    // �����ɹ�
    // ���б�־λȫ�����

	  buzzer(false);
		
		sum_angle = 0;
		
		cir_sancha = 1;
		
		leave_pid = 0;
		
    enter_Left = 0;
		
		iscir = 0;

    flag[1] = flag[2] = flag[3] = flag[4] = flag[5] = flag[6] = 0;
		
		enter_flag = 0;
		
		leave_flag = 0;
		
		normal_left = 0;
		
		leave_step_left = 0;
		
		open = 0;
		
		vary_pulse = 0; // ���� 
		
		vary_num = 0; // duty_ �޷�
		
		soon_leave = 0;
		
		enter_step_left = 0;
		
		enter_step_left = 0;
		
		pansancha = 1;
		
  }

}

void Right_circle(){
	
//	if( ad[2] > 150 )
//	{
////	��������Բ��λ��
////		enter_flag = 1;
//      enter_Right = 1;
//	}

  if( ad[2] > 210 && flag[2] == 0  && (ad[1] + ad[0]) > 250 ) {

    //���÷�����
		
		buzzer(1);
		
		open = 1;

    flag[1] = 1;
		
		sum_angle = 0;

  }

  if( flag[1] == 1 && flag[3] == 0 ){

    if(ad[2] < 205){
			
			buzzer(0);
			
			enter_flag = 1;
			
      flag[2] = 1;
      // ��ʼ���� Բ��
			
			vary_pulse = 0;  // ÿ�ν��� ������
			
      enter_step_right = enter_step_right + nowspeed_L;
			
      if(enter_step_right > 5000){

        flag[3] = 1;

      }
    }
  }
	
  if(flag[3] == 1 && flag[5] == 0){
		
		enter_flag = 0;
		
    // �ڻ���������

    if(sum_angle <= -260 && flag[4] == 0){

      // ��������
			
		 soon_leave = 1;
			
		 leave_flag = 1;
			
     flag[4] = 1;
			
		 flag[5] = 1;
			
		 buzzer(1);

    }
		
  }

  if(flag[5] == 1 && flag[6] == 0){

    // ��Բ��

    leave_step_right = leave_step_right + nowspeed_L;

    if(leave_step_right > 3000 || ( ad[0] + ad[1] + ad[2] ) > 300 || sum_angle < -355){

      flag[6] = 1;
			
			buzzer(0);

    } 

  }

  if(flag[6] == 1)
  {
    // �����ɹ�
    // ���б�־λȫ�����
		
		buzzer(0);
		
    enter_Right = 0;

    flag[1] = flag[2] = flag[3] = flag[4] = flag[5] = flag[6] = 0;
		
		enter_flag = 0;
		
		leave_flag = 0;
		
		vary_pulse = 0; // ���� 
		
		vary_num = 0; // duty_ �޷�
		
		open = 0;
		
		soon_leave = 0;
		
		enter_step_right = 0;
		
		leave_step_right = 0;
		
		cir_sancha = 1;
		
  }

}

void clear_count()
{
	if(circle_count == 1)
	{
		 run_step = run_step + nowspeed_L;
		
		if(run_step >= 50000)
		{
			circle_count = 0;
			run_step = 0;
		}
	}
}

void pulse()
{

	if(normal_left == 1)

	vary_pulse = vary_pulse + nowspeed_L;
	
	if(vary_pulse < 2000)
	{
		vary_num = 0;
	}
	
	else if(vary_pulse < 3000)
	{
		vary_num = 1;
	}
	
	else if(vary_pulse < 4000)
	{
		vary_num = 2;
	}
	
	else if(vary_pulse < 5000)
	{
		vary_num = 3;
	}
	
	else if(vary_pulse < 6000)
	{
		vary_num = 4;
	}
	
	else if(vary_pulse < 7000)
	{
		vary_num = 6;
	}

	else if(vary_pulse < 10000)
	{
		vary_num = 7;
	}
	
	else if(vary_pulse < 11000)
	{
		vary_num = 8;
	}
	
	else if(vary_pulse < 12000)
	{
		vary_num = 9;
	}
	
	else if(vary_pulse < 12500)
	{
		vary_num = 10;
	}
	
}


