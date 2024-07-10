#include "ls1x.h"
#include "ls1x_gpio.h"
#include "ls1x_wdg.h"
#include "ls1x_common.h"
#include "ls1x_exti.h"
#include "ls1c102_interrupt.h"
#include "ls1c102_touch.h"
#include "ls1c102_ptimer.h"
#include "ls1c102_i2c.h"
#include "Config.h"


#define	BEBUG_IRQ()  printf("\r\n < IRQ: %d func:%s   >\r\n",__LINE__,__FUNCTION__)
void (* const exti_irq_handle[32])(void);

void exti_gpioa0_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_A0);
}
void exti_gpioa1_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_A1);
}
void exti_gpioa2_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_A2);
}
void exti_gpioa3_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_A3);
}
void exti_gpioa4_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_A4);
}
void exti_gpioa5_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_A5);
}
void exti_gpioa6_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_A6);
}
void exti_gpioa7_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_A7);
}
void exti_gpiob0_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_B0);
}
void exti_gpiob1_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_B1);
}
void exti_gpiob2_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_B2);
}
void exti_gpiob3_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_B3);
}
void exti_gpiob4_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_B4);
}
void exti_gpiob5_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_B5);
}
void exti_gpiob6_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_B6);
}
void exti_gpiob7_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_B7);
}

void exti_gpioc0_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_C0);
}
void exti_gpioc1_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_C1);
}
void exti_gpioc2_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_C2);
}
void exti_gpioc3_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_C3);
}
void exti_gpioc4_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_C4);
}
void exti_gpioc5_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_C5);
}
void exti_gpioc6_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_C6);
}
void exti_gpioc7_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_C7);
}
void exti_gpiod0_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_D0);
}
void exti_gpiod1_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_D1);
}
void exti_gpiod2_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_D2);
}
void exti_gpiod3_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_D3);
}
void exti_gpiod4_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_D4);
}

void exti_gpiod5_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_D5);
}
void exti_gpiod6_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_D6);
}
void exti_gpiod7_irq_handler(void)
{
    BEBUG_IRQ();
    EXTI_ClearITPendingBit(EXTI, IRQ_GPIO_D7);
}
void (* const Ext_IrqHandle[32])(void) =
{
    exti_gpioa0_irq_handler,
    exti_gpioa1_irq_handler,
    exti_gpioa2_irq_handler,
    exti_gpioa3_irq_handler,
    exti_gpioa4_irq_handler,
    exti_gpioa5_irq_handler,
    exti_gpioa6_irq_handler,
    exti_gpioa7_irq_handler,
    exti_gpiob0_irq_handler,
    exti_gpiob1_irq_handler,
    exti_gpiob2_irq_handler,
    exti_gpiob3_irq_handler,
    exti_gpiob4_irq_handler,
    exti_gpiob5_irq_handler,
    exti_gpiob6_irq_handler,
    exti_gpiob7_irq_handler,
    exti_gpioc0_irq_handler,
    exti_gpioc1_irq_handler,
    exti_gpioc2_irq_handler,
    exti_gpioc3_irq_handler,
    exti_gpioc4_irq_handler,
    exti_gpioc5_irq_handler,
    exti_gpioc6_irq_handler,
    exti_gpioc7_irq_handler,
    exti_gpiod0_irq_handler,
    exti_gpiod1_irq_handler,
    exti_gpiod2_irq_handler,
    exti_gpiod3_irq_handler,
    exti_gpiod4_irq_handler,
    exti_gpiod5_irq_handler,
    exti_gpiod6_irq_handler,
    exti_gpiod7_irq_handler,
};

void ext_handler(void)
{
    PMU_CMDW = (1 << 24);
    INT32U regsrc;// = EXTI->EXINT_SRC;
    INT32U regen;// = EXTI->EXINT_SRC;
    INT32U irq_no;
    //BEBUG_IRQ();
    regsrc = EXTI->EXINT_SRC;
    regen = EXTI->EXINT_EN;
    regsrc = (regsrc & regen);
    asm("nop");

    for(irq_no = 0; irq_no < 32; irq_no++)
    {
        if((regsrc>>irq_no) & 0x1)
        {
            Ext_IrqHandle[irq_no]();
        }
    }
}

void SOFT_INT(void)
{
    printf("\n.............SOFT_INT..............\n\r");
    Set_soft_stop();
}

/***********************************************************************
 函数功能:    	8M定时器中断处理函数
 @param:		无
 @other:     无
 @return:	无
 @auther :	朱晓宇
 @time	:	2020年4月9日
 ***********************************************************************/
void TIMER_8M_INT(void)
{
    PMU_CMDW = (1 << 21); // 清除中断标志
    Set_Timer_clear();
    Set_Timer_Init(8 * 10000); //  1.25ms
}

/***********************************************************************
 函数功能:    	定时唤醒中断处理函数
 @param:		无
 @other:     睡眠下定时喂狗，防止系统复位
 @return:	无
 @auther :	朱晓宇
 @time	:	2020年4月9日
 ***********************************************************************/
void TIMER_WAKE_INT(void)
{
    printf("TIMER_WAKE_INT feed WDG!\n\r");
    PMU_CMDW = (1 << 16); // 清除中断标志
    INT32U SleepEn = PMU_CMDSTS & 0xffffffff;
    WDG_DogFeed();
    (void)SleepEn;
    //睡眠后，定时喂狗，否则会不断重启
    Wake_Set(6);        //定时唤醒喂狗
}

/***********************************************************************
 函数功能:    	触摸按键中断处理函数
 @param:	无
 @other:        无
 @return:	无
 @auther :	朱晓宇
 @time	:	2020年4月9日
 ***********************************************************************/
#define KEY_CANCLE 8
void TOUCH(void)
{
    INT16U KeyChannel;
    INT8U KeyType;
    KeyChannel = (TS_STAT >> 16) & 0xfff;
    KeyType = TS_STAT & 0xf;
    PMU_CMDW = (1 << 17); // 清除中断标志
    TS_STAT = 0xf;

    Printf_KeyType(KeyType);
    Printf_KeyChannel(KeyChannel);
    Printf_KeyVal();
}

/***********************************************************************
 函数功能:    	串口2接收中断处理函数
 @param:		无
 @other:     无
 @return:	无
 @auther :	朱晓宇
 @time	:	2020年4月9日
 ***********************************************************************/
void UART2_INT(void)
{
    PMU_CMDW = (1 << 18);
    INT8U uart_sr = UART2_IIR;
    (void)uart_sr;
}

/***********************************************************************
 函数功能:    	电量检测中断处理函数
 @param:		无
 @other:     该中断可查看用户手册
 @return:	无
 @auther :	朱晓宇
 @time	:	2020年4月9日
 ***********************************************************************/
void BAT_FAIL(void)
{
    uint32_t tmp = (PMU_CMDSTS & 0xf80000)>>19;
    PMU_CMDW = (PMU_CMDSTS & 0xf80000);
    switch(tmp)
    {
        case 0x1:
            printf("\r\n.............BAT_FAIL..............\r\n");
            PMU_CMDSTS  =   0x0;   // IT config
            break;
        case 0x2:
            break;
        case 0x4:
            break;
        case 0x8:
            break;
        case 0x10:
            printf("\r\n.............ADC..............\r\n");
            PMU_CMDSTS  &=   (~0x8000);   // IT dis
            break;
        default:
            break;
    }
}

void INTC(void)
{
}

void RING(void)
{
}
int gpio_state0 = 0;
int gpio_state1 = 0;
int count_timer_irq = 0;
int pwm_max_count = 20;
int pwm_cmp0 = 1;
int pwm_cmp1 = 0;

void TIM_SetCompare1(int gpio, int pwm_cmp)
{
    if(gpio == 13)
    {
        if(pwm_cmp > pwm_max_count)
            pwm_cmp0 = pwm_max_count;
        else if(pwm_cmp < 0)
            pwm_cmp0 = 0;
        else
            pwm_cmp0 = pwm_cmp;
    }
    if(gpio == 14)
    {
        if(pwm_cmp > pwm_max_count)
            pwm_cmp1 = pwm_max_count;
        else if(pwm_cmp < 0)
            pwm_cmp1 = 0;
        else
            pwm_cmp1 = pwm_cmp;
    }
}
/***********************************************************************
 函数功能:    	INTC中断处理函数
 @param:		无
 @other:     该中断可查看用户手册
 @return:	无
 @auther :	朱晓宇
 @time	:	2020年4月9日
 ***********************************************************************/
int cnt=0;
int duty;
int fanzhuan=0;
int fanzhuan1=1;
extern short jiasu[3];
int time1=0,time2=0,time3=0;
int biaozhi1=0,biaozhi2=0,biaozhi3=0;
int shuaidao=0;
uint8_t sec=0,min=0,hour=0;
int secss=0;
void intc_handler(void)
{

    INT8U IntReg = INT_OUT;

    if(TIM_GetITStatus(TIM_FLAG_Trigger))
    {

        cnt++;
        secss++;
        fanzhuan++;
               if (secss>10000)
            {
                secss=0;sec++;
            }
            if (sec>59)
            {
                sec=0;min++;
            }
            if (min>59)
            {
                min=0;hour++;

            }
            if(hour>23)
            {
                hour=0;
            }
        if(time1>100000)
       {
     if(jiasu[1]<1000){biaozhi2=1;biaozhi3=1;time1=0;} 
     else{time1=0;}
       }
       
        if((jiasu[1]<1000) || (biaozhi2==1))
        {
            biaozhi2=1;
            if(!biaozhi3){time1++;}
            if(time1>100000){biaozhi2=0;}
            if(biaozhi3==1)
            {
                time2++;
                if(time2>50000)
             {
                if((jiasu[1]<1000) &&(((jiasu[0]>800) || (jiasu[0]<-800)) || ((jiasu[2]>800)||(jiasu[2]<-800))))
                {shuaidao=1;time2=0;biaozhi2=0;}
                else{time2=0;biaozhi2=0;}
             }
           
                
            }
        }

        if(fanzhuan==500)
        {
            fanzhuan=0;
            fanzhuan1=1;
        
        }
        if(cnt>=0&&cnt<=duty)
        {
            gpio_write_pin(GPIO_PIN_26,1);
        }
        if(cnt>duty)
        {
            gpio_write_pin(GPIO_PIN_26,0);
        }
        if(cnt==100)
        {
            cnt=0;
        }

        TIM_ClearIT(TIM_FLAG_Trigger);

    }
    if (IntReg & UART1_INT_OUT) //Uart1
    {
        INT_CLR = UART1_INT_CLR;
    }
    if (IntReg & UART0_INT_OUT) //Uart0
    {
        INT_CLR = UART0_INT_CLR;
    }

    INT_CLR = 0xff;
}

void TIMER_HANDLER(void)
{
    Set_Timer_clear();
    printf("Core Timer clear interrupt..\r\n");
    Set_Timer_stop();
}

