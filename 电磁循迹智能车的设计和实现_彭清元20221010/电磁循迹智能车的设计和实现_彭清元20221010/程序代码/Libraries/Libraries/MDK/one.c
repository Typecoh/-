#include "headfile.h"
#include "one.h"

double ad[10];
double temp_ad[10];

double save_0[10];
double save_1[10];
double save_2[10];
double save_3[10];
double save_4[10];
double save_5[10];
double save_6[10];
double save_7[10];
double save_8[10];
double save_9[10];

double temp_save_0[10];
double temp_save_1[10];
double temp_save_2[10];
double temp_save_3[10];
double temp_save_4[10];
double temp_save_5[10];
double a = 0.7;
double b = 0.3;
int k = 0;

double min1 = 100;
double min2 = 100;
double min3 = 100; // 270
double min4 = 100;
double min5 = 105;
double max1 = 4095;
double max2 = 4095;
double max3 = 4095;
double max4 = 4095;
double max5 = 4095;
		
		
void ad_read()
{
		 int i = 0;
	
     for(i = 0; i < 10; i++ )
	  {

     save_0[i] = adc_mean_filter(ADC_P15,ADC_12BIT,10);  //下左

     save_1[i] = adc_mean_filter(ADC_P11,ADC_12BIT,10);  //下右

//     save_0[i] = adc_mean_filter(ADC_P11,ADC_12BIT,10);  //下左

//     save_1[i] = adc_mean_filter(ADC_P15,ADC_12BIT,10);  //下右

     save_2[i] = adc_mean_filter(ADC_P16,ADC_12BIT,10);  //下左竖直

     save_3[i] = adc_mean_filter(ADC_P13,ADC_12BIT,10); //下右竖直
			
		 save_4[i] = adc_mean_filter(ADC_P00,ADC_12BIT,10); //上左
			 
	   save_5[i] = adc_mean_filter(ADC_P10,ADC_12BIT,10); // 上右

//		 save_4[i] = adc_mean_filter(ADC_P10,ADC_12BIT,10); //上左
//			 
//	   save_5[i] = adc_mean_filter(ADC_P00,ADC_12BIT,10); // 上右
			
		 save_6[i] = adc_mean_filter(ADC_P14,ADC_12BIT,10); // 下中
		 
		 save_7[i] = adc_mean_filter(ADC_P01,ADC_12BIT,10);  //上左竖直

     save_8[i] = adc_mean_filter(ADC_P06,ADC_12BIT,10);  //上右竖直

     save_9[i] = adc_mean_filter(ADC_P05,ADC_12BIT,10);  //上中间
						
    }

      ad[0] = LB(save_0);
      ad[1] = LB(save_1);
			ad[2] = LB(save_2);
		  ad[3] = LB(save_3);
		  ad[4] = LB(save_4);
	  	ad[5] = LB(save_5);
			ad[6] = LB(save_6);
			ad[7] = LB(save_7);
      ad[8] = LB(save_8);
			ad[9] = LB(save_9);
			
      ad[0] = (double) (ad[0] - min1) / (double) (max1 - min1) * 200;  // 左水平
      ad[1] = (double) (ad[1] - min2) / (double) (max2 - min2) * 200;  // 有水平
			ad[2] = (double) (ad[2] - min2) / (double) (max2 - min2) * 200;	 // 左竖直
	   	ad[3] = (double) (ad[3] - min2) / (double) (max2 - min2) * 200;	 // 右竖直
	  	ad[4] = (double) (ad[4] - min2) / (double) (max2 - min2) * 200;	 // 左前水平
		  ad[5] = (double) (ad[5] - min2) / (double) (max2 - min2) * 200;  // 右前水平
			ad[6] = (double) (ad[6] - min2) / (double) (max2 - min2) * 200;  // 右前水平
			ad[7] = (double) (ad[7] - min2) / (double) (max2 - min2) * 200;	 // 左前水平
		  ad[8] = (double) (ad[8] - min2) / (double) (max2 - min2) * 200;  // 右前水平
			ad[9] = (double) (ad[9] - min2) / (double) (max2 - min2) * 200;  // 右前水平
			

      for( k = 0 ; k<= 9; k++)
      {
          if(ad[k] <= 0) ad[k] = 1;
      }


}

double LB(float *ad)//???????
{
    int i;
    double max1,min1;  //???弫??????
    double sum = 0;

    max1 = ad[0];
    min1 = ad[0];

    for(i=0;i<sizeof(ad);i++)
    {
        if(max1 < ad[i] ) max1 = ad[i];

        if(min1 > ad[i] ) min1 = ad[i];

        sum += ad[i];
    }

    sum =(sum-max1-min1)/(sizeof(ad)-2);    //>>3
		
    return sum;
}
