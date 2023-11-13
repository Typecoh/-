		#include "headfile.h"
		#include "fork.h"
		#include "math.h"

		int s_flag1 = 0;
		int s_flag2 = 0;
		int s_flag3 = 0;
		int s_flag4 = 0;
		int s_flag5 = 0;
		
		int left_podao = 0;
		int step_podao = 0;
	
		
		int ente = 0;

		int enter_fork = 0;
		int duty_fork = 0;
		int leave_fork = 0;

		int cnt_fork = 1;  //第几次进三岔

		int in_left = 0;
		int in_right = 0;

		int fork_left = 0;
		int fork_right = 0;

		int in_forks = 0;  //标记 进入三岔

		int in_forks_left = 0;
		int in_forks_right = 0;

		int enter_fork_step = 0;
		int leave_step = 0;

		int sc = 1000;

		int maichong = 0;

		int switch_cnt = 0;

		int leave_left = 0;
		int leave_right = 0;
		int leave_pid = 0;

		int recording = 0;
		
		int sancha = 0;
		
		int pansancha = 0; // 出圆环 才判断 三岔

		void forks();

		void forks()
		{

				if( ((ad[0] + ad[1]) > (ad[4] + ad[5]))
					&& ad[4] < 80 && ad[5] < 80 
					&& ad[7] < 40 && ad[8] < 40 
					&& s_flag1 == 0 && s_flag2 == 0 && s_flag3 == 0
					&&( maichong == 0 || maichong == 1000)
			  	&& sc >= 1000
					&& ad[9] < 70
					&& ad[0] > 20 && ad[1] > 20
//					&& pansancha == 1
				) // 预判三岔
				{
//						buzzer(true);
						s_flag1 = 1;
						maichong = 0;
				}
				

				if(s_flag1 == 1 && s_flag2 == 0 && s_flag3 == 0 ){ //去除出界

						if ( ( my_divide(ad[4],ad[5]) < 2.3  
									&&  (ad[7] + ad[8] < 45) && (ad[0] + ad[1] > 95) 
									&& ad[6] > ad[9] * 1.1 ) && abs(s_error) < 400 && ( ad[2] + ad[3] + ad[7] + ad[8] < 95) )
					 {
						 
						 in_forks = 1;
						 
						 s_flag2 = 1;
								 
//						 buzzer(true);
						 
						 open = 1;
						 
						 sum_angle = 0;
						
					 }

					 else {

						s_flag1 = 0;

					 }
				}
				
				if(s_flag2 == 1 && s_flag3 == 0) // 判断到 了 三岔
				{
				
					buzzer(true);
					
					duty_fork = 1; // 进入三岔 大角 标志
					
					enter_fork = 1; // 进入三岔
					
					if( cnt_fork == 1)
					{
					 if(recording == 1) recording = 2;
//				 if(recording == 0) recording = 1;
					
						switch_cnt = 1;
						
						maichong = 1;
						
						fork_left = 1; //进左边
						
						left_podao = 1;
						
						fork_right = 0;
						
						duty_ = left ;
						
						Servoinit();
					
						if( sum_angle > 25)
						{
							
							in_forks_left = 1;
							
							open = 0;
							
							s_flag1 = 0;
							
							s_flag2 = 0;
							
							s_flag3 = 1;
							
							enter_fork = 0;
							
							duty_fork = 0;
							
						}
					}
							
					if( cnt_fork == 2)
					{
					
//					if(recording == 1) recording = 2;

						if(recording == 0) recording = 1;
						
						switch_cnt = 2;
						
						maichong = 1;
						
						fork_left = 0;
						
						fork_right = 1; //进右边
						
						duty_ = right - 10 ;
						
						Servoinit();
						
						ki_l = 20;
						ki_r = 20;
						
						Servoinit();

//						if( sum_angle < -20 )
////						if(sum_angle < -20 || ((ad[0] + ad[1] < 70) && (ad[0] + ad[1] > 35) && (ad[2]<15 && ad[3] <15)))
//						{

						if( sum_angle < -20 
//						|| ((ad[0] + ad[1] + ad[4] + ad[5] > 150) && (ad[0] + ad[1] + ad[4] + ad[5] < 190) && my_divide(ad[6],ad[9]) < 1.5) && ad[9] > 25
						)
//						if(sum_angle < -20 || ((ad[0] + ad[1] < 70) && (ad[0] + ad[1] > 35) && (ad[2]<15 && ad[3] <15)))
						{

							in_forks_right = 1;	
							
							s_flag1 = 0;
							
							s_flag2 = 0;
							
							s_flag3 = 1;
							
							enter_fork = 0;
							
							duty_fork = 0;
							
							open = 0;
											
							ki_l = 1;
							ki_r = 1;
							
						}
					}
			}
				
				if(s_flag3 == 1 && s_flag4 == 0)
				{
					
					ente = ente + (nowspeed_L + nowspeed_R) / 2;
					
					if(ente > 1000) {
						ente = 1000;
					}
					//在三岔内部
					
					cir_sancha = 0;
					
					if(fork_left == 1 && fork_right == 0)
					{
						cnt_fork = 2;
					}
					
					if(fork_right == 1 && fork_left == 0)
					{
						cnt_fork = 1;
					}
					
//				if( ((ad[4] > 70 || ad[5] > 70) || (ad[4] +  ad[5]) > 170)
//						&& fork_left == 1 ) 
//				if( ((ad[4] > 65 && ad[5] > 65) || (ad[4] +  ad[5]) > 140)
//						&& fork_left == 1 ) 

					if((((ad[0] > 75 || ad[1] > 75) 
						|| (ad[0] + ad[1] + ad[4] + ad[5])> 340
						|| ad[0] > 150
						|| ad[1] > 150 
						|| ad[4] > 150 
						|| ad[5] > 150)  && fork_left == 1 && step_podao == 10000) 
						&& ente == 1000 && flag_po)
				{
				
						step_podao = 0;
						left_podao = 0;
						cir_sancha = 0; //清空三岔 圆环 之间的pid
				    ente = 0;
						buzzer(false);
						maichong = 0;
						sc = 0;
						
						open = 0;

						s_flag1 = 0;
						s_flag2 = 0;
						s_flag3 = 0;
						s_flag4 = 0;

						enter_fork = 0;
						duty_fork = 0;
						leave_fork = 0;
						
						in_left = 0;
						in_right = 0;

						fork_left = 0;
						fork_right = 0;

						in_forks = 0;  //标记 进入三岔

						in_forks_left = 0;
						in_forks_right = 0;
						
						leave_step = 0;	
						ki_l = 1;
						ki_r = 1;		
						
						pansancha = 0;

						flag_po = 0;
						ki_l = 1;
						ki_r = 1;
						in_normall_speed = speed_yuan;				
						
				}
					 
//					if(((ad[0] > 75 || ad[1] > 75) 
//						|| (ad[0] + ad[1] + ad[4] + ad[5])> 360
//						|| ad[0] > 150
//						|| ad[1] > 150 
//						|| ad[4] > 150 
//						|| ad[5] > 150)  && fork_right == 1) 
					if((((ad[0] > 70 && ad[1] > 70) 
						|| (ad[0] + ad[1] + ad[4] + ad[5])> 320
						|| ad[0] > 140
						|| ad[1] > 140 
						|| ad[4] > 140 
						|| ad[5] > 140)  && fork_right == 1) 
						&& ente == 1000)

						{
							cir_sancha = 0; //清空三岔 圆环 之间的pid
							ente = 0;
		   				leave_pid = 1;
						
							leave_right = 1;
							
							buzzer(false);
							maichong = 0;
							sc = 0;
							open = 0;

							s_flag1 = 0;
							s_flag2 = 0;
							s_flag3 = 0;
							s_flag4 = 0;

							enter_fork = 0;
							duty_fork = 0;
							leave_fork = 0;
							
							in_left = 0;
							in_right = 0;

							fork_left = 0;
							fork_right = 0;

							in_forks = 0;  //标记 进入三岔

							in_forks_left = 0;
							in_forks_right = 0;
							
							leave_step = 0;	
							ki_l = 1;
							ki_r = 1;
							
							pansancha = 0;
							cheku_flag1 = 1;		

						
					}
				}
		}