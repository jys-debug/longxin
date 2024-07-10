#include "ls1x.h"
#include "Config.h"
#include "ls1x_gpio.h"
#include "ls1x_latimer.h"
#include "ls1c102_interrupt.h"
#include "ls1c102_ptimer.h"
#include "iic.h"
#include "ls1x_wdg.h"
#include "ls1x_spi.h"
#include "ls1c102_touch.h"
#include "ls1x_common.h"
#include "ls1x_exti.h"
#include "ls1x_string.h"
#include "UserGpio.h"
#include "ls1x_clock.h"
#include "ls1c102_adc.h"
#include "oled.h"
char str1[50];
char str2[50];
char str3[50];
int value1,value2,value3;
extern int duty;
extern int fanzhuan1;
extern uint8_t choiceNum;
// double myln(double a)
// {
//    int N = 15;
//    int k,nk;
//    double x,xx,y;
//    x = (a-1)/(a+1);
//    xx = x*x;
//    nk = 2*N+1;
//    y = 1.0/nk;
//    for(k=N;k>0;k--)
//    {
//      nk = nk - 2;
//      y = 1.0/nk+xx*y;
     
//    }
//    return 2.0*x*y;
// }
int myln(int a)
{
   int N = 15;
   int k,nk;
   int x,xx,y;
   x = (a-1)/(a+1);
   xx = x*x;
   nk = 2*N+1;
   y = 1/nk;
   for(k=N;k>0;k--)
   {
     nk = nk - 2;
     y = 1/nk+xx*y;
     
   }
   return 2*x*y;
}
// float temp_Get_R(u16 adct)
// {
// 	float v1 = (float)(adct*5)/4096;
// 	float v2 = 5 - v1;
// 	float r = (v1/v2)*10;
	
// 	return r;
// }
int temp_Get_R(int adct)
{
    int v1,v2,r1;
        v1=(adct*5)/4096;
        v2=5-value1;
        r1=(v1/v2)*10;
	return r1;
}
// float Get_Kelvin_Temperature(uint16_t t)
// {
// 	float N1,N2,N3,N4;
// 	float Rntc = temp_Get_R(t);
// 	N1 = (myln(R25)-myln(Rntc))/B;
// 	N2 = 1/T25 - N1;
// 	N3 = 1/N2;
// 	N4 = N3-273.15;
// 	return N4;
// }

int Get_Kelvin_Temperature(int t)
{
	int N1,N2,N3,N4;
	int Rntc = temp_Get_R(t);
	N1 = (myln(10)-myln(Rntc))/3435;
	N2 = 1/298 - N1;
	N3 = 1/N2;
	N4 = N3-273;
	
	return N4;
}
void  ADinit()
{
   
           AFIO_RemapConfig(AFIOB, GPIO_Pin_14, 0);
           AFIO_RemapConfig(AFIOB, GPIO_Pin_16, 0);
           AFIO_RemapConfig(AFIOB, GPIO_Pin_17, 0);       
           Adc_powerOn();
           Adc_close(ADC_CHANNEL_I4);
           Adc_close(ADC_CHANNEL_I6);
           Adc_close(ADC_CHANNEL_I7);
}
void ADSum()
{      
  int wendu;
  if(fanzhuan1==1)
  {
        Adc_open(ADC_CHANNEL_I6);
        value1 = Adc_Measure(ADC_CHANNEL_I6);
        Adc_close(ADC_CHANNEL_I6);
         if(value1>=4000)
         {duty=100;}
         else if(value1<4000 && value1>=2500)
                               {duty=50;}
         else {duty=0;}
        // Adc_open(ADC_CHANNEL_I6);
        // value2 = Adc_Measure(ADC_CHANNEL_I6);
        // Adc_close(ADC_CHANNEL_I6);
         Adc_open(ADC_CHANNEL_I7);
         value3 = Adc_Measure(ADC_CHANNEL_I7);
         Adc_close(ADC_CHANNEL_I7);
        wendu=18+((4096-value3)/150);
        //  value1=Get_Kelvin_Temperature(value1);
          // sprintf(str1, "%4d", value1);
        // sprintf(str2, "%4d", value2);
          sprintf(str3, ":%d", wendu);  
          // OLED_Show_Str(0,4,str1,16); 
        //  OLED_Show_Str(33,2,str2,16);
          if(choiceNum==0)
          {
            OLED_Show_Str(0,4,"光照情况：",16);
            if(duty==100)
            {
              OLED_Show_Str(80,4,"  暗",16);}
                if(duty==50)
            {
              OLED_Show_Str(80,4,"偏暗",16);}
                if(duty==0)
            {
              OLED_Show_Str(80,4,"  亮",16);}
            
            
            OLED_Show_Str(0,2,"温度",16);
            OLED_Show_Str(32,2,str3,16);}
  }
}
