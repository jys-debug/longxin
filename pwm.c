#include "ls1x_gpio.h"
#include "ls1c102_ptimer.h"
extern int duty;
void PwmInit()
{

timer_init(100);
duty=0;
gpio_set_direction(GPIO_PIN_40,GPIO_Mode_Out);
gpio_set_direction(GPIO_PIN_40,GPIO_Mode_Out);

}