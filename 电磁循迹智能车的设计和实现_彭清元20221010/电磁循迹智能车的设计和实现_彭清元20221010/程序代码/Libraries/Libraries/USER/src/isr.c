///*********************************************************************************************************************
// * COPYRIGHT NOTICE
// * Copyright (c) 2020,��ɿƼ�
// * All rights reserved.
// * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
// *
// * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
// * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
// *
// * @file       		isr
// * @company	   		�ɶ���ɿƼ����޹�˾
// * @author     		��ɿƼ�(QQ790875685)
// * @version    		�鿴doc��version�ļ� �汾˵��
// * @Software 			MDK FOR C251 V5.60
// * @Target core		STC16F40K128
// * @Taobao   			https://seekfree.taobao.com/
// * @date       		2020-4-14
// ********************************************************************************************************************/
#include "headfile.h"
#include "math.h"
int stop_add = 0;

//UART1�ж�
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
        //�����Զ�����
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

//UART2�ж�
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
		//�������ݼĴ���Ϊ��S2BUF

	}
}

//UART3�ж�
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
		//�������ݼĴ���Ϊ��S3BUF

	}
}

//UART4�ж�
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
		//�������ݼĴ���Ϊ��S4BUF;
		
		wireless_uart_callback();//����ת���ڻص�����
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
	INT2_CLEAR_FLAG;  //����жϱ�־
}

void INT3_Isr() interrupt 11
{
	INT3_CLEAR_FLAG;  //����жϱ�־
}

void INT4_Isr() interrupt 16
{
	INT4_CLEAR_FLAG;  //����жϱ�־
}

void TM0_Isr() interrupt 1
{

}

void TM1_Isr() interrupt 3
{

}

void TM2_Isr() interrupt 12
{
	TIM2_CLEAR_FLAG;  //����жϱ�־
}

void TM3_Isr() interrupt 19
{
	TIM3_CLEAR_FLAG; //����жϱ�־
}


void TM4_Isr() interrupt 20
{
	TIM4_CLEAR_FLAG; //����жϱ�־
	
	
	
	//�Լ��ĺ�����дλ��
	
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

		get_icm20602_gyro_simspi(); // ���������ǵ� ���ٶ�
		
		Dial(); // ���뿪��
		
		w_angle = (icm_gyro_z + 7) / 16.384;
    w_angle_y = (icm_gyro_y + 2) / 16.384;
		angle_y();
		if(fork_left) 
		{
			podao();
		}
		if(open == 1)
		{
			angle(); // �Ƕ��ۼ�
		}
		
		if(stop_add < 110)
		{
			stop_add = stop_add + 1;
		}
		
		if(!cheku_flag) speed_analsy();
		
		if(stop_add > 100)
		{
			my_stop(); //ͣ������
		}
		getspeed();	 //��ȡ�ٶ�
	
		cal_speed(); //�����ٶ�
		
		ad_read(); // ��ж���

		pre_dir_circle();  //�ж�Բ���ķ���

//		1 ��ʾ ���
//		2 ��ʾ �ұ�
//		cnt_fork = 2;
		if(enter_Left == 1)  //������
		{
			Left_circle();
		}
		
		if(enter_Right == 1) //�����һ�
		{
			Right_circle();
		}
		
		
//		out = 1;
		// enter_flag ��ʾ ������־
		if(enter_flag == 0 && leave_flag == 0 && duty_fork == 0)
		{
			
			duty_ = (int)PID_servo(); //λ��PID
			
			// enter_Left ��ʾ �����󻷱�־
			// ��Բ������ ѭ��
			if(enter_Left == 1 && normal_left == 1)
			{
			
				duty_ = (int)PID_servo(); //λ��PID
				
				if(duty_ < 740 )
				{
					duty_ = 740;
				}
		
			}
		}
		
		//�� ����Բ���� ʱ�� ��ִ�� һ�º���
		
		if(enter_flag == 1 && leave_flag == 0)
		{
				duty_ = 755;
		}
		
	  clear_count(); // �����Բ���Ĵ���
	
		if(iscir == 0 && ( sancha >= 20000 ))
		{
			forks();  //�ж�����
		}
		if( sancha <= 20100)
		{
			sancha = sancha + (nowspeed_L + nowspeed_R) / 2;
		}
		
  	cheku_plus();
		Servoinit(); //������ֵ	
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