#include "ls1x.h"
#include "config.h"
#include "ls1x_gpio.h"
#include "ls1x_latimer.h"
#include "ls1c102_interrupt.h"
#include "ls1c102_ptimer.h"
#include "ls1c102AD.h"
#include "iic.h"
#include "ls1x_wdg.h"
#include "ls1x_spi.h"
#include "ls1c102_touch.h"
#include "ls1x_common.h"
#include "ls1x_exti.h"
#include "ls1x_string.h"
#include "ls1x_rtc.h"
#include "ls1c102_i2c.h"
#include "ls1x_uart.h"
#include "UserGpio.h"
#include "ls1x_clock.h"
#include "ls1c102_adc.h"
#include "oled.h"
#include "ADXL345.h"
#include "pwm.h"
#include "Max30102_Work.h"
#include "TimerStartWork.h"
#include "Key.h"
int main(void)
{
  /**/
   extern int shuaidao,time1,set;
   extern uint8_t keynum;
  int celiang2=0;
    SystemClockInit();
    GPIOInit();
     PwmInit();
    KEY_Init();                                 
    OLED_Init();
    EnableInt();  
    ADinit();
    Init_ADXL345();
    Max30102chushi();
    // Ds1302_Init();
Uart1_init(9600);
while(1)
{
  
 
  	  TimeWork();
         ADSum();
  // if(keynum==4 && set==0){celiang2++;celiang2=celiang2%2;}
    // Ds1302_Work();

  //  if(celiang2==1) 
  ADXL345_Work();
  if(shuaidao==1){gpio_write_pin(GPIO_PIN_63,1);UART_SendDataALL(UART1,"AT\r\n",5);
  delay_ms(500);
  UART_SendDataALL(UART1,"ATD17852567315;\r\n",18);
  delay_ms(500);}
}


    /*
     * Never goto here!
     */
    return 0;
}
