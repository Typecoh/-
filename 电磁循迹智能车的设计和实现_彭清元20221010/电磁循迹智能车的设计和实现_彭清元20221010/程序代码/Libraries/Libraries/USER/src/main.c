/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"

/*
 *关于内核频率的设定，可以查看board.h文件
 *在board_init中,已经将P54引脚设置为复位
 *如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */
 
void all_init();
void buzzerInit();
void dataInit();
void show();
void main()
{
	
	DisableGlobalIRQ();	//关闭总中断	
    //sys_clk可选值:30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600。
    //设置系统频率，此频率需要跟STC-ISP软件中的 <输入用户程序运行的IRC频率>选项的频率一致。
    //如果频率设置不对，将会导致串口的数据不正常,PWM的工作不正常等等。
  sys_clk = 30000000;     //设置系统频率为30MHz
	board_init();	
	all_init();  	// 所有函数初始化
	buzzerInit(); // 蜂鸣器初始化
	dataInit(); //数据初始化
  seekfree_wireless_init();  //手机发送使用
	pit_timer_ms(TIM_4,5);				//使用TIMER作为周期中断，时间5ms一次
	EnableGlobalIRQ();	//开启总中断、
	
  while(1)
	{
	
//		show(); //液晶显示的数据
//    
//		data_conversion(sum_angle,maichong,place,w_angle,virtual_scope_data);

//	  uart_putbuff(UART_4,virtual_scope_data,10);		

//		  // 左轮
//			pwm_duty(PWMA_CH3P_P64, 3000);

//			pwm_duty(PWMA_CH4P_P66, 0);
//			
//			// 右轮
//			pwm_duty(PWMA_CH1P_P60, 0);

//			pwm_duty(PWMA_CH2P_P62, 3000);
			
			

	
		
  }		
}

void all_init()
{
	uart_init(UART_4, UART4_RX_P02, UART4_TX_P03, 115200, TIM_2);
	pwm_init(PWMA_CH1P_P60, 17000, 0);     //初始化PWM5  使用引脚P2.5  输出PWM频率17000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMA_CH2P_P62, 17000, 0);
	pwm_init(PWMA_CH3P_P64, 17000, 0);     //初始化PWM5  使用引脚P2.5  输出PWM频率17000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMA_CH4P_P66, 17000, 0);
	ips114_init(); //液晶初始化
	pwm_init(PWMB_CH1_P74,50,mid); //舵机初始化  480
	ctimer_count_init(CTIM0_P34); //编码器初始化
	ctimer_count_init(CTIM3_P04); // 编码器初始化
	gpio_mode(P7_7,GPO_PP); //蜂鸣器初始化
	
	//拨码开关
	gpio_mode(P7_0,GPIO); 
	gpio_mode(P7_1,GPIO); 
	gpio_mode(P7_2,GPIO); 
	gpio_mode(P7_3,GPIO); 
	
	// 干簧管停车
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
	icm20602_init_simspi(); // 陀螺仪初始化
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

		ips114_showuint8(0,0,(int)ad[0]); // 左电感
		ips114_showuint8(40,0,(int)ad[1]); // 右电感
		ips114_showuint8(80,0,(int)ad[2]); // 左竖直电感
		ips114_showuint8(120,0,(int)ad[3]); // 右竖直电感
		ips114_showuint8(160,0,(int)ad[4]); // 左电感
		ips114_showuint8(0,1,(int)ad[5]); // 右电感
		ips114_showuint8(40,1,(int)ad[6]); //  中间电感 
		ips114_showuint8(80,1,(int)ad[7]); // 左电感
		ips114_showuint8(120,1,(int)ad[8]); // 右电感
		ips114_showuint8(160,1,(int)ad[9]); //  中间电感 

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
