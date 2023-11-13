///*********************************************************************************************************************
// * COPYRIGHT NOTICE
// * Copyright (c) 2020,逐飞科技
// * All rights reserved.
// * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
// *
// * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
// * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
// *
// * @file       		isr
// * @company	   		成都逐飞科技有限公司
// * @author     		逐飞科技(QQ790875685)
// * @version    		查看doc内version文件 版本说明
// * @Software 			MDK FOR C251 V5.60
// * @Target core		STC16F40K128
// * @Taobao   			https://seekfree.taobao.com/
// * @date       		2020-4-14
// ********************************************************************************************************************/
#include "headfile.h"
#include "math.h"
int stop_add = 0;

//UART1中断
void UART1_Isr() interrupt 4
{
    uint8 res;
	static uint8 dwon_count;
    if(UART1_GET_TX_FLAG)
    {
        UART1_CLEAR_TX_FLAG;
        busy[1] = 0;
    }
    if(UART1_GET_RX_FLAG)
    {
        UART1_CLEAR_RX_FLAG;
        res = SBUF;
        //程序自动下载
        if(res == 0x7F)
        {
            if(dwon_count++ > 20)
                IAP_CONTR = 0x60;
        }
        else
        {
            dwon_count = 0;
        }
    }
}

//UART2中断
void UART2_Isr() interrupt 8
{
    if(UART2_GET_TX_FLAG)
	{
        UART2_CLEAR_TX_FLAG;
		busy[2] = 0;
	}
    if(UART2_GET_RX_FLAG)
	{
        UART2_CLEAR_RX_FLAG;
		//接收数据寄存器为：S2BUF

	}
}

//UART3中断
void UART3_Isr() interrupt 17
{
    if(UART3_GET_TX_FLAG)
	{
        UART3_CLEAR_TX_FLAG;
		busy[3] = 0;
	}
    if(UART3_GET_RX_FLAG)
	{
        UART3_CLEAR_RX_FLAG;
		//接收数据寄存器为：S3BUF

	}
}

//UART4中断
void UART4_Isr() interrupt 18
{
    if(UART4_GET_TX_FLAG)
	{
        UART4_CLEAR_TX_FLAG;
		busy[4] = 0;
	}
    if(UART4_GET_RX_FLAG)
	{
        UART4_CLEAR_RX_FLAG;
		//接收数据寄存器为：S4BUF;
		
		wireless_uart_callback();//无线转串口回调函数
	}
}


void INT0_Isr() interrupt 0
{

}

void INT1_Isr() interrupt 2
{

}

void INT2_Isr() interrupt 10
{
	INT2_CLEAR_FLAG;  //清除中断标志
}

void INT3_Isr() interrupt 11
{
	INT3_CLEAR_FLAG;  //清除中断标志
}

void INT4_Isr() interrupt 16
{
	INT4_CLEAR_FLAG;  //清除中断标志
}

void TM0_Isr() interrupt 1
{

}

void TM1_Isr() interrupt 3
{

}

void TM2_Isr() interrupt 12
{
	TIM2_CLEAR_FLAG;  //清除中断标志
}

void TM3_Isr() interrupt 19
{
	TIM3_CLEAR_FLAG; //清除中断标志
}


void TM4_Isr() interrupt 20
{
	TIM4_CLEAR_FLAG; //清除中断标志
	
	
	
	//自己的函数书写位置
	
		pd_shizi();

		if(left_podao == 1)
		{
				step_podao = step_podao + nowspeed_L;
				if(step_podao >= 10000) step_podao = 10000;
		}

		if(sc <= 1010)
		{
			 sc += 1;
		}
			
		action();
		
		finsh();
		
		if(isstart == 1)
		{
			nowtime = cur();
		}
		
		if(isend == 1)
		{
			end_time = Endtime();
		}
	
		if(switch_cnt == 1 || switch_cnt == 2)
		{
			maichong = maichong + (nowspeed_L + nowspeed_R) / 2;
			
			if(maichong > 1000) maichong = 1000;
			
		}

		get_icm20602_gyro_simspi(); // 调用陀螺仪的 角速度
		
		Dial(); // 拨码开关
		
		w_angle = (icm_gyro_z + 7) / 16.384;
    w_angle_y = (icm_gyro_y + 2) / 16.384;
		angle_y();
		if(fork_left) 
		{
			podao();
		}
		if(open == 1)
		{
			angle(); // 角度累加
		}
		
		if(stop_add < 110)
		{
			stop_add = stop_add + 1;
		}
		
		if(!cheku_flag) speed_analsy();
		
		if(stop_add > 100)
		{
			my_stop(); //停车保护
		}
		getspeed();	 //获取速度
	
		cal_speed(); //计算速度
		
		ad_read(); // 电感读数

		pre_dir_circle();  //判断圆环的方向

//		1 表示 左边
//		2 表示 右边
//		cnt_fork = 2;
		if(enter_Left == 1)  //进入左环
		{
			Left_circle();
		}
		
		if(enter_Right == 1) //进入右环
		{
			Right_circle();
		}
		
		
//		out = 1;
		// enter_flag 表示 进环标志
		if(enter_flag == 0 && leave_flag == 0 && duty_fork == 0)
		{
			
			duty_ = (int)PID_servo(); //位置PID
			
			// enter_Left 表示 进入左环标志
			// 在圆环里面 循迹
			if(enter_Left == 1 && normal_left == 1)
			{
			
				duty_ = (int)PID_servo(); //位置PID
				
				if(duty_ < 740 )
				{
					duty_ = 740;
				}
		
			}
		}
		
		//在 进入圆环的 时候 会执行 一下函数
		
		if(enter_flag == 1 && leave_flag == 0)
		{
				duty_ = 755;
		}
		
	  clear_count(); // 清除进圆环的次数
	
		if(iscir == 0 && ( sancha >= 20000 ))
		{
			forks();  //判断三岔
		}
		if( sancha <= 20100)
		{
			sancha = sancha + (nowspeed_L + nowspeed_R) / 2;
		}
		
  	cheku_plus();
		Servoinit(); //舵机输出值	
}


//void  INT0_Isr()  interrupt 0;
//void  TM0_Isr()   interrupt 1;
//void  INT1_Isr()  interrupt 2;
//void  TM1_Isr()   interrupt 3;
//void  UART1_Isr() interrupt 4;
//void  ADC_Isr()   interrupt 5;
//void  LVD_Isr()   interrupt 6;
//void  PCA_Isr()   interrupt 7;
//void  UART2_Isr() interrupt 8;
//void  SPI_Isr()   interrupt 9;
//void  INT2_Isr()  interrupt 10;
//void  INT3_Isr()  interrupt 11;
//void  TM2_Isr()   interrupt 12;
//void  INT4_Isr()  interrupt 16;
//void  UART3_Isr() interrupt 17;
//void  UART4_Isr() interrupt 18;
//void  TM3_Isr()   interrupt 19;
//void  TM4_Isr()   interrupt 20;
//void  CMP_Isr()   interrupt 21;
//void  I2C_Isr()   interrupt 24;
//void  USB_Isr()   interrupt 25;
//void  PWM1_Isr()  interrupt 26;
//void  PWM2_Isr()  interrupt 27;