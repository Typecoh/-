#include "headfile.h"
#include "switch.h"

int Dial_Switch[4] = {0};

#define only_left 1
#define only_right 2
#define not_open_cir 3
#define all_open 4

int state = 4;

void Dial();

void Dial()
{
    if(P70 == 0 && P71 == 0 && P72 == 0 && P73 == 0)
    {
				 if(cnt_fork==2)
				 
         enter_forks_speed = 65;
				 
				 if(cnt_fork == 1)
				 
				 enter_forks_speed = 68;
				 
         in_left_speed = 76;

         in_right_speed = 76;

         in_normall_speed = 76;

         in_cir_speed = 76;
    }

    else if(P70 == 0 && P71 == 0 && P72 == 0 && P73 == 1)
    {
				 if(cnt_fork==2)
				 
         enter_forks_speed =70;
				 
				 if(cnt_fork == 1)
				 
				 enter_forks_speed = 70;
				 
         in_left_speed = 77;

         in_right_speed = 80;

         in_normall_speed = 78;

         in_cir_speed = 78;
    }

    else if(P70 == 0 && P71 == 0 && P72 == 1 && P73 == 0)
    {
				 if(cnt_fork==2)
				 
         enter_forks_speed = 67;
				 
				 if(cnt_fork == 1)
				 
				 enter_forks_speed = 60;
				 
         in_left_speed = 76;

         in_right_speed = 81;

         in_normall_speed = 79;

         in_cir_speed = 78;
    }

    else if(P70 == 0 && P71 == 1 && P72 == 0 && P73 == 0)
    {
				 if(cnt_fork==2)
				 
         enter_forks_speed = 65;
				 
				 if(cnt_fork == 1)
				 
				 enter_forks_speed = 68;
				 
         in_left_speed = 76;

         in_right_speed = 77;

         in_normall_speed = 77;

         in_cir_speed = 77;
    }
		
		else if(P70 == 1 && P71 == 0 && P72 == 0 && P73 == 0)
    {
				 if(cnt_fork==2)
				 
         enter_forks_speed = 65;
				 
					if(cnt_fork == 1)
				 
				  enter_forks_speed = 65;
				 
         in_left_speed = 68;

         in_right_speed = 68;

         in_normall_speed = 68;

         in_cir_speed = 68;
    }
		
		else if(P70 == 0 && P71 == 0 && P72 == 1 && P73 == 1)
    {
				 if(cnt_fork==2)
				 
         enter_forks_speed = 65;
				 
				 if(cnt_fork == 1)
				 
				 enter_forks_speed = 65;
				 
         in_left_speed = 75;

         in_right_speed = 82;

         in_normall_speed = 75;

         in_cir_speed = 75;
    }
		
	  else if(P70 == 0 && P71 == 1 && P72 == 0 && P73 == 1)
    {
				 if(cnt_fork==2)
				 
         enter_forks_speed = 65;
				 
				 if(cnt_fork == 1)
				 
				 enter_forks_speed = 65;
				 
         in_left_speed = 72;

         in_right_speed = 72;

         in_normall_speed = 72;

         in_cir_speed = 69;
    }
		
		else if(P70 == 1 && P71 == 0 && P72 == 0 && P73 == 1)
    {
				  if(cnt_fork==2)
				 
         enter_forks_speed = 65;
				 
				 if(cnt_fork == 1)
				 
				 enter_forks_speed = 68;
				 
         in_left_speed = 76;

         in_right_speed = 76;

         in_normall_speed = 76;

         in_cir_speed = 76;
    }
		
		else
    {
				 if(cnt_fork==2)
				 
         enter_forks_speed = 67;
				 
				 if(cnt_fork == 1)
				 
				 enter_forks_speed = 67;
				 
         in_left_speed = 77;

         in_right_speed = 81;

         in_normall_speed = 79;

         in_cir_speed = 72;
    }
}
