/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"

/*
 *�����ں�Ƶ�ʵ��趨�����Բ鿴board.h�ļ�
 *��board_init��,�Ѿ���P54��������Ϊ��λ
 *�����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */
 
void all_init();
void buzzerInit();
void dataInit();
void show();
void main()
{
	
	DisableGlobalIRQ();	//�ر����ж�	
    //sys_clk��ѡֵ:30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
  sys_clk = 30000000;     //����ϵͳƵ��Ϊ30MHz
	board_init();	
	all_init();  	// ���к�����ʼ��
	buzzerInit(); // ��������ʼ��
	dataInit(); //���ݳ�ʼ��
  seekfree_wireless_init();  //�ֻ�����ʹ��
	pit_timer_ms(TIM_4,5);				//ʹ��TIMER��Ϊ�����жϣ�ʱ��5msһ��
	EnableGlobalIRQ();	//�������жϡ�
	
  while(1)
	{
	
//		show(); //Һ����ʾ������
//    
//		data_conversion(sum_angle,maichong,place,w_angle,virtual_scope_data);

//	  uart_putbuff(UART_4,virtual_scope_data,10);		

//		  // ����
//			pwm_duty(PWMA_CH3P_P64, 3000);

//			pwm_duty(PWMA_CH4P_P66, 0);
//			
//			// ����
//			pwm_duty(PWMA_CH1P_P60, 0);

//			pwm_duty(PWMA_CH2P_P62, 3000);
			
			

	
		
  }		
}

void all_init()
{
	uart_init(UART_4, UART4_RX_P02, UART4_TX_P03, 115200, TIM_2);
	pwm_init(PWMA_CH1P_P60, 17000, 0);     //��ʼ��PWM5  ʹ������P2.5  ���PWMƵ��17000HZ   ռ�ձ�Ϊ�ٷ�֮ pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMA_CH2P_P62, 17000, 0);
	pwm_init(PWMA_CH3P_P64, 17000, 0);     //��ʼ��PWM5  ʹ������P2.5  ���PWMƵ��17000HZ   ռ�ձ�Ϊ�ٷ�֮ pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMA_CH4P_P66, 17000, 0);
	ips114_init(); //Һ����ʼ��
	pwm_init(PWMB_CH1_P74,50,mid); //�����ʼ��  480
	ctimer_count_init(CTIM0_P34); //��������ʼ��
	ctimer_count_init(CTIM3_P04); // ��������ʼ��
	gpio_mode(P7_7,GPO_PP); //��������ʼ��
	
	//���뿪��
	gpio_mode(P7_0,GPIO); 
	gpio_mode(P7_1,GPIO); 
	gpio_mode(P7_2,GPIO); 
	gpio_mode(P7_3,GPIO); 
	
	// �ɻɹ�ͣ��
	gpio_mode(P2_6,GPIO); 

	adc_init(ADC_P00,ADC_SYSclk_DIV_2);
	adc_init(ADC_P01,ADC_SYSclk_DIV_2);
	adc_init(ADC_P05,ADC_SYSclk_DIV_2);
	adc_init(ADC_P06,ADC_SYSclk_DIV_2);
	adc_init(ADC_P10,ADC_SYSclk_DIV_2);
	adc_init(ADC_P11,ADC_SYSclk_DIV_2);
	adc_init(ADC_P13,ADC_SYSclk_DIV_2);
	adc_init(ADC_P14,ADC_SYSclk_DIV_2);
	adc_init(ADC_P15,ADC_SYSclk_DIV_2);
	adc_init(ADC_P16,ADC_SYSclk_DIV_2);
	icm20602_init_simspi(); // �����ǳ�ʼ��
}

void buzzerInit()
{
	P77 = 0;
}

void dataInit()
{
	sum_angle = 0;
}

void show()	
{

		ips114_showuint8(0,0,(int)ad[0]); // ����
		ips114_showuint8(40,0,(int)ad[1]); // �ҵ��
		ips114_showuint8(80,0,(int)ad[2]); // ����ֱ���
		ips114_showuint8(120,0,(int)ad[3]); // ����ֱ���
		ips114_showuint8(160,0,(int)ad[4]); // ����
		ips114_showuint8(0,1,(int)ad[5]); // �ҵ��
		ips114_showuint8(40,1,(int)ad[6]); //  �м��� 
		ips114_showuint8(80,1,(int)ad[7]); // ����
		ips114_showuint8(120,1,(int)ad[8]); // �ҵ��
		ips114_showuint8(160,1,(int)ad[9]); //  �м��� 

		ips114_showstr(0,2,"ch");
//		ips114_showint16(50,2,cha1);
		ips114_showfloat(50,2,cha1,3,2);
		ips114_showstr(100,2,"cha");
		ips114_showfloat(150,2,cha2,3,2);
		ips114_showstr(0,3,"all_L");
		ips114_showint16(50,3,all_speed_L); 
		ips114_showstr(100,3,"z");
		ips114_showint16(150,3,sum_angle);

		ips114_showstr(0,4,"soon");
		ips114_showint8(50,4,soon_leave); 
		ips114_showstr(100,4,"open");
		ips114_showint8(150,4,open); 
		
		ips114_showstr(0,5,"duty");
		ips114_showuint16(50,5,duty_);
		
		ips114_showstr(100,5,"error");
		ips114_showfloat(150,5,s_error,3,2);
		
		ips114_showstr(0,6,"p");
		ips114_showfloat(50,6,p,2,3);
		
		ips114_showstr(100,6,"d");
		ips114_showfloat(150,6,d,2,3);
		
		ips114_showstr(0,7,"cir");
		ips114_showint8(50,7,cir_sancha);
		
		ips114_showstr(100,7,"SUM");
		ips114_showint16(150,7,circle_count);

}
